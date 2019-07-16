#include "netsnmpget.h"

#include <QDebug>

/*****************************************************************/

SDPO::NetSnmpGet::NetSnmpGet(QObject *parent)
    : QObject(parent),
      ss(nullptr)
{
    snmp_sess_init( &session );
}

/*****************************************************************/

SDPO::NetSnmpGet::~NetSnmpGet()
{
    if (ss) {
        snmp_close(ss);
    }
}

/*****************************************************************/

void SDPO::NetSnmpGet::setPeername(const QString &host)
{
    session.peername = strdup(host.toLatin1());
}

/*****************************************************************/

void SDPO::NetSnmpGet::setVersion(SnmpVersion version)
{
    session.version = static_cast<long>(version);
}

/*****************************************************************/

void SDPO::NetSnmpGet::setCommunity(const QString &community)
{
    session.community = reinterpret_cast<u_char*>(community.toLocal8Bit().data());
    session.community_len = static_cast<size_t>(community.size());
}

/*****************************************************************/

void SDPO::NetSnmpGet::setTimeout(const int timeout)
{
    Q_UNUSED(timeout)
    // TODO set session.timeout
}

/*****************************************************************/

void SDPO::NetSnmpGet::setRetries(const int retries)
{
    session.retries = retries;
}

/*****************************************************************/

SDPO::SnmpValue SDPO::NetSnmpGet::get(const QString& oidStr)
{
    SDPO::SnmpValue result;

    ss = snmp_open(&session);                     /* establish the session */

    if (!ss) {
      return result;
    }

    SnmpPdu *pdu = snmp_pdu_create(SnmpPduGet);
    oid anOID[MAX_OID_LEN];
    size_t anOID_len = MAX_OID_LEN;

    if (!snmp_parse_oid(oidStr.toLatin1(), anOID, &anOID_len)) {
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
    }

    if (pduResponse) {
      snmp_free_pdu(pduResponse);
    }

    /* endif -- SnmpRespStatSuccess */
    return result;
}

/*****************************************************************/

QList<SDPO::SnmpValue> SDPO::NetSnmpGet::getNext(const QString &oidStr, int cnt)
{
    QList<SDPO::SnmpValue> result;

    ss = snmp_open(&session);                     /* establish the session */

    if (!ss) {
      return result;
    }

    oid anOID[MAX_OID_LEN];
    size_t anOID_len = MAX_OID_LEN;
    if (!snmp_parse_oid(oidStr.toLatin1(), anOID, &anOID_len)) {
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
        }

        if (pduResponse) {
          snmp_free_pdu(pduResponse);
        }
    }

    return result;
}

/*****************************************************************/

QList<SDPO::SnmpValue> SDPO::NetSnmpGet::getRow(const QString &oidStr)
{
    QList<SDPO::SnmpValue> result;

    ss = snmp_open(&session);                     /* establish the session */

    if (!ss) {
      return result;
    }

    oid anOID[MAX_OID_LEN];
    size_t anOID_len = MAX_OID_LEN;
    if (!snmp_parse_oid(oidStr.toLatin1(), anOID, &anOID_len)) {
      return result;
    }

    bool curRow = true;

    while(curRow) {

        SnmpPdu *pdu = snmp_pdu_create(SnmpPduGetNext);
        snmp_add_null_var(pdu, anOID, anOID_len);

        SnmpPdu *pduResponse = nullptr;
        SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(ss, pdu, &pduResponse));

        if (status == SnmpRespStatSuccess) {
            if (pduResponse->errstat == SNMP_ERR_NOERROR) {
                for(netsnmp_variable_list *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
                    //! TODO end of the row criteria
                    for (size_t i=0; i<anOID_len && i<vars->name_length-1; ++i) {
                        if (anOID[i] != vars->name[i]) {
                            curRow = false;
                            break;
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
        } else {                    /* status == SnmpRespStatError */
            qDebug() << QString("Error in Response from %1.").arg(session.peername);
        }

        if (pduResponse) {
          snmp_free_pdu(pduResponse);
        }
    }

    return result;
}

/*****************************************************************/
