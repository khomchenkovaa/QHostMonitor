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
    SnmpPdu pduResponse;

    bool retry = false;

    do {
        retry = false;
        pduResponse = this->synchResponse(pdu);

        if (pduResponse.status == SnmpRespStatSuccess) {
            if (pduResponse.errStat() == SNMP_ERR_NOERROR) {
                for(SnmpVar var = pduResponse.variables(); var.isValid(); var = var.nextVariable()) {
                    result.append(SnmpValue::fromVar(var));
                }
            } else {
                QString errString
                        = QString("Error in packet\nReason: %1\n").arg(pduResponse.errorString());
                SnmpVar errVar = pduResponse.failedObject();
                if (errVar.isValid()) {
                    errString.append(QString("Failed object: %1\n").arg(errVar.mibOid().toString()));
                }
                emit error(errString);

                if (m_FixPdu) {
                    pdu = pduResponse.fix(SnmpPduGet);
                    pduResponse.cleanup();
                    retry = pdu.isValid();
                }
            }


        } else if (pdu.status == SnmpRespStatTimeout) {
            emit error(QString("Timeout: No Response from %1.").arg(m_DestHost));
        } else { /* status == SnmpRespStatError */
            emit error(errorStr());
        }

    } while (retry);

    pduResponse.cleanup();

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
        SnmpPdu pduResponse = this->synchResponse(pdu);

        if (pduResponse.status == SnmpRespStatSuccess) {
            if (pduResponse.errStat() == SNMP_ERR_NOERROR) {
                for(SnmpVar var = pduResponse.variables(); var.isValid(); var = var.nextVariable()) {
                    anOid = var.mibOid();
                    SnmpValue snmpValue = SnmpValue::fromVar(var);
                    result.append(snmpValue);
                }
            } else {
                emit error(QString("Error in packet\nReason: %1").arg(
                                    pduResponse.errorString()));
                break;
            }
        } else if (pdu.status == SnmpRespStatTimeout) {
            emit error(QString("Timeout: No Response from %1.").arg(m_DestHost));
            break;
        } else { /* status == SnmpRespStatError */
            emit error(errorStr());
            break;
        }

        pduResponse.cleanup();
    }

    return result;
}

/*****************************************************************/

QList<SnmpValue> NetSnmpSession::getRow(const QString &oidStr)
{
    QList<SnmpValue> result;

    MibOid anOID = MibOid::parse(oidStr);
    if (anOID.hasError()) {
        result.append(SnmpValue::fromError(anOID, anOID.errString()));
        return result;
    }

    if (!open()) {
        result.append(SnmpValue::fromError(anOID, m_ErrorStr));
        return result;
    }

    bool curRow     = true;
    bool firstValue = true;

    while(curRow) {

        snmp_pdu *pdu = snmp_pdu_create(SnmpPduGetNext);
        snmp_add_null_var(pdu, anOID.numOid, anOID.length);

        snmp_pdu *pduResponse = nullptr;
        SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(m_SessPtr, pdu, &pduResponse));

        if (status == SnmpRespStatSuccess) {
            if (pduResponse->errstat == SNMP_ERR_NOERROR) {
                for(netsnmp_variable_list *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
                    if (firstValue) {
                        firstValue = false;
                        anOID = MibOid(vars->name, vars->name_length);
                    } else { // end of the table criteria
                        if (anOID.length != vars->name_length) {
                            curRow = false;
                        } else { // end of the row criteria
                            for (size_t i=0; i<vars->name_length-1; ++i) {
                                if (anOID.numOid[i] != vars->name[i]) {
                                    curRow = false;
                                    break;
                                }
                            }
                        }
                    }
                    if (curRow) {
                        SnmpValue snmpValue = SnmpValue::fromVar(vars);
                        result.append(snmpValue);
                        anOID = snmpValue.name;
                    }
                }
            } else {
                result.append(SnmpValue::fromError(anOID, snmp_errstring(static_cast<int>(pduResponse->errstat))));
                curRow = false;
            }
        } else if (status == SnmpRespStatTimeout) {
            result.append(SnmpValue::fromError(anOID, QString("Timeout: No Response from %1.").arg(m_DestHost)));
            curRow = false; // break;
        } else {                    /* status == SnmpRespStatError */
            result.append(SnmpValue::fromError(anOID, errorStr()));
            curRow = false; // break;
        }

        if (pduResponse) {
          snmp_free_pdu(pduResponse);
        }
    }

    return result;
}

/*****************************************************************/

SnmpValue NetSnmpSession::set(const QString &oidStr, const QVariant &oidValue)
{
    MibOid anOID = MibOid::parse(oidStr);
    if (anOID.hasError()) {
        return SnmpValue::fromError(anOID, anOID.errString());
    }

    MibNode mibNode = MibNode::findByOid(anOID);
    if (!mibNode.isValid()) {
        return SnmpValue::fromError(anOID, QString("Can not get MibTree for %1").arg(oidStr));
    }

    char dataType = mibNode.typeChar();

    snmp_pdu *pdu = snmp_pdu_create(SnmpPduSet);
    int xerr = snmp_add_var(pdu, anOID.numOid, anOID.length, dataType, oidValue.toString().toLatin1());
    if (xerr) {
        QString serr = QString(snmp_api_errstring(xerr));
        if (pdu) {
          snmp_free_pdu(pdu);
        }
        return SnmpValue::fromError(anOID, serr);
    }

    putenv(QString("POSIXLY_CORRECT=1").toLatin1().data());

    if (!open()) {
        return SnmpValue::fromError(anOID, m_ErrorStr);
    }

    SnmpValue result;
    snmp_pdu  *pduResponse = nullptr;
    SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(m_SessPtr, pdu, &pduResponse));

    if (status == SnmpRespStatSuccess) {
        if (pduResponse->errstat == SNMP_ERR_NOERROR) {
            for(SnmpVar var = pduResponse->variables; var.isValid(); var = var.nextVariable()) {
                result = SnmpValue::fromVar(var);
            }
        } else {
            result.val = snmp_errstring(static_cast<int>(pduResponse->errstat));
        }
    } else if (status == SnmpRespStatTimeout) {
        result = SnmpValue::fromError(anOID, QString("Timeout: No Response from %1.").arg(m_DestHost));
    } else {                    /* status == SnmpRespStatError */
        result = SnmpValue::fromError(anOID, errorStr());
    }

    // Cleanup
    if (pduResponse) {
      snmp_free_pdu(pduResponse);
    }

    return result;
}

/*****************************************************************/

QList<QList<SnmpValue> > NetSnmpSession::getTable()
{
    // TODO NetSnmpSession::getTable()
    return QList<QList<SnmpValue>>();
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

QList<SnmpColumn *> NetSnmpSession::readColumns(const QString &oidStr)
{
    QList<SnmpColumn*> result;

    MibOid anOID = MibOid::parse(oidStr);
    if (anOID.hasError()) {
        return result;
    }

    MibNode mibNode = MibNode::findByOid(anOID);
    if (mibNode.isValid()) { // get table entry
        mibNode = mibNode.childList();
    }
    if (!mibNode.isValid()) { // no entry - not a table
        return result;
    }

    // TODO NetSnmpSession::readColumns()

    return result;
}

/*****************************************************************/
