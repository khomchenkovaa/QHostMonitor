#include "snmpvar.h"

using namespace SDPO;

/*****************************************************************/

QVariant SnmpVarData::value() const
{
    switch(type) {
    case SnmpDataInteger:
    case SnmpDataUnsigned:
    case SnmpDataBits:
    case SnmpDataCounter:
    case SnmpDataTimeTicks:
        return data.integer? QString::number(*(data.integer)) : "nullptr";
    case SnmpDataCounter64:
        return data.counter64? QString("%1 %2").arg(data.counter64->high).arg(data.counter64->low) : "nullptr";
    case SnmpDataBitString:
        if (data.bitstring) {
            QByteArray tmp = QByteArray::fromRawData((const char *)data.bitstring, length);
            return QString(tmp);
        }
        break;
    case SnmpDataOctetString:
        if (data.string) {
            QByteArray tmp = QByteArray::fromRawData((const char *)data.string, length);
            return QString(tmp);
            // TODO if OctetString without ranges => display as hex
        }
        break;
    case SnmpDataIPAddress:
        return ipAddress();
    case SnmpDataObjectId: {
        MibOid oidObj(static_cast<oid*>(data.objid), length / sizeof (oid));
        return oidObj.toString();
    } break;
    case SnmpDataNull:
        return "NULL";
    default:
        return "Unknown";
    }

    return QVariant();
}

/*****************************************************************/

QString SnmpVarData::ipAddress() const
{
    QStringList result;
    u_char *ip = data.string;
    for (size_t i=0; i < length; ++i) {
        result.append(QString::number(ip[i]));
    }
    return result.join('.');
}

/*****************************************************************/
