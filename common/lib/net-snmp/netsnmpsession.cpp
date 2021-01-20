#include "netsnmpsession.h"
#include "snmpvar.h"

#include <QDebug>

using namespace SDPO;

/*****************************************************************/

NetSnmpSession::NetSnmpSession(QObject *parent)
    : QObject (parent),
      m_SessPtr (nullptr),
      m_DestHost   (DEST_HOST_DEFAULT),
      m_Community  (COMMUNITY_DEFAULT),
      m_Version    (SnmpVersion::SNMPvDefault),
      m_Timeout    (SnmpDefaults::SnmpTimeout),
      m_Retries    (SnmpDefaults::SnmpRetries)
{
    NetSNMP::initMib();
}

/*****************************************************************/

NetSnmpSession::NetSnmpSession(const QVariantMap &map, QObject *parent)
    : QObject(parent),
      m_SessPtr(nullptr)
{
    m_DestHost   = map.value(NET_SNMP_SESSION_DESTHOST, DEST_HOST_DEFAULT).toString();
    m_Community  = map.value(NET_SNMP_SESSION_COMMUNITY, COMMUNITY_DEFAULT).toString();
    m_Version    = static_cast<SnmpVersion>(map.value(NET_SNMP_SESSION_VERSION, SnmpVersion::SNMPvDefault).toInt());
    m_Timeout    = map.value(NET_SNMP_SESSION_TIMEOUT, SnmpDefaults::SnmpTimeout).toInt();
    m_Retries    = map.value(NET_SNMP_SESSION_RETRIES, SnmpDefaults::SnmpRetries).toInt();

    NetSNMP::initMib();
}

/*****************************************************************/

NetSnmpSession::~NetSnmpSession()
{
    close();
}

/*****************************************************************/

bool NetSnmpSession::open()
{
    m_ErrorStr.clear();

    if (m_SessPtr) { // already opened
        if (m_Reopen) {
            close();
        } else {
            return true;
        }
    }

    // Initialize a "session" that defines who we're going to talk to
    netsnmp_session session;
    snmp_sess_init(&session); // setup defaults
    session.peername      = m_DestHost.toLocal8Bit().data();
    session.version       = static_cast<long>(m_Version);
    session.community     = reinterpret_cast<u_char*>(m_Community.toLocal8Bit().data());
    session.community_len = static_cast<size_t>(m_Community.size());
    session.retries       = m_Retries;

    SOCK_STARTUP;
    m_SessPtr = snmp_open(&session); // establish the session

    if (!m_SessPtr) {
        char *err;
        snmp_error(&session, nullptr, nullptr, &err);
        m_ErrorStr = QString(err);
        SNMP_FREE(err);
        SOCK_CLEANUP;
        return false;
    }
    return true;
}

/*****************************************************************/

void NetSnmpSession::close()
{
    if (m_SessPtr) {
        snmp_close(m_SessPtr);
        SOCK_CLEANUP;
    }
    m_Reopen = false;
}

/*****************************************************************/

SnmpPdu NetSnmpSession::synchResponse(const SnmpPdu &request)
{
    SnmpPdu response;
    response.status = static_cast<SnmpResponseStatus>(snmp_synch_response(m_SessPtr, request.ptr, &response.ptr));
    return response;
}

/*****************************************************************/

SnmpValue NetSnmpSession::get(const QString &oidStr)
{
    MibOid anOid = MibOid::parse(oidStr);
    if (anOid.hasError()) {
        emit error(QString("%1: %2").arg(oidStr, anOid.errString()));
        return SnmpValue();
    }

    QList<MibOid> mibOids;
    mibOids.append(anOid);

    QList<SnmpValue> values = get(mibOids);
    if (!values.isEmpty()) {
        return values.first();
    }

    return SnmpValue();
}

/*****************************************************************/

