#include "netsnmpget.h"

#include <QDebug>

using namespace SDPO;

/*****************************************************************/

NetSnmpGet::NetSnmpGet(QObject *parent)
    : NetSnmpCommon(parent)
{
}

/*****************************************************************/

NetSnmpGet::~NetSnmpGet()
{
}

/*****************************************************************/

SnmpValue NetSnmpGet::get(const QString& oidStr)
{
    SnmpValue result;

    MibOid anOID = MibOid::parse(oidStr);
    result.setName(anOID);

    if (anOID.hasError()) {
        return SnmpValue::fromError(anOID, anOID.errString());
    }

    // Initialize a "session" that defines who we're going to talk to
    SnmpSession session;
    snmpSessionInit( &session );

    SnmpPdu *pdu = snmp_pdu_create(SnmpPduGet);
    snmp_add_null_var(pdu, anOID.oidNum, anOID.oidLen);

    SOCK_STARTUP;
    SnmpSession *ss = snmp_open(&session); // establish the session
    if (!ss) {
        QString err = snmpSessionLogError(LOG_ERR, "netsnmpget", &session);
        SOCK_CLEANUP;
        return SnmpValue::fromError(anOID, err);
    }

    SnmpPdu *pduResponse = nullptr;
    SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(ss, pdu, &pduResponse));

    if (status == SnmpRespStatSuccess) {
        if (pduResponse->errstat == SNMP_ERR_NOERROR) {
            for(SnmpVariableList *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
                result = SnmpValue::fromVar(vars);
            }
        } else {
            result = SnmpValue::fromError(anOID, snmp_errstring(static_cast<int>(pduResponse->errstat)));
        }
    } else if (status == SnmpRespStatTimeout) {
        result = SnmpValue::fromError(anOID, QString("Timeout: No Response from %1.").arg(session.peername));
    } else {                    /* status == SnmpRespStatError */
        QString err = snmpSessionLogError(LOG_ERR, "netsnmpget", ss);
        result = SnmpValue::fromError(anOID, err);
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

QList<SnmpValue> NetSnmpGet::getNext(const QString &oidStr, int cnt)
{
    QList<SnmpValue> result;

    MibOid anOID = MibOid::parse(oidStr);
    if (anOID.hasError()) {
        result.append(SnmpValue::fromError(anOID, anOID.errString()));
        return result;
    }

    // Initialize a "session" that defines who we're going to talk to
    SnmpSession session;   
    snmpSessionInit( &session );

    SOCK_STARTUP;
    SnmpSession *ss = snmp_open(&session); // establish the session
    if (!ss) {
        snmpSessionLogError(LOG_ERR, "ack", &session);
        SOCK_CLEANUP;
        result.append(SnmpValue::fromError(anOID, "Cannot open the session"));
        return result;
    }

    for(int i=0;i<cnt;i++) {

        SnmpPdu *pdu = snmp_pdu_create(SnmpPduGetNext);
        snmp_add_null_var(pdu, anOID.oidNum, anOID.oidLen);

        SnmpPdu *pduResponse = nullptr;
        SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(ss, pdu, &pduResponse));

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
            result.append(SnmpValue::fromError(anOID, QString("Timeout: No Response from %1.").arg(session.peername)));
        } else {                    /* status == SnmpRespStatError */
            result.append(SnmpValue::fromError(anOID, QString("Error in Response from %1.").arg(session.peername)));
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

QList<SnmpValue> NetSnmpGet::getRow(const QString &oidStr)
{
    QList<SnmpValue> result;

    MibOid anOID = MibOid::parse(oidStr);
    if (anOID.hasError()) {
        result.append(SnmpValue::fromError(anOID, anOID.errString()));
        return result;
    }

    // Initialize a "session" that defines who we're going to talk to
    SnmpSession session;
    snmpSessionInit( &session );

    SOCK_STARTUP;
    SnmpSession *ss = snmp_open(&session); // establish the session
    if (!ss) {
        snmpSessionLogError(LOG_ERR, "ack", &session);
        SOCK_CLEANUP;
        result.append(SnmpValue::fromError(anOID, "Cannot open the session"));
        return result;
    }

    bool curRow     = true;
    bool firstValue = true;

    while(curRow) {

        SnmpPdu *pdu = snmp_pdu_create(SnmpPduGetNext);
        snmp_add_null_var(pdu, anOID.oidNum, anOID.oidLen);

        SnmpPdu *pduResponse = nullptr;
        SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(ss, pdu, &pduResponse));

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
            result.append(SnmpValue::fromError(anOID, QString("Timeout: No Response from %1.").arg(session.peername)));
            curRow = false; // break;
        } else {                    /* status == SnmpRespStatError */
            result.append(SnmpValue::fromError(anOID, QString("Error in Response from %1.").arg(session.peername)));
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
