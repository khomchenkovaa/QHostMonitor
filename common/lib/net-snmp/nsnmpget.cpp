#include "nsnmpget.h"

/*****************************************************************/

SDPO::NSnmpGet::NSnmpGet(QObject *parent) : QObject(parent),
    ss(nullptr), pdu(nullptr), pduResponse(nullptr),
    responseStatus(SnmpRespStatUnknown)
{
    snmp_sess_init( &session );
}

/*****************************************************************/

SDPO::NSnmpGet::~NSnmpGet()
{
    if (pduResponse) {
      snmp_free_pdu(pduResponse);
    }
    if (ss) {
        snmp_close(ss);
    }
}

/*****************************************************************/

void SDPO::NSnmpGet::setPeername(const QString &host)
{
    session.peername = strdup(host.toLatin1());
}

/*****************************************************************/

void SDPO::NSnmpGet::setVersion(SnmpVersion version)
{
    session.version = static_cast<long>(version);
}

/*****************************************************************/

void SDPO::NSnmpGet::setCommunity(const QString &community)
{
    session.community = reinterpret_cast<u_char*>(community.toLocal8Bit().data());
    session.community_len = static_cast<size_t>(community.size());
}

/*****************************************************************/

void SDPO::NSnmpGet::setTimeout(const int timeout)
{
    Q_UNUSED(timeout)
    // TODO set session.timeout
}

/*****************************************************************/

void SDPO::NSnmpGet::setRetries(const int retries)
{
    session.retries = retries;
}

/*****************************************************************/

bool SDPO::NSnmpGet::request(const QString& oidStr)
{
    ss = snmp_open(&session);                     /* establish the session */

    if (!ss) {
      return false;
    }

    pdu = snmp_pdu_create(SnmpPduGet);
    oid anOID[MAX_OID_LEN];
    size_t anOID_len = MAX_OID_LEN;

    if (!snmp_parse_oid(oidStr.toLatin1(), anOID, &anOID_len)) {
      return false;
    }

    snmp_add_null_var(pdu, anOID, anOID_len);

    responseStatus = static_cast<SnmpResponseStatus>(snmp_synch_response(ss, pdu, &pduResponse));

    return (SnmpRespStatSuccess == responseStatus);
}

/*****************************************************************/

QStringList SDPO::NSnmpGet::response() const
{
    QStringList result;

    if (pduResponse->errstat == SNMP_ERR_NOERROR) {
        for(netsnmp_variable_list *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
            switch(vars->type) {
            case SnmpDataInteger:
            case SnmpDataUnsigned:
            case SnmpDataBits:
            case SnmpDataCounter:
            case SnmpDataTimeTicks:
                result << ( vars->val.integer? QString::number(*(vars->val.integer)) : "nullptr" );
                break;
            case SnmpDataCounter64:
                result << ( vars->val.counter64? QString("%1 %2").arg(vars->val.counter64->high).arg(vars->val.counter64->low) : "nullptr" );
                break;
            case SnmpDataBitString:
                result << ( vars->val.bitstring? QString(reinterpret_cast<char *>(vars->val.bitstring)) : "nullptr" );
                break;
            case SnmpDataOctetString:
            case SnmpDataIPAddress:
                result << ( vars->val.string? QString(reinterpret_cast<char *>(vars->val.string)) : "nullptr" );
                break;
            case SnmpDataObjectId:
                result << ( vars->val.objid? QString::number(*(vars->val.objid)) : "nullptr" );
                break;
            case SnmpDataNull:
                result << "NULL";
                break;
            default:
                result << "Unknown";
                break;
            }
        }
    } else {
        result << snmp_errstring(static_cast<int>(pduResponse->errstat));
    }
    return result;
}

/*****************************************************************/

QString SDPO::NSnmpGet::status() const
{
    QString result;

    switch(responseStatus) {
    case SnmpRespStatUnknown:
        result = "Unknown";
        break;
    case SnmpRespStatSuccess:
        result = "Success";
        break;
    case SnmpRespStatError:
        result = "Error";
        break;
    case SnmpRespStatTimeout:
        result = "Timeout";
        break;
    }
    return result;
}

/*****************************************************************/
