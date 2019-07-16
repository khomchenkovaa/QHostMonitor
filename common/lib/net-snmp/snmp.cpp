#include "snmp.h"
#include <QDebug>

using namespace SDPO;

/*****************************************************************/

NetSNMP *NetSNMP::instance()
{
    // Meyers implementation of Singleton pattern, thread-safe in C++11
    static NetSNMP instance;

    return &instance;
}

/*****************************************************************/

MibTree *NetSNMP::allMibs()
{
    return read_all_mibs();
}

/*****************************************************************/

QString NetSNMP::moduleName(int modId)
{
    struct module *mp = find_module(modId);

    if (mp) {
        return mp->name;
    } else {
        return QString("#%1").arg(modId);
    }
}

/*****************************************************************/

QString NetSNMP::mibTypeName(MibType type)
{
    switch (type) {
    case MibTypeObjId       : return "OBJECT IDENTIFIER";
    case MibTypeOctetStr    : return "OCTET STRING";
    case MibTypeInteger     : return "INTEGER";
    case MibTypeNetAddr     : return "NetworkAddress";
    case MibTypeIpAddr      : return "IpAddress";
    case MibTypeCounter     : return "Counter32";
    case MibTypeGauge       : return "Gauge32";
    case MibTypeTimeTicks   : return "TimeTicks";
    case MibTypeOpaque      : return "Opaque";
    case MibTypeNull        : return "NULL";
    case MibTypeCounter64   : return "Counter64";
    case MibTypeBitString   : return "BITS";
    case MibTypeNsapAddress : return "NsapAddress";
    case MibTypeUInreger    : return "UInteger32";
    case MibTypeUnsigned32  : return "Unsigned32";
    case MibTypeInteger32   : return "Integer32";
    case MibTypeTrap        : return "Trap Type";
    case MibTypeNotif       : return "Notif Type";
    case MibTypeObjGroup    : return "Obj Group";
    case MibTypeNotifGroup  : return "Notif Group";
    case MibTypeModId       : return "Mod Id";
    case MibTypeAgentCap    : return "Agent Cap";
    case MibTypeModComp     : return "Mod Comp";
    case MibTypeObjIdentity : return "Obj Identity";
    default: break;
    }
    return QString();
}

/*****************************************************************/

QString NetSNMP::mibAccessName(MibAccess access)
{
    switch (access) {
    case MibAccessReadOnly  : return "read-only";
    case MibAccessReadWrite : return "read-write";
    case MibAccessWriteOnly : return "write-only";
    case MibAccessNoAccess  : return "not-accessible";
    case MibAccessNotify    : return "accessible-for-notify";
    case MibAccessCreate    : return "read-create";
    }
    return QString();
}

/*****************************************************************/

QString NetSNMP::mibStatusName(MibStatus status)
{
    switch (status) {
    case MibStatusMandatory  : return "mandatory";
    case MibStatusOptional   : return "optional";
    case MibStatusObsolete   : return "obsolete";
    case MibStatusDeprecated : return "deprecated";
    case MibStatusCurrent    : return "current";
    }
    return QString();
}

/*****************************************************************/

QString NetSNMP::valueTypeName(SnmpDataType type)
{
    switch (type) {
    case SnmpDataUnknown     : return "Unknown";
    case SnmpDataNull        : return "Null";
    case SnmpDataInteger     : return "INTEGER";
    case SnmpDataUnsigned    : return "Unsigned";
    case SnmpDataOctetString : return "OctetString";
    case SnmpDataBits        : return "Bits";
    case SnmpDataBitString   : return "BitString";
    case SnmpDataObjectId    : return "ObjectId";
    case SnmpDataIPAddress   : return "IPAddress";
    case SnmpDataCounter     : return "Counter";
    case SnmpDataCounter64   : return "Counter64";
    case SnmpDataTimeTicks   : return "TimeTicks";
    }
    return QString();
}

/*****************************************************************/

SnmpValue NetSNMP::valueFrom(SnmpVariableList *vars)
{
    SnmpValue result;
    result.setName(vars->name, vars->name_length);
    result.type = static_cast<SnmpDataType>(vars->type);

    switch(vars->type) {
    case SnmpDataInteger:
    case SnmpDataUnsigned:
    case SnmpDataBits:
    case SnmpDataCounter:
    case SnmpDataTimeTicks:
        result.val = vars->val.integer? QString::number(*(vars->val.integer)) : "nullptr";
        break;
    case SnmpDataCounter64:
        result.val = vars->val.counter64? QString("%1 %2").arg(vars->val.counter64->high).arg(vars->val.counter64->low) : "nullptr";
        break;
    case SnmpDataBitString:
        result.val = vars->val.bitstring? QString(reinterpret_cast<const char *>(vars->val.bitstring)) : "nullptr";
        break;
    case SnmpDataOctetString:
    case SnmpDataIPAddress:
        result.val = vars->val.string? QString(reinterpret_cast<const char *>(vars->val.string)) : "nullptr";
        break;
    case SnmpDataObjectId:
        result.val = oidToString(static_cast<oid*>(vars->val.objid), vars->val_len / sizeof (oid));
        break;
    case SnmpDataNull:
        result.val = "NULL";
        break;
    default:
        result.val = "Unknown";
        break;
    }
    return result;
}

/*****************************************************************/

QString NetSNMP::oidToString(oid *numOID, size_t oid_len)
{
    QString result;
    for (size_t i=0; i<oid_len; ++i) {
        result.append(QString(".%1").arg(numOID[i]));
    }
    return result;
}

/*****************************************************************/

NetSNMP::NetSNMP()
{
    snmp_set_mib_warnings(0);
    snmp_set_mib_errors(0);
    snmp_set_save_descriptions(1);
    init_snmp("SDPO");
}

/*****************************************************************/

void SnmpValue::setName(oid *numOID, size_t oid_len)
{
    for (size_t i=0; i<oid_len; ++i) {
        name.append(numOID[i]);
    }
}

/*****************************************************************/

QString SnmpValue::nameAsStr() const
{
    QString result;
    for (int i=0; i<name.size(); ++i) {
        result.append(QString(".%1").arg(name.at(i)));
    }
    return result;
}

/*****************************************************************/

QString SnmpValue::toString() const
{
    return QString("[%1] = %2: %3")
            .arg(nameAsStr())
            .arg(NetSNMP::valueTypeName(type))
            .arg(val);
}

/*****************************************************************/