QList<SnmpValue> NetSnmpSession::get(const QList<MibOid>& oids)
{
    QList<SnmpValue> result;

    if (oids.isEmpty()) {
        emit error("Missing object names");
        return result;
    }

    if (oids.size() > SNMP_MAX_CMDLINE_OIDS) {
        emit error(QString("Too many object identifiers specified.\n"
             "Only %1 allowed in one request.").arg(SNMP_MAX_CMDLINE_OIDS));
        return result;
    }

    if (!open()) {
        emit error(m_ErrorStr);
        return result;
    }

    SnmpPdu pdu = SnmpPdu::create(SnmpPduGet, oids);
    SnmpPdu response;

    bool retry = false;

    do {
        retry = false;
        response = this->synchResponse(pdu);

        if (response.status == SnmpRespStatSuccess) {
            if (response.errStat() == SNMP_ERR_NOERROR) {
                for(SnmpVar var = response.variables(); var.isValid(); var = var.nextVariable()) {
                    result.append(SnmpValue::fromVar(var));
                }
            } else {
                QString errString
                        = QString("Error in packet\nReason: %1\n").arg(response.errorString());
                SnmpVar errVar = response.failedObject();
                if (errVar.isValid()) {
                    errString.append(QString("Failed object: %1\n").arg(errVar.mibOid().toString()));
                }
                emit error(errString);

                if (m_FixPdu) {
                    pdu = response.fix(SnmpPduGet);
                    response.cleanup();
                    retry = pdu.isValid();
                }
            }


        } else if (response.status == SnmpRespStatTimeout) {
            emit error(QString("Timeout: No Response from %1.").arg(m_DestHost));
        } else { // status == SnmpRespStatError
            emit error(errorStr());
        }

    } while (retry);

    response.cleanup();

    return result;
}

/*****************************************************************/

QList<SnmpValue> NetSnmpSession::get(const QStringList &oids)
{
    QList<MibOid> mibOids;
    foreach(const QString& oidStr, oids) {
        MibOid anOid = MibOid::parse(oidStr);
        if (anOid.hasError()) {
            emit error(QString("%1: %2").arg(oidStr, anOid.errString()));
            return QList<SnmpValue>();
        }
        mibOids.append(anOid);
    }

    return get(mibOids);
}

/*****************************************************************/

QList<SnmpValue> NetSnmpSession::get(const QVariantMap &map)
{
    QStringList oids = map.value(NET_SNMP_CMD_OIDS, QStringList()).toStringList();
    return get(oids);
}

/*****************************************************************/

QList<SnmpValue> NetSnmpSession::getNext(const QString &oidStr, int cnt)
{
    QList<SnmpValue> result;

    MibOid anOid = MibOid::parse(oidStr);
    if (anOid.hasError()) {
        emit error(QString("%1: %2").arg(oidStr, anOid.errString()));
        return result;
    }

    if (!open()) {
        emit error(m_ErrorStr);
        return result;
    }


    for(int i=0;i<cnt;i++) {

        SnmpPdu pdu = SnmpPdu::create(SnmpPduGetNext, anOid);
        SnmpPdu response = this->synchResponse(pdu);

        if (response.status == SnmpRespStatSuccess) {
            if (response.errStat() == SNMP_ERR_NOERROR) {
                for(SnmpVar var = response.variables(); var.isValid(); var = var.nextVariable()) {
                    anOid = var.mibOid();
                    SnmpValue snmpValue = SnmpValue::fromVar(var);
                    result.append(snmpValue);
                }
            } else {
                emit error(QString("Error in packet\nReason: %1").arg(
                                    response.errorString()));
                break;
            }
        } else if (response.status == SnmpRespStatTimeout) {
            emit error(QString("Timeout: No Response from %1.").arg(m_DestHost));
            break;
        } else { // status == SnmpRespStatError
            emit error(errorStr());
            break;
        }

        response.cleanup();
    }

    return result;
}

/*****************************************************************/

