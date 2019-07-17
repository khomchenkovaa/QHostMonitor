#include "netsnmpget.h"

#include <QDebug>

/*****************************************************************/

SDPO::NetSnmpGet::NetSnmpGet(QObject *parent)
    : QObject(parent),
      m_Timeout(2000),
      m_Retries(1)
{
    init_snmp("SDPO");
}

/*****************************************************************/

SDPO::NetSnmpGet::~NetSnmpGet()
{
}

/*****************************************************************/

void SDPO::NetSnmpGet::setHost(const QString &host)
{
    m_Host = host;
}

/*****************************************************************/

void SDPO::NetSnmpGet::setProfile(const SDPO::SnmpProfile &profile)
{
    m_Version   = profile.version;
    m_Community = profile.community;

    if (profile.version == SNMPv3) {
        //! TODO fields for SNMPv3
    }

}

/*****************************************************************/

void SDPO::NetSnmpGet::setTimeout(const int timeout)
{
    m_Timeout = timeout;
}

/*****************************************************************/

void SDPO::NetSnmpGet::setRetries(const int retries)
{
    m_Retries = retries;
}

/*****************************************************************/

SDPO::SnmpValue SDPO::NetSnmpGet::get(const QString& oidStr)
{
    SDPO::SnmpValue result;

    // Initialize a "session" that defines who we're going to talk to
    SnmpSession session;
    snmp_sess_init( &session ); // setup defaults
    snmpSessionInit( &session );

    SOCK_STARTUP;
    SnmpSession *ss = snmp_open(&session); // establish the session
    if (!ss) {
        snmpSessionLogError(LOG_ERR, "ack", &session);
        SOCK_CLEANUP;
        return result;
    }

    SnmpPdu *pdu = snmp_pdu_create(SnmpPduGet);
    oid      anOID[MAX_OID_LEN];
    size_t   anOID_len = MAX_OID_LEN;

    if (!snmp_parse_oid(oidStr.toLatin1(), anOID, &anOID_len)) {
        int xerr = snmp_errno;
        const char *str = snmp_api_errstring(xerr);
        qDebug() << oidStr << ": " << str;
//        snmp_log(LOG_ERR, "%s: %s\n", static_cast<const char *>(oidStr.toLatin1()), str);
        snmp_close(ss);
        SOCK_CLEANUP;
        return result;
    }
    snmp_add_null_var(pdu, anOID, anOID_len);

    SnmpPdu    *pduResponse = nullptr;
    SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(ss, pdu, &pduResponse));

    if (status == SnmpRespStatSuccess) {
        if (pduResponse->errstat == SNMP_ERR_NOERROR) {
            for(SnmpVariableList *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
                result = NetSNMP::valueFrom(vars);
            }
        } else {
            result.val = snmp_errstring(static_cast<int>(pduResponse->errstat));
        }
    } else if (status == SnmpRespStatTimeout) {
        result.val = QString("Timeout: No Response from %1.").arg(session.peername);
    } else {                    /* status == SnmpRespStatError */
        result.val = QString("Error in Response from %1.").arg(session.peername);
        snmpSessionLogError(LOG_ERR, "GET", &session);
    }

    // Cleanup
    if (pduResponse) {
      snmp_free_pdu(pduResponse);
    }
    snmp_close(ss);
    SOCK_CLEANUP;

    return result;
}

/*****************************************************************/

QList<SDPO::SnmpValue> SDPO::NetSnmpGet::getNext(const QString &oidStr, int cnt)
{
    QList<SDPO::SnmpValue> result;

    // Initialize a "session" that defines who we're going to talk to
    SnmpSession session;
    snmp_sess_init( &session ); // setup defaults
    snmpSessionInit( &session );

    SOCK_STARTUP;
    SnmpSession *ss = snmp_open(&session); // establish the session
    if (!ss) {
        snmpSessionLogError(LOG_ERR, "ack", &session);
        SOCK_CLEANUP;
        return result;
    }

    oid    anOID[MAX_OID_LEN];
    size_t anOID_len = MAX_OID_LEN;
    if (!snmp_parse_oid(oidStr.toLatin1(), anOID, &anOID_len)) {
        int xerr = snmp_errno;
        const char *str = snmp_api_errstring(xerr);
        qDebug() << oidStr << ": " << str;
//        snmp_log(LOG_ERR, "%s: %s\n", static_cast<const char *>(oidStr.toLatin1()), str);
        snmp_close(ss);
        SOCK_CLEANUP;
        return result;
    }

    for(int i=0;i<cnt;i++) {

        SnmpPdu *pdu = snmp_pdu_create(SnmpPduGetNext);
        snmp_add_null_var(pdu, anOID, anOID_len);

        SnmpPdu *pduResponse = nullptr;
        SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(ss, pdu, &pduResponse));

        if (status == SnmpRespStatSuccess) {
            if (pduResponse->errstat == SNMP_ERR_NOERROR) {
                for(netsnmp_variable_list *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
                    result.append(NetSNMP::valueFrom(vars));
                    for (size_t j=0; j<vars->name_length; ++j) {
                        anOID[j] = vars->name[j];
                    }
                    anOID_len = vars->name_length;
                }
            } else {
                qDebug() << snmp_errstring(static_cast<int>(pduResponse->errstat));
            }
        } else if (status == SnmpRespStatTimeout) {
            qDebug() << QString("Timeout: No Response from %1.").arg(session.peername);
        } else {                    /* status == SnmpRespStatError */
            qDebug() << QString("Error in Response from %1.").arg(session.peername);
            snmpSessionLogError(LOG_ERR, "GETNEXT", &session);
        }

        if (pduResponse) {
          snmp_free_pdu(pduResponse);
        }
    }

    snmp_close(ss);
    SOCK_CLEANUP;

    return result;
}

