#ifndef MIBNODE_H
#define MIBNODE_H

#include "miboid.h"

#define MIB_NODE_ALL "ALL"

namespace SDPO {

/*****************************************************************/
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

/*****************************************************************/
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

/*****************************************************************/
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

/*****************************************************************/
/*!
* \brief Net-SNMP MIB tree wrapper
* More details in http://www.net-snmp.org/dev/agent/structtree.html
*/
class MibNode
{
public:
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
    QString augments() const {
        return node->augments;
    }
    QString hint() const {
        return node->hint;
    }
    QString units() const {
        return node->units;
    }
    QString reference() const {
        return node->reference;
    }
    QString defaultValue() const {
        return node->defaultValue;
    }

    bool hasChildren() const;
    MibNode childAt(int idx) const;
    int indexOf() const;
    int childCount() const;
    MibNode getNextNode() const;
    QString name() const;
    QString labelAndId() const;

    bool isTable() const;
    MibNode tableEntry() const;
    QList<MibNode> tableColumns() const;

    QString moduleName() const;
    QString objectID() const;          /**< dotted decimal fully qualified OID */
    MibOid  mibOid() const;
    char    typeChar() const;
    QString typeName() const;
    QString syntax() const;
    QString accessName() const;
    QString statusName() const;
    QString enums() const;
    QString indexes() const;
    QString varbinds() const;
    QString description() const;

    static MibNode getRoot();
    static MibNode findByOid(const MibOid& mibOid);
    static MibNode findNode(const QString& label);
    static void clearTreeFlags();
    static bool addMibDir(const QString& mibDir);
    static MibNode readMib(const QString& mibFile = QString());
    static MibNode readModule(const QString& module = QString());

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

} // namespace SDPO

#endif // MIBNODE_H