QList<SnmpValue> NetSnmpSession::getRow(const QString &oidStr)
{
    QList<SnmpValue> result;

    MibOid anOID = MibOid::parse(oidStr);
    if (anOID.hasError()) {
        emit error(QString("%1: %2").arg(oidStr, anOID.errString()));
        return result;
    }

    if (!open()) {
        emit error(m_ErrorStr);
        return result;
    }

    bool curRow     = true;
    bool firstValue = true;

    while(curRow) {

        SnmpPdu pdu = SnmpPdu::create(SnmpPduGetNext, anOID);
        SnmpPdu response = this->synchResponse(pdu);

        if (response.status == SnmpRespStatSuccess) {
            if (response.errStat() == SNMP_ERR_NOERROR) {
                for(SnmpVar var = response.variables(); var.isValid(); var = var.nextVariable()) {
                    if (firstValue) {
                        firstValue = false;
                    } else { // end of the table criteria
                        MibOid varOid = var.mibOid();
                        if (anOID.length != varOid.length) {
                            curRow = false;
                        } else { // end of the row criteria
                            for (size_t i=0; i<varOid.length-1; ++i) {
                                if (anOID.numOid[i] != varOid.numOid[i]) {
                                    curRow = false;
                                    break;
                                }
                            }
                        }
                    }
                    if (curRow) {
                        anOID = var.mibOid();
                        SnmpValue snmpValue = SnmpValue::fromVar(var);
                        result.append(snmpValue);
                    }
                }
            } else {
                emit error(QString("Error in packet\nReason: %1").arg(
                                    response.errorString()));
                curRow = false;
            }
        } else if (response.status == SnmpRespStatTimeout) {
            emit error(QString("Timeout: No Response from %1.").arg(m_DestHost));
            curRow = false; // break;
        } else { // status == SnmpRespStatError
            emit error(errorStr());
            curRow = false; // break;
        }

        response.cleanup();
    }

    return result;
}

/*****************************************************************/

SnmpValue NetSnmpSession::set(const QString &oidStr, const QVariant &oidValue)
{
    SnmpValue result;

    MibOid anOID = MibOid::parse(oidStr);
    if (anOID.hasError()) {
        emit error(QString("%1: %2").arg(oidStr, anOID.errString()));
        return result;
    }

    MibNode mibNode = MibNode::findByOid(anOID);
    if (!mibNode.isValid()) {
        emit error(QString("Can not get MibTree for %1").arg(oidStr));
        return result;
    }

    char dataType = mibNode.typeChar();

    SnmpPdu pdu = SnmpPdu::create(SnmpPduSet);
    int xerr = pdu.addVar(anOID, dataType, oidValue.toString());
    if (xerr) {
        emit error(NetSNMP::apiErrstring(xerr));
        pdu.cleanup();
        return result;
    }

    if (!open()) {
        emit error(m_ErrorStr);
        return result;
    }

    SnmpPdu response = this->synchResponse(pdu);

    if (response.status == SnmpRespStatSuccess) {
        if (response.errStat() == SNMP_ERR_NOERROR) {
            for(SnmpVar var = response.variables(); var.isValid(); var = var.nextVariable()) {
                result = SnmpValue::fromVar(var);
            }
        } else {
            QString errString
                    = QString("Error in packet\nReason: %1\n").arg(response.errorString());
            SnmpVar errVar = response.failedObject();
            if (errVar.isValid()) {
                errString.append(QString("Failed object: %1\n").arg(errVar.mibOid().toString()));
            }
            emit error(errString);
        }
    } else if (response.status == SnmpRespStatTimeout) {
        emit error(QString("Timeout: No Response from %1.").arg(m_DestHost));
    } else { // status == SnmpRespStatError
        emit error(errorStr());
    }

    response.cleanup();

    return result;
}

/*****************************************************************/

QList<QList<SnmpValue> > NetSnmpSession::getTable(const QString &oidStr, const QVariantMap &options)
{
    QList<QList<SnmpValue>> result;

    MibOid rootOID = MibOid::parse(oidStr);
    if (rootOID.hasError()) {
        emit error(QString("%1: %2").arg(oidStr, rootOID.errString()));
        return result;
    }
    // read options



    // TODO NetSnmpSession::getTable()
    return result;
}

/*****************************************************************/

