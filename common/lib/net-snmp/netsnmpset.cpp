#include "netsnmpset.h"

#include <QDebug>

/*****************************************************************/

SDPO::NetSnmpSet::NetSnmpSet(QObject *parent)
    : NetSnmpCommon(parent)
{
}

/*****************************************************************/

SDPO::NetSnmpSet::~NetSnmpSet()
{
}

/*****************************************************************/

SDPO::SnmpValue SDPO::NetSnmpSet::set(const QString &oidStr, const QString &oidValue)
{
    SDPO::SnmpValue result;

    oid      anOID[MAX_OID_LEN];
    size_t   anOID_len = MAX_OID_LEN;
    if (!snmp_parse_oid(oidStr.toLatin1(), anOID, &anOID_len)) {
        int xerr = snmp_errno;
        const char *str = snmp_api_errstring(xerr);
        qDebug() << oidStr << ": " << str;
        return result;
    }

    MibTree *tbl = get_tree(anOID, anOID_len, get_tree_head());
    if (!tbl) {
        qDebug() << "Can not get MibTree for" << oidStr;
        return result;
    }

    char dataType = '=';
    switch(static_cast<MibType>(tbl->type)) {
    case MibTypeObjId       : dataType = 'o'; break;
    case MibTypeOctetStr    : dataType = 's'; break;
    case MibTypeInteger     : dataType = 'i'; break;
    case MibTypeIpAddr      : dataType = 'a'; break;
    case MibTypeCounter     : dataType = 'c'; break;
    case MibTypeTimeTicks   : dataType = 't'; break;
    case MibTypeCounter64   : dataType = 'C'; break;
    case MibTypeBitString   : dataType = 'b'; break;
    case MibTypeUInteger    : dataType = 'u'; break;
    case MibTypeUnsigned32  : dataType = 'u'; break;
    case MibTypeInteger32   : dataType = 'i'; break;
    default: break;
    }

    // Initialize a "session" that defines who we're going to talk to
    SnmpSession session;
    snmpSessionInit( &session );

    SnmpPdu *pdu = snmp_pdu_create(SnmpPduSet);
    int xerr = snmp_add_var(pdu,anOID, anOID_len, dataType, oidValue.toLatin1());
    if (xerr) {
        const char *str = snmp_api_errstring(xerr);
        qDebug() << oidStr << ": " << str;
        return result;
    }

    SOCK_STARTUP;
    putenv(strdup("POSIXLY_CORRECT=1"));

    SnmpSession *ss = snmp_open(&session); // establish the session
    if (!ss) {
        snmpSessionLogError(LOG_ERR, "ack", &session);
        SOCK_CLEANUP;
        return result;
    }

    SnmpPdu    *pduResponse = nullptr;
    SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(ss, pdu, &pduResponse));

    if (status == SnmpRespStatSuccess) {
        if (pduResponse->errstat == SNMP_ERR_NOERROR) {
            for(SnmpVariableList *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
                result = SnmpValue::fromVar(vars);
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
