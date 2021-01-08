#include "netsnmpsession.h"

#include <QDebug>

using namespace SDPO;

/*****************************************************************/

NetSnmpSession::NetSnmpSession(QObject *parent)
    : QObject(parent),
      m_SessPtr    (nullptr),
      m_DestHost   (DEST_HOST_DEFAULT),
      m_Community  (COMMUNITY_DEFAULT),
      m_Version    (SnmpVersion::SNMPvDefault),
      m_RemotePort (SnmpDefaults::SnmpPort),
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
    m_RemotePort = map.value(NET_SNMP_SESSION_REMOTEPORT, SnmpDefaults::SnmpPort).toInt();
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
    if (m_SessPtr) { // already opened
        return true;
    }

    // Initialize a "session" that defines who we're going to talk to
    netsnmp_session session;
    snmp_sess_init(&session); // setup defaults
    session.peername      = m_DestHost.toLatin1().data();
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
}

/*****************************************************************/

SnmpValue NetSnmpSession::get(const QString &oidStr)
{
    MibOid anOID = MibOid::parse(oidStr);
    if (anOID.hasError()) {
        return SnmpValue::fromError(anOID, anOID.errString());
    }

    if (!open()) {
        return SnmpValue::fromError(anOID, m_ErrorStr);
    }

    return get(anOID);
}

/*****************************************************************/

SnmpValue NetSnmpSession::get(const MibOid &anOID)
{
    SnmpPdu *pdu = snmp_pdu_create(SnmpPduGet);
    snmp_add_null_var(pdu, anOID.oidNum, anOID.oidLen);

    SnmpValue result;
    SnmpPdu  *pduResponse = nullptr;

    SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(m_SessPtr, pdu, &pduResponse));

    if (status == SnmpRespStatSuccess) {
        if (pduResponse->errstat == SNMP_ERR_NOERROR) {
            for(SnmpVariableList *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
                result = SnmpValue::fromVar(vars);
            }
        } else {
            result = SnmpValue::fromError(anOID, snmp_errstring(static_cast<int>(pduResponse->errstat)));
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

QList<SnmpValue> NetSnmpSession::get(const QVariantMap &map)
{
    // TODO implement me
    return QList<SnmpValue>();
}

/*****************************************************************/

QList<SnmpValue> NetSnmpSession::getNext(const QString &oidStr, int cnt)
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


    for(int i=0;i<cnt;i++) {

        SnmpPdu *pdu = snmp_pdu_create(SnmpPduGetNext);
        snmp_add_null_var(pdu, anOID.oidNum, anOID.oidLen);

        SnmpPdu *pduResponse = nullptr;
        SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(m_SessPtr, pdu, &pduResponse));

        if (status == SnmpRespStatSuccess) {
            if (pduResponse->errstat == SNMP_ERR_NOERROR) {
                for(netsnmp_variable_list *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
                    SnmpValue snmpValue = SnmpValue::fromVar(vars);
                    result.append(snmpValue);
                    anOID = snmpValue.name;
                }
            } else {
                result.append(SnmpValue::fromError(anOID, snmp_errstring(static_cast<int>(pduResponse->errstat))));
            }
        } else if (status == SnmpRespStatTimeout) {
            result.append(SnmpValue::fromError(anOID, QString("Timeout: No Response from %1.").arg(m_DestHost)));
        } else {                    /* status == SnmpRespStatError */
            result.append(SnmpValue::fromError(anOID, errorStr()));
        }

        if (pduResponse) {
          snmp_free_pdu(pduResponse);
        }
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

        SnmpPdu *pdu = snmp_pdu_create(SnmpPduGetNext);
        snmp_add_null_var(pdu, anOID.oidNum, anOID.oidLen);

        SnmpPdu *pduResponse = nullptr;
        SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(m_SessPtr, pdu, &pduResponse));

        if (status == SnmpRespStatSuccess) {
            if (pduResponse->errstat == SNMP_ERR_NOERROR) {
                for(netsnmp_variable_list *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
                    if (firstValue) {
                        firstValue = false;
                        anOID = MibOid(vars->name, vars->name_length);
                    } else { // end of the table criteria
                        if (anOID.oidLen != vars->name_length) {
                            curRow = false;
                        } else { // end of the row criteria
                            for (size_t i=0; i<vars->name_length-1; ++i) {
                                if (anOID.oidNum[i] != vars->name[i]) {
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

    SnmpPdu *pdu = snmp_pdu_create(SnmpPduSet);
    int xerr = snmp_add_var(pdu, anOID.oidNum, anOID.oidLen, dataType, oidValue.toString().toLatin1());
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
    SnmpPdu  *pduResponse = nullptr;
    SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(m_SessPtr, pdu, &pduResponse));

    if (status == SnmpRespStatSuccess) {
        if (pduResponse->errstat == SNMP_ERR_NOERROR) {
            for(SnmpVariableList *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
                result = SnmpValue::fromVar(vars);
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

void NetSnmpSession::setProfile(const SnmpProfile &profile)
{
    m_Version   = profile.version;
    m_Community = profile.community;

    if (profile.version == SNMPv3) {
        //! TODO fields for SNMPv3
    }
}

/*****************************************************************/

void NetSnmpSession::snmpSessionInit(SnmpSession *session)
{
    snmp_sess_init(session); // setup defaults
    session->peername      = m_DestHost.toLatin1().data();
    session->version       = static_cast<long>(m_Version);
    session->community     = reinterpret_cast<u_char*>(m_Community.toLocal8Bit().data());
    session->community_len = static_cast<size_t>(m_Community.size());
    session->retries       = m_Retries;
}

/*****************************************************************/

QString NetSnmpSession::snmpSessionLogError(int priority, const QString &prog, SnmpSession *ss)
{
    Q_UNUSED(priority)
    char *err;
    snmp_error(ss, nullptr, nullptr, &err);
    QString result(err);
    qDebug() << prog << ": " << err;
//    snmp_log(priority, "%s: %s\n", static_cast<const char *>(prog.toLatin1()), err);
    SNMP_FREE(err);
    return result;
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
