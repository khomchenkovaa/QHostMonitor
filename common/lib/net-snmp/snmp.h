#ifndef SDPO_NET_SNMP_H
#define SDPO_NET_SNMP_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include <QString>
#include <QVariant>
#include <QVector>

#define SNMP_INIT_DEFAULT_NAME "SDPO"

namespace SDPO {

/*****************************************************************/

/**
 * @brief SNMP defaults
 */
enum SnmpDefaults {
    SnmpPort      = SNMP_PORT,       /**< standard UDP port for SNMP agents to receive requests*/
    SnmpTrapPort  = SNMP_TRAP_PORT,  /**< standard UDP port for SNMP managers to receive notification*/
    SnmpMaxLen    = SNMP_MAX_LEN,    /**< typical maximum message size */
    SnmpMinMaxLen = SNMP_MIN_MAX_LEN /**< minimum maximum message size */
};

/**
 * @brief SNMP version to be used
 */
enum SnmpVersion {
    SNMPv1  = SNMP_VERSION_1,  /**< SNMP version 1 (=0) */
    SNMPv2c = SNMP_VERSION_2c, /**< SNMP version 2 (=1) */
    SNMPv3  = SNMP_VERSION_3   /**< SNMP version 3 (=3) */
};

enum SnmpSecAuth {
    AuthNone, AuthMD5, AuthSHA
};

enum SnmpSecPrivType {
    PrivNone, PrivDes, Priv3Des, PrivAes
};

/**
 * @brief PDU type to be encapsulated into SNMP message
 */
enum SnmpPduType {
    SnmpPduGet      = SNMP_MSG_GET,      /**< GET request */
    SnmpPduGetNext  = SNMP_MSG_GETNEXT,  /**< GET NEXT request */
    SnmpPduResponse = SNMP_MSG_RESPONSE, /**< Response */
    SnmpPduSet      = SNMP_MSG_SET,      /**< SET request */
    SnmpPduTrap     = SNMP_MSG_TRAP,     /**< Trap message (v1) */
    SnmpPduGetBulk  = SNMP_MSG_GETBULK,  /**< GET BULK request */
    SnmpPduInform   = SNMP_MSG_INFORM,   /**< Inform message */
    SnmpPduTrap2    = SNMP_MSG_TRAP2,    /**< Trap message (v2, v3) */
    SnmpPduReport   = SNMP_MSG_REPORT    /**< Report message */
};

/**
 * @brief SNMP Data type to PDU object
 */
enum SnmpDataType {
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
};

/**
 * @brief SNMP response status to be used
 */
enum SnmpResponseStatus {
    SnmpRespStatUnknown = -1,           /**< SNMP response not set */
    SnmpRespStatSuccess = STAT_SUCCESS, /**< SNMP response success */
    SnmpRespStatError   = STAT_ERROR,   /**< SNMP response with errors */
    SnmpRespStatTimeout = STAT_TIMEOUT  /**< SNMP response timeout */
};

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
enum MibAccess {
    MibAccessReadOnly  = MIB_ACCESS_READONLY,  /**< Read-Only access */
    MibAccessReadWrite = MIB_ACCESS_READWRITE, /**< Read-Write access */
    MibAccessWriteOnly = MIB_ACCESS_WRITEONLY, /**< Write-Only access */
    MibAccessNoAccess  = MIB_ACCESS_NOACCESS,  /**< Not Accessible */
    MibAccessNotify    = MIB_ACCESS_NOTIFY,    /**< Accessible for notify */
    MibAccessCreate    = MIB_ACCESS_CREATE     /**< Read-create access */
};

/**
 * @brief SNMP Data type to PDU object
 */
enum MibType {
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
    MibTypeUInteger    = TYPE_UINTEGER,
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
};

/*****************************************************************/

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

typedef QList<QPair<int, QString> > MibEnumList; // value, label

typedef QList<QPair<int, int> > MibRangeList; // low, high

typedef QList<QPair<QString, QChar> > MibIndexList; // ilabel, isimplied

typedef QStringList MibVarbindList;

/**
* @brief Net-SNMP oid array wrapper
*/
struct MibOid {
    oid    oidNum[MAX_OID_LEN];
    size_t oidLen = MAX_OID_LEN;
    QString oidStr;
    int    errNo = 0;

    explicit MibOid() {}
    explicit MibOid(oid *numOID, size_t oid_len);

