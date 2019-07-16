#ifndef SDPO_NET_SNMP_H
#define SDPO_NET_SNMP_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include <QString>
#include <QVariant>
#include <QVector>

namespace SDPO {

/**
 * @brief SNMP defaults
 */
typedef enum SnmpDefaultsEnum {
    SnmpPort      = SNMP_PORT,       /**< standard UDP port for SNMP agents to receive requests*/
    SnmpTrapPort  = SNMP_TRAP_PORT,  /**< standard UDP port for SNMP managers to receive notification*/
    SnmpMaxLen    = SNMP_MAX_LEN,    /**< typical maximum message size */
    SnmpMinMaxLen = SNMP_MIN_MAX_LEN /**< minimum maximum message size */
} SnmpDefaults;

/**
 * @brief SNMP version to be used
 */
typedef enum SnmpVersionEnum {
    SNMPv1  = SNMP_VERSION_1,  /**< SNMP version 1 (=0) */
    SNMPv2c = SNMP_VERSION_2c, /**< SNMP version 2 (=1) */
    SNMPv3  = SNMP_VERSION_3   /**< SNMP version 3 (=3) */
} SnmpVersion;

/**
 * @brief PDU type to be encapsulated into SNMP message
 */
typedef enum SnmpPduTypeEnum {
    SnmpPduGet      = SNMP_MSG_GET,      /**< GET request */
    SnmpPduGetNext  = SNMP_MSG_GETNEXT,  /**< GET NEXT request */
    SnmpPduResponse = SNMP_MSG_RESPONSE, /**< Response */
    SnmpPduSet      = SNMP_MSG_SET,      /**< SET request */
    SnmpPduTrap     = SNMP_MSG_TRAP,     /**< Trap message (v1) */
    SnmpPduGetBulk  = SNMP_MSG_GETBULK,  /**< GET BULK request */
    SnmpPduInform   = SNMP_MSG_INFORM,   /**< Inform message */
    SnmpPduTrap2    = SNMP_MSG_TRAP2,    /**< Trap message (v2, v3) */
    SnmpPduReport   = SNMP_MSG_REPORT    /**< Report message */
} SnmpPduType;

/**
 * @brief SNMP Data type to PDU object
 */
typedef enum SnmpDataTypeEnum {
    SnmpDataUnknown     = -1,               /**< Unknown type */
    SnmpDataNull        = ASN_NULL,         /**< Null type */
    SnmpDataInteger     = ASN_INTEGER,      /**< Signed Integer type */
    SnmpDataUnsigned    = ASN_UNSIGNED,     /**< Unsigned Integer type */
    SnmpDataOctetString = ASN_OCTET_STR,    /**< Octet String type */
    SnmpDataBits        = ASN_BIT8,         /**< Bits type */
    SnmpDataBitString   = ASN_BIT_STR,      /**< BitString type */
    SnmpDataObjectId    = ASN_OBJECT_ID,    /**< OID type */
    SnmpDataIPAddress   = ASN_IPADDRESS,    /**< IP Address type */
    SnmpDataCounter     = ASN_COUNTER,      /**< Counter type */
    SnmpDataCounter64   = ASN_COUNTER64,    /**< 64 bits Counter type */
    SnmpDataGauge       = ASN_GAUGE,        /**< Gauge type */
    SnmpDataTimeTicks   = ASN_TIMETICKS     /**< Time Ticks type*/
} SnmpDataType;

/**
 * @brief SNMP response status to be used
 */
typedef enum SnmpResponseStatusEnum {
    SnmpRespStatUnknown = -1,           /**< SNMP response not set */
    SnmpRespStatSuccess = STAT_SUCCESS, /**< SNMP response success */
    SnmpRespStatError   = STAT_ERROR,   /**< SNMP response with errors */
    SnmpRespStatTimeout = STAT_TIMEOUT  /**< SNMP response timeout */
} SnmpResponseStatus;

/**
 * @brief Current status to MIB object
 * Defined in www.net-snmp.org/dev/agent/parse_8h_source.html#l00188
 */
typedef enum MibStatusEnum {
    MibStatusMandatory  = MIB_STATUS_MANDATORY,  /**< Mandatory status */
    MibStatusOptional   = MIB_STATUS_OPTIONAL,   /**< Optional status */
    MibStatusObsolete   = MIB_STATUS_OBSOLETE,   /**< Obsolete status */
    MibStatusDeprecated = MIB_STATUS_DEPRECATED, /**< Deprecated status */
    MibStatusCurrent    = MIB_STATUS_CURRENT     /**< Current status */
} MibStatus;

/**
 * @brief Access mode to MIB object
 * Defined in www.net-snmp.org/dev/agent/parse_8h_source.html#l00181
 */
typedef enum MibAccessEnum {
    MibAccessReadOnly  = MIB_ACCESS_READONLY,  /**< Read-Only access */
    MibAccessReadWrite = MIB_ACCESS_READWRITE, /**< Read-Write access */
    MibAccessWriteOnly = MIB_ACCESS_WRITEONLY, /**< Write-Only access */
    MibAccessNoAccess  = MIB_ACCESS_NOACCESS,  /**< Not Accessible */
    MibAccessNotify    = MIB_ACCESS_NOTIFY,    /**< Accessible for notify */
    MibAccessCreate    = MIB_ACCESS_CREATE     /**< Read-create access */
} MibAccess;

/**
 * @brief SNMP Data type to PDU object
 */
typedef enum MibTypeEnum {
    MibTypeOther       = TYPE_OTHER,
    MibTypeObjId       = TYPE_OBJID,
    MibTypeOctetStr    = TYPE_OCTETSTR,
    MibTypeInteger     = TYPE_INTEGER,
    MibTypeNetAddr     = TYPE_NETADDR,
    MibTypeIpAddr      = TYPE_IPADDR,
    MibTypeCounter     = TYPE_COUNTER,
    MibTypeGauge       = TYPE_GAUGE,
    MibTypeTimeTicks   = TYPE_TIMETICKS,
    MibTypeOpaque      = TYPE_OPAQUE,
    MibTypeNull        = TYPE_NULL,
    MibTypeCounter64   = TYPE_COUNTER64,
    MibTypeBitString   = TYPE_BITSTRING,
    MibTypeNsapAddress = TYPE_NSAPADDRESS,
    MibTypeUInreger    = TYPE_UINTEGER,
    MibTypeUnsigned32  = TYPE_UNSIGNED32,
    MibTypeInteger32   = TYPE_INTEGER32,
    MibTypeTrap        = TYPE_TRAPTYPE,
    MibTypeNotif       = TYPE_NOTIFTYPE,
    MibTypeObjGroup    = TYPE_OBJGROUP,
    MibTypeNotifGroup  = TYPE_NOTIFGROUP,
    MibTypeModId       = TYPE_MODID,
    MibTypeAgentCap    = TYPE_AGENTCAP,
    MibTypeModComp     = TYPE_MODCOMP,
    MibTypeObjIdentity = TYPE_OBJIDENTITY
} MibType;

/**
 * @brief Net-SNMP data value
 * More details in http://www.net-snmp.org/dev/agent/unionnetsnmp__vardata.html
 */
typedef netsnmp_vardata SnmpVarData;

/**
 * @brief Net-SNMP session with agent
 * More details in http://www.net-snmp.org/dev/agent/structsnmp__session.html
 */
typedef netsnmp_session SnmpSession;

/**
 * @brief Net-SNMP request/response PDU
 * More details in http://www.net-snmp.org/dev/agent/structsnmp__pdu.html
 */
typedef struct snmp_pdu SnmpPdu;

/**
 * @brief Net-SNMP variable list
 * More details in http://www.net-snmp.org/dev/agent/structvariable__list.html
 */
typedef netsnmp_variable_list SnmpVariableList;

/**
 * @brief Net-SNMP MIB tree
 * More details in http://www.net-snmp.org/dev/agent/structtree.html
 */
typedef struct tree MibTree;

struct SnmpValue {
    QVector<oid> name;
    SnmpDataType type;
    QString      val;

    SnmpValue() {
        type = SnmpDataUnknown;
    }

    void setName(oid *numOID, size_t oid_len);
    QString nameAsStr() const;
    QString toString() const;
};

class NetSNMP {
public:
    /**
     * @brief Get a SNMP instance
     * @return  pointer to instance of SNMP class
     */
    static NetSNMP *instance();

    MibTree *allMibs();
    QString moduleName(int modId);
    static QString mibTypeName(MibType type);
    static QString mibAccessName(MibAccess access);
    static QString mibStatusName(MibStatus status);
    static QString valueTypeName(SnmpDataType type);
    static SnmpValue valueFrom(SnmpVariableList *vars);
    static QString oidToString(oid *numOID, size_t oid_len);

private:
    NetSNMP();
    NetSNMP(const NetSNMP&) {}
    NetSNMP& operator=(const NetSNMP&) { return *this; }
    ~NetSNMP() {}
};

} // namespace SDPO

#endif // SDPO_NET_SNMP_H
