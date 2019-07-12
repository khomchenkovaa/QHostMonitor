#include "snmp.h"

using namespace SDPO;

/*****************************************************************/

NetSNMP *NetSNMP::instance()
{
    // Meyers implementation of Singleton pattern, thread-safe in C++11
    static NetSNMP instance;

    return &instance;
}

/*****************************************************************/

SnmpMibTree *NetSNMP::allMibs()
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

NetSNMP::NetSNMP()
{
    snmp_set_mib_warnings(0);
    snmp_set_mib_errors(0);
    snmp_set_save_descriptions(1);
    init_snmp("SDPO");
}

/*****************************************************************/
