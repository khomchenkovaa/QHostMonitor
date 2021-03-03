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
    NetSNMP::initSnmp();
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
    session.peername      = strdup(m_DestHost.toLocal8Bit().data());
    session.version       = static_cast<long>(m_Version);
    session.community     = reinterpret_cast<u_char*>(strdup(m_Community.toLocal8Bit().data()));
    session.community_len = static_cast<size_t>(m_Community.size());
    session.retries       = m_Retries;
    session.timeout       = m_Timeout;

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
        m_SessPtr = nullptr;
    }
    m_AddrString.clear();
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

SnmpValueList NetSnmpSession::get(const QList<MibOid>& oids)
{
    SnmpValueList result;

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

    bool running = true;

    while (running) {
        running = false;
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
                    running = pdu.isValid();
                }
            }

        } else if (response.status == SnmpRespStatTimeout) {
            emit error(QString("Timeout: No Response from %1.").arg(m_DestHost));
            m_Reopen = true;
        } else { // status == SnmpRespStatError
            emit error(errorStr());
        }

    }

    // fix session address
    SnmpTransport transport = snmp_sess_transport(snmp_sess_pointer(m_SessPtr));
    m_AddrString = transport.addrString(pdu);

    response.cleanup();

    return result;
}

/*****************************************************************/

SnmpValueList NetSnmpSession::get(const QStringList &oids)
{
    QList<MibOid> mibOids;
    foreach(const QString& oidStr, oids) {
        MibOid anOid = MibOid::parse(oidStr);
        if (anOid.hasError()) {
            emit error(QString("%1: %2").arg(oidStr, anOid.errString()));
            return SnmpValueList();
        }
        mibOids.append(anOid);
    }

    return get(mibOids);
}

/*****************************************************************/

SnmpValueList NetSnmpSession::get(const QVariantMap &map)
{
    QStringList oids = map.value(NET_SNMP_CMD_OIDS, QStringList()).toStringList();
    return get(oids);
}

/*****************************************************************/

SnmpValueList NetSnmpSession::getNext(const QList<MibOid> &oids)
{
    SnmpValueList result;

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

    SnmpPdu pdu = SnmpPdu::create(SnmpPduGetNext, oids);
    SnmpPdu response;

    bool running = true;

    while (running) {
        running = false;
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
                    pdu = response.fix(SnmpPduGetNext);
                    response.cleanup();
                    running = pdu.isValid();
                }
            }

        } else if (response.status == SnmpRespStatTimeout) {
            emit error(QString("Timeout: No Response from %1.").arg(m_DestHost));
            m_Reopen = true;
        } else { // status == SnmpRespStatError
            emit error(errorStr());
        }

    }

    response.cleanup();

    return result;
}

/*****************************************************************/

SnmpValueList NetSnmpSession::getRow(const QString &oidStr)
{
    SnmpValueList result;

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
            m_Reopen = true;
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
        m_Reopen = true;
    } else { // status == SnmpRespStatError
        emit error(errorStr());
    }

    response.cleanup();

    return result;
}

/*****************************************************************/

SnmpValueList NetSnmpSession::bulkGet(const QList<MibOid> &names, int nonRepeaters, int maxRepetitions)
{
    SnmpValueList result;

    if (names.isEmpty()) {
        emit error("Missing object names");
        return result;
    }

    if (!open()) {
        emit error(m_ErrorStr);
        return result;
    }

    SnmpPdu pdu = SnmpPdu::create(SnmpPduGetBulk);
    pdu.setNonRepeaters(nonRepeaters);
    pdu.setMaxRepetitions(maxRepetitions);
    foreach(const MibOid& name, names) {
        pdu.addNullVar(name);
    }

    SnmpPdu response = this->synchResponse(pdu);

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
        }
    } else if (response.status == SnmpRespStatTimeout) {
        emit error(QString("Timeout: No Response from %1.").arg(m_DestHost));
        m_Reopen = true;
    } else { // status == SnmpRespStatError
        emit error(errorStr());
    }

    response.cleanup();

    return result;
}

/*****************************************************************/

SnmpValueList NetSnmpSession::bulkWalk(const MibOid &rootOid, int nonRepeaters, int maxRepetitions, bool checkLexicographic, bool includeRequested)
{
    SnmpValueList result;

    if (!open()) {
        emit error(m_ErrorStr);
        return result;
    }

    if (includeRequested) {
        QList<MibOid> names;
        names.append(rootOid);
        result.append(this->get(names));
    }

    SnmpResponseStatus status = SnmpResponseStatus::SnmpRespStatUnknown;

    MibOid runOid = rootOid;
    bool running = true;
    while(running) {
        SnmpPdu pdu = SnmpPdu::create(SnmpPduGetBulk);
        pdu.setNonRepeaters(nonRepeaters);
        pdu.setMaxRepetitions(maxRepetitions);
        pdu.addNullVar(runOid);

        SnmpPdu response = this->synchResponse(pdu);
        status = response.status;

        if (status == SnmpRespStatSuccess) {
            if (response.errStat() == SNMP_ERR_NOERROR) {
                for(SnmpVar var = response.variables(); var.isValid(); var = var.nextVariable()) {
                    MibOid curOid = var.mibOid();
                    if (!curOid.isPartOfSubtree(rootOid)) {
                        // not part of this subtree
                        running = 0;
                        continue;
                    }
                    result.append(SnmpValue::fromVar(var));

                    if (!var.isExceptionValue()) {
                        if (checkLexicographic && runOid.compare(curOid) >= 0) {
                            QString errString("Error: OID not increasing: %1 >= %2");
                            emit error (errString.arg(runOid.toString(), curOid.toString()));
                            running = 0;
                        }
                        // Check if last variable, and if so, save for next request.
                        if (!var.nextVariable().isValid()) {
                            runOid = curOid;
                        }
                    } else {
                        // an exception value, so stop
                        running = 0;
                    }
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
        } else if (status == SnmpRespStatTimeout) {
            emit error(QString("Timeout: No Response from %1.").arg(m_DestHost));
            running = false;
            m_Reopen = true;
        } else { // status == SnmpRespStatError
            emit error(errorStr());
            running = false;
        }

        response.cleanup();
    }

    if (result.isEmpty() && status == STAT_SUCCESS) {
        // no printed successful results, which may mean we were pointed at an only existing instance.
        // Attempt a GET, just for get measure.
        QList<MibOid> names;
        names.append(rootOid);
        result.append(this->get(names));
    }
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

SnmpValueTable NetSnmpSession::getTableRows(const QList<MibOid> &columns)
{
    SnmpValueTable result;

    if (columns.isEmpty()) {
        emit error("No columns - not a table");
        return result;
    }

    QList<MibOid> oids;       // for iterations
    oids.append(columns);

    while (oids.size() == columns.size()) {
        SnmpValueList row = getNext(oids);
        if (row.size() < columns.size()) break;
        oids.clear();
        for (int i=0; i<columns.size(); ++i) {
            if (row.at(i).name.isPartOfSubtree(columns.at(i))) {
                oids.append(row.at(i).name);
            }
        }
        if (oids.size() == columns.size()) {
            result.append(row);
        }
    }

    return result;
}

/*****************************************************************/
