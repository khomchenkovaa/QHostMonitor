#ifndef SDPO_NET_SNMP_H
#define SDPO_NET_SNMP_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include <QString>
#include <QVariant>
#include <QVector>

#include "miboid.h"

#define SNMP_INIT_DEFAULT_NAME "SDPO"

namespace SDPO {

/*****************************************************************/

/*!
 * \brief SNMP defaults
 */
enum SnmpDefaults {
    SnmpPort      = SNMP_PORT,            /**< standard UDP port for SNMP agents to receive requests*/
    SnmpTrapPort  = SNMP_TRAP_PORT,       /**< standard UDP port for SNMP managers to receive notification*/
    SnmpMaxLen    = SNMP_MAX_LEN,         /**< typical maximum message size */
    SnmpMinMaxLen = SNMP_MIN_MAX_LEN,     /**< minimum maximum message size */
    SnmpTimeout   = SNMP_DEFAULT_TIMEOUT,
    SnmpRetries   = SNMP_DEFAULT_RETRIES
};

/*!
 * \brief SNMP version to be used
 */
enum SnmpVersion {
    SNMPvDefault = SNMP_DEFAULT_VERSION,
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

/*!
 * \brief PDU type to be encapsulated into SNMP message
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

/*!
 * \brief SNMP Data type to PDU object
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

/*!
 * \brief SNMP response status to be used
 */
enum SnmpResponseStatus {
    SnmpRespStatUnknown = -1,           /**< SNMP response not set */
    SnmpRespStatSuccess = STAT_SUCCESS, /**< SNMP response success */
    SnmpRespStatError   = STAT_ERROR,   /**< SNMP response with errors */
    SnmpRespStatTimeout = STAT_TIMEOUT  /**< SNMP response timeout */
};

/*!
 * \brief Current status to MIB object
 * Defined in www.net-snmp.org/dev/agent/parse_8h_source.html#l00188
 */
enum MibStatus {
    MibStatusMandatory  = MIB_STATUS_MANDATORY,  /**< Mandatory status */
    MibStatusOptional   = MIB_STATUS_OPTIONAL,   /**< Optional status */
    MibStatusObsolete   = MIB_STATUS_OBSOLETE,   /**< Obsolete status */
    MibStatusDeprecated = MIB_STATUS_DEPRECATED, /**< Deprecated status */
    MibStatusCurrent    = MIB_STATUS_CURRENT     /**< Current status */
};

/*!
 * \brief Access mode to MIB object
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

/*!
 * \brief SNMP Data type to PDU object
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

/*!
 * \brief The OidOptionFlag enum
 */
enum OidOptionFlag {
    NoFlags        = 0x00,
    FailOnNullOid  = 0x01,
    UseLongNames   = 0x02,
    NonLeafName    = 0x04,
    UseNumericOids = 0x08
};
Q_DECLARE_FLAGS(OidOptions, OidOptionFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(OidOptions)

/*****************************************************************/

/*!
 * \brief Net-SNMP data value
 * More details in http://www.net-snmp.org/dev/agent/unionnetsnmp__vardata.html
 */
typedef netsnmp_vardata SnmpVarData;

/*!
 * \brief Net-SNMP session with agent
 * More details in http://www.net-snmp.org/dev/agent/structsnmp__session.html
 */
typedef netsnmp_session SnmpSession;

/*!
 * \brief Net-SNMP request/response PDU wrapper
 * More details in http://www.net-snmp.org/dev/agent/structsnmp__pdu.html
 */
struct SnmpPdu {
    snmp_pdu *ptr = nullptr;
    SnmpResponseStatus status = SnmpRespStatUnknown;

    SnmpPdu(void *pointer = nullptr) {
        this->ptr = static_cast<snmp_pdu*>(pointer);
    }

    bool noError() {
        if (status == SnmpRespStatSuccess) {
            return (ptr->errstat == SNMP_ERR_NOERROR);
        }
        return false;
    }

    void cleanup() {
        if (ptr) {
            snmp_free_pdu(ptr);
        }
    }

    void addNullVar(const MibOid& mibOid) {
        snmp_add_null_var(ptr, mibOid.numOid, mibOid.length);
    }

    static SnmpPdu create(SnmpPduType type) {
        return SnmpPdu(snmp_pdu_create(type));
    }

    static SnmpPdu create(SnmpPduType type, const QList<MibOid>& oids) {
        SnmpPdu result = create(type);
        foreach(const MibOid& mibOid, oids) {
            result.addNullVar(mibOid);
        }
        return result;
    }
};

/*****************************************************************/

/*!
 * \brief Net-SNMP variable list
 * More details in http://www.net-snmp.org/dev/agent/structvariable__list.html
 */
typedef netsnmp_variable_list SnmpVariableList;

//typedef QList<QPair<int, QString> > MibEnumList; // value, label

//typedef QList<QPair<int, int> > MibRangeList; // low, high

//typedef QList<QPair<QString, QChar> > MibIndexList; // ilabel, isimplied

//typedef QStringList MibVarbindList;

/*!
* \brief Net-SNMP MIB tree wrapper
* More details in http://www.net-snmp.org/dev/agent/structtree.html
*/
struct MibNode {
    tree *node = nullptr;

    MibNode(tree *pointer) {
        this->node = pointer;
    }

    MibNode(void *pointer = nullptr) {
        this->node = static_cast<tree *>(pointer);
    }

    bool isValid() const {
        return (node != nullptr);
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
    ulong subID() const {
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
        return (isValid()? static_cast<MibType>(node->type) : MibType::MibTypeOther);
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
    MibNode childAt(int idx) const;
    int indexOf() const;
    int childCount() const;
    MibNode getNextNode() const;
    QString name() const;
    QString labelAndId() const;
    bool isTable() const;
    QString moduleName() const;
    QString objectID() const;          /**< dotted decimal fully qualified OID */
    MibOid  mibOid() const;
    QString syntax() const;
    char    typeChar() const;
    QString typeName() const;
    QString statusName() const;
    QString accessName() const;
    QString description() const;

    static MibNode getRoot();
    static MibNode findByOid(const MibOid& mibOid);
    static MibNode findNode(const QString& label);
    static void clearTreeFlags();

    operator bool() const {
        return isValid();
    }
    bool operator== (const MibNode &rhs) {
        return (this->node == rhs.node);
    }
    bool operator!= (const MibNode &rhs) {
        return (this->node != rhs.node);
    }
 };


/*****************************************************************/

struct SnmpValue {
    MibOid       name;
    SnmpDataType type;
    QString      val;
    MibNode      mibNode;

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
    static bool autoInitMib;      ///< enable automatic MIB loading at session creation time
    static bool useLongNames;     ///< non-zero to prefer longer mib textual identifiers rather than just leaf indentifiers
    static int useSprintValue;   ///< non-zero to enable formatting of response values using the snmp libraries "snprint_value"
    static int useEnums;         ///< non-zero to return integers as enums and allow sets using enums where appropriate
    static int useNumeric;       ///< non-zero to return object tags as numeric OID's instead of converting to textual representations.
    static MibNode mibRoot;      ///< tied hash to access libraries internal mib tree structure parsed in from mib files
    static int verbose;          ///< controls warning/info output of SNMP module, 0 => no output, 1 =>enables warning and info output from NetSNMP class itself
    static int debugging;        ///< non-zero to globally enable libsnmp do_debugging output set to >= 2 to enabling packet dumping
    static int dumpPacket;       ///< non-zero to globally enable libsnmp dump_packet output.
    static int saveDescriptions; ///< tied scalar to control saving descriptions during mib parsing - must be set prior to mib loading
    static int bestGuess;        ///< determine whether or not to enable best-guess regular expression object name translation.  1 = Regex (-Ib), 2 = random (-IR)
    static int nonIncreasing;    ///< stop polling with an "OID not increasing"-error when an OID does not increases in bulkwalk. */
    static int replaceNewer;     ///< determine whether or not to tell the parser to replace older MIB modules with newer ones when loading MIBs.
public:
    static void registerDebugTokens(const QString& tokens);
    static QVariant getEnv(const QString& name);
    static int setEnv(const QString& envName, const QVariant& envVal, int overwrite);
    static void initMib();
    static bool addMibDirs(const QStringList& mibDirs);
    static bool addMibFiles(const QStringList& mibFiles);
    static bool loadModules(const QStringList& mibModules);
    static QString translateObj(const QString& obj, bool toLongName = false, bool includeModuleName = true);
    static QList<SnmpValue> get(const QVariantMap& map);


    static QString ipToString(u_char *ip, size_t ip_len);

private:
    static void initSnmp(const QString& appName = SNMP_INIT_DEFAULT_NAME);
    static void librariesInit(const QString& appName);
    static bool addMibDir(const QString& mibDir);
    static bool readMib(const QString& mibFile);
    static bool readModule(const QString& module);
};


/*****************************************************************/

} // namespace SDPO

#endif // SDPO_NET_SNMP_H