QString NetSnmpSession::errorStr()
{
    if (!m_SessPtr) {
        return m_ErrorStr;
    }
    char *err;
    snmp_error(m_SessPtr, nullptr, nullptr, &err);
    QString result(err);
    SNMP_FREE(err);
    return result;
}

/*****************************************************************/

SnmpValue NetSnmpSession::errorValue(const MibOid &anOid, const SnmpPdu &pdu)
{
    SnmpValue result;
    if (pdu.status == SnmpRespStatSuccess) {
        result = SnmpValue::fromError(anOid, pdu.errorString());
    } else if (pdu.status == SnmpRespStatTimeout) {
        result = SnmpValue::fromError(anOid, QString("Timeout: No Response from %1.").arg(m_DestHost));
    } else { /* status == SnmpRespStatError */
        result = SnmpValue::fromError(anOid, errorStr());
    }
    return result;
}

/*****************************************************************/

void NetSnmpSession::setProfile(const SnmpProfile &profile)
{
    setVersion(profile.version);
    setCommunity(profile.community);

    if (profile.version == SNMPv3) {
        //! TODO fields for SNMPv3
    }
}

/*****************************************************************/

QList<MibNode> NetSnmpSession::readColumns(const QString &oidStr)
{
    MibOid anOID = MibOid::parse(oidStr);
    if (anOID.hasError()) {
        emit error(QString("%1: %2").arg(oidStr, anOID.errString()));
        return QList<MibNode>();
    }

    MibNode mibNode = MibNode::findByOid(anOID);
    return mibNode.tableColumns();
}

/*****************************************************************/

QList<QList<SnmpValue> > NetSnmpSession::getTableEntries(const QList<MibNode> &columns, const QVariantMap &options)
{
    QList<QList<SDPO::SnmpValue>> result;

    if (columns.isEmpty()) {
        emit error("No columns - not a table");
        return result;
    }

    MibOid rootOid = columns.last().parent().mibOid();
    oid      name[MAX_OID_LEN];
    size_t   namelen = rootOid.length + 1;
    for (size_t i=0; i<rootOid.length; ++i) {
        name[i] = rootOid.numOid[i];
    }

    // Initialize a "session" that defines who we're going to talk to
    if (!open()) {
        emit error(errorStr());
        return result;
    }

    bool running = true;
    int entries = 0;
    const int MaxEntries = 20;
    // while (!end of table) {
    while (running && (entries < MaxEntries)) {

        // create pdu with column ids
        snmp_pdu *pdu = snmp_pdu_create(SNMP_MSG_GETNEXT);
        for (int i = 0; i < columns.size(); i++) {
            name[rootOid.length] = columns.at(i).subID();
            snmp_add_null_var(pdu, name, namelen);
        }

        snmp_pdu *pduResponse = nullptr;
        SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(m_SessPtr, pdu, &pduResponse));

        if (status == SnmpRespStatSuccess) {
            if (pduResponse->errstat == SNMP_ERR_NOERROR) {
                netsnmp_variable_list *vars = pduResponse->variables;
                if (!entries) {
                    namelen++;
                } else {
                    if ((namelen != vars->name_length) || (name[namelen-1] >= vars->name[namelen-1])) {
                        running = false;
                    }
                }
                if (running) {
                    name[namelen-1] = vars->name[namelen-1];
                    entries++;
                    QList<SDPO::SnmpValue> entry;
                    for(; vars != nullptr; vars = vars->next_variable) {
                        entry.append(SnmpValue::fromVar(vars));
                    }
                    result.append(entry);
                }
            } else if (pduResponse->errstat == SNMP_ERR_NOSUCHNAME) {
                running = false; // end of table
            } else {
                emit error(snmp_errstring(static_cast<int>(pduResponse->errstat)));
                running = false;
            }
        } else if (status == SnmpRespStatTimeout) {
            emit error(QString("Timeout: No Response from %1.").arg(destHost()));
            running = false;
        } else { // status == SnmpRespStatError
            emit error(errorStr());
            running = false;
        }

        if (pduResponse) {
          snmp_free_pdu(pduResponse);
        }
    }

    return result;
}

/*****************************************************************/