    bool hasError() const {
        return errNo;
    }
    QString toString() const;
    QString errString() const;

    static MibOid parse(const QString& oidStr);
};

/**
 * @brief Net-SNMP MIB tree
 * More details in http://www.net-snmp.org/dev/agent/structtree.html
 */
typedef struct tree MibTree;

/**
* @brief Net-SNMP MIB tree wrapper
* More details in http://www.net-snmp.org/dev/agent/structtree.html
*/
struct MibNode {
    MibTree *node;

    MibNode(MibTree *node = nullptr) {
        this->node = node;
    }
    // main data
    /** Linked list of children of this node */
    MibNode childList() const {
        return node->child_list;
    }
    /** Next node in list of peers */
    MibNode nextPeer() const {
        return node->next_peer;
    }
    /** Next node in hashed list of names */
    MibNode next() const {
        return node->next;
    }
    /** Parent node */
    MibNode parent() const {
        return node->parent;
    }
    /** This node's textual name */
    QString label() const {
        return node->label;
    }
    /** This node's integer subidentifier */
    ulong id() const {
        return node->subid;
    }
    /** The main module containing this node */
    int moduleId() const {
        return node->modid;
    }
    /** Total modules containing this node */
    int numModules() const {
        return node->number_modules;
    }
    /** Module ids containing this node */
    QVector<int> moduleList() const;

    /** (WTF?) index into tclist (-1 if NA) */
    int tcIndex() const {
        return node->tc_index;
    }
    /** This node's object type */
    MibType type() const {
        return static_cast<MibType>(node->type);
    }
    /** This nodes access */
    MibAccess access() const {
        return static_cast<MibAccess>(node->access);
    }
    /** This nodes status */
    MibStatus status() const {
        return static_cast<MibStatus>(node->status);
    }

    bool hasChildren() const;
    QString name() const;
    QString moduleName() const;
    QString oid() const;
    QString syntax() const;
    char    typeChar() const;
    QString typeName() const;
    QString statusName() const;
    QString accessName() const;
    QString description() const;

    static MibNode getRoot();
};


/*****************************************************************/

struct SnmpValue {
    MibOid name;
    SnmpDataType type;
    QString      val;

    SnmpValue() {
        type = SnmpDataUnknown;
    }

    void setName(const MibOid& mibOid);
    void setName(oid *numOID, size_t oid_len);
    QString nameAsStr() const;
    QString dataTypeName() const;
    QString toString() const;

    static SnmpValue fromVar(SnmpVariableList *vars);
    static SnmpValue fromError(const MibOid& mibOid, const QString& err);
};

/*****************************************************************/

struct SnmpProfile {
    QString         name;
    SnmpVersion     version;
    QString         community;
    // SNMP v3 fields
    QString         context;
    SnmpSecAuth     auth;
    QString         authPwd;
    SnmpSecPrivType privType;
    QString         privPwd;
    bool            chkOpaque;

    SnmpProfile() :
        version(SNMPv2c),
        auth(AuthNone),
        privType(PrivNone),
        chkOpaque(false)
    {}

    static SnmpProfile findByName(const QString& name);
    static QStringList names();
    static int defaultIdx();
    static QList<SnmpProfile> credentials;
};

/*****************************************************************/

typedef QList<SnmpProfile> GSnmpCredentials;

/*****************************************************************/

class NetSNMP {
public:
    static void init(const QString name = SNMP_INIT_DEFAULT_NAME);
    static QString ipToString(u_char *ip, size_t ip_len);
};

/*****************************************************************/

class NetSnmpCommon : public QObject
{
    Q_OBJECT
public:
    explicit NetSnmpCommon(QObject *parent = nullptr);

    void setHost(const QString& host) {
        m_Host = host;
    }
    void setProfile(const SnmpProfile& profile);
    void setTimeout(const int timeout) {
       m_Timeout = timeout;
    }
    void setRetries(const int retries) {
        m_Retries = retries;
    }

protected:
    void snmpSessionInit(SnmpSession *session);
    QString snmpSessionLogError(int priority, const QString& prog, SnmpSession *ss);

protected:
    QString     m_Host;
    SnmpVersion m_Version;
    QString     m_Community;
    int         m_Timeout;
    int         m_Retries;

};

/*****************************************************************/

} // namespace SDPO

#endif // SDPO_NET_SNMP_H