/*****************************************************************/

QList<SDPO::SnmpValue> SDPO::NetSnmpGet::getRow(const QString &oidStr)
{
    QList<SDPO::SnmpValue> result;

    // Initialize a "session" that defines who we're going to talk to
    SnmpSession session;
    snmp_sess_init( &session ); // setup defaults
    snmpSessionInit( &session );

    SOCK_STARTUP;
    SnmpSession *ss = snmp_open(&session); // establish the session
    if (!ss) {
        snmpSessionLogError(LOG_ERR, "ack", &session);
        SOCK_CLEANUP;
        return result;
    }

    oid    anOID[MAX_OID_LEN];
    size_t anOID_len = MAX_OID_LEN;
    if (!snmp_parse_oid(oidStr.toLatin1(), anOID, &anOID_len)) {
        int xerr = snmp_errno;
        const char *str = snmp_api_errstring(xerr);
        qDebug() << oidStr << ": " << str;
//        snmp_log(LOG_ERR, "%s: %s\n", static_cast<const char *>(oidStr.toLatin1()), str);
        snmp_close(ss);
        SOCK_CLEANUP;
        return result;
    }

    bool curRow     = true;
    bool firstValue = true;

    while(curRow) {

        SnmpPdu *pdu = snmp_pdu_create(SnmpPduGetNext);
        snmp_add_null_var(pdu, anOID, anOID_len);

        SnmpPdu *pduResponse = nullptr;
        SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(ss, pdu, &pduResponse));

        if (status == SnmpRespStatSuccess) {
            if (pduResponse->errstat == SNMP_ERR_NOERROR) {
                for(netsnmp_variable_list *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
                    if (firstValue) {
                        firstValue = false;
                        for (size_t j=0; j<vars->name_length; ++j) {
                            anOID[j] = vars->name[j];
                        }
                        anOID_len = vars->name_length;
                    } else { // end of the row criteria
                        if (anOID_len != vars->name_length) {
                            curRow = false;
                        } else {
                            for (size_t i=0; i<vars->name_length-1; ++i) {
                                if (anOID[i] != vars->name[i]) {
                                    curRow = false;
                                    break;
                                }
                            }
                        }
                    }
                    if (curRow) {
                        result.append(NetSNMP::valueFrom(vars));
                        for (size_t j=0; j<vars->name_length; ++j) {
                            anOID[j] = vars->name[j];
                        }
                        anOID_len = vars->name_length;
                    }
                }
            } else {
                qDebug() << snmp_errstring(static_cast<int>(pduResponse->errstat));
            }
        } else if (status == SnmpRespStatTimeout) {
            qDebug() << QString("Timeout: No Response from %1.").arg(session.peername);
            curRow = false; // break;
        } else {                    /* status == SnmpRespStatError */
            qDebug() << QString("Error in Response from %1.").arg(session.peername);
            snmpSessionLogError(LOG_ERR, "GETROW", &session);
            curRow = false; // break;
        }

        if (pduResponse) {
          snmp_free_pdu(pduResponse);
        }
    }

    snmp_close(ss);
    SOCK_CLEANUP;

    return result;
}

/*****************************************************************/

void SDPO::NetSnmpGet::snmpSessionInit(SnmpSession *session)
{
    session->peername = strdup(m_Host.toLatin1());
    session->version = static_cast<long>(m_Version);
    session->community = reinterpret_cast<u_char*>(m_Community.toLocal8Bit().data());
    session->community_len = static_cast<size_t>(m_Community.size());
    session->retries = m_Retries;
}

/*****************************************************************/

void SDPO::NetSnmpGet::snmpSessionLogError(int priority, const QString &prog, SDPO::SnmpSession *ss)
{
    char *err;
    snmp_error(ss, nullptr, nullptr, &err);
    qDebug() << prog << ": " << err;
    Q_UNUSED(priority)
//    snmp_log(priority, "%s: %s\n", static_cast<const char *>(prog.toLatin1()), err);
    SNMP_FREE(err);
}

/*****************************************************************/
