#include "mibnode.h"

#include "snmp.h"

#include <QRegularExpression>

using namespace SDPO;

/*****************************************************************/
// MibTreeWrapper
/*****************************************************************/

QVector<int> MibNode::moduleList() const
{
    QVector<int> result(node->number_modules);
    for (int i=0; i < node->number_modules; ++i) {
        result.append(node->module_list[i]);
    }
    return result;
}

/*****************************************************************/

bool MibNode::hasChildren() const
{
    return node->child_list != nullptr;
}

/*****************************************************************/

MibNode MibNode::childAt(int idx) const
{
    MibNode child = isValid() ? childList() : getRoot();
    for(int i = 0; i != idx; ++i ) {
        child = child.nextPeer();
        if (!child.isValid()) {
            break;
        }
    }
    return child;
}

/*****************************************************************/

int MibNode::indexOf() const
{
    int result = -1; // not found
    MibNode parentNode = parent();
    MibNode child = parentNode.isValid()? parentNode.childList() : getRoot();
    for(int idx = 0; child.isValid(); child = child.nextPeer()) {
        if (child.node == node) {
            result = idx;
            break;
        }
        ++idx;
    }
    return result;
}

/*****************************************************************/

int MibNode::childCount() const
{
    int cnt = 0;
    if (!isValid())
        return cnt;
    for(MibNode child = childList(); child.isValid(); child = child.nextPeer()) {
        cnt++;
    }
    return cnt;
}

/*****************************************************************/

MibNode MibNode::getNextNode() const
{
    if (node->child_list) return(node->child_list);
    if (node->next_peer) return(node->next_peer);
    tree *tp = node->parent;
    while ( tp ) {
        if (tp->next_peer) return tp->next_peer;
        tp = tp->parent;
    }
    return MibNode();
}

/*****************************************************************/

QString MibNode::name() const
{
    return QString("%1::%2").arg(moduleName(), label());
}

/*****************************************************************/

QString MibNode::labelAndId() const
{
    return QString("%1 (%2)").arg(label()).arg(subID());
}

/*****************************************************************/

bool MibNode::isTable() const
{
    return (hasChildren() && childList().node->indexes);
}

/*****************************************************************/

MibNode MibNode::tableEntry() const
{
    if (isValid()) {
        return childList();
    }
    return MibNode();
}

/*****************************************************************/

QList<MibNode> MibNode::tableColumns() const
{
    QList<MibNode> result;
    MibNode node = tableEntry(); // get table entry
    if (!node.isValid()) { // no entry - not a table
        return result;
    }
    node = node.childList(); // get first field
    if (!node.isValid()) { // no fields - not a table
        return result;
    }
    do {
        if (node.access() == MIB_ACCESS_NOACCESS) {
            continue;
        }
        result.prepend(node);
    } while ((node = node.nextPeer()));
    return result;
}

/*****************************************************************/

QString MibNode::moduleName() const
{
    module *mp = find_module(node->modid);

    if (mp) {
        return mp->name;
    } else {
        return QString("#%1").arg(node->modid);
    }
}

/*****************************************************************/

QString MibNode::objectID() const
{
    QString oid = QString(".%1").arg(node->subid);
    MibNode oidNode = node;
    while ((oidNode = oidNode.parent())) {
        oid = QString(".%1").arg(oidNode.subID()) + oid;
    }
    if (!hasChildren()) {
        oid += ".0";
    }
    return oid;
}

/*****************************************************************/

MibOid MibNode::mibOid() const
{
    MibOid curOid;
    if (node->parent) {
        MibNode par = parent();
        curOid = par.mibOid(); // recource
    }
    curOid.addOid(subID());
    return curOid;
}

/*****************************************************************/

char MibNode::typeChar() const
{
    switch(node->type) {
    case MibTypeObjId       : return 'o';
    case MibTypeOctetStr    : return 's';
    case MibTypeInteger     : return 'i';
    case MibTypeIpAddr      : return 'a';
    case MibTypeCounter     : return 'c';
    case MibTypeTimeTicks   : return 't';
    case MibTypeCounter64   : return 'C';
    case MibTypeBitString   : return 'b';
    case MibTypeUInteger    : return 'u';
    case MibTypeUnsigned32  : return 'u';
    case MibTypeInteger32   : return 'i';
    default: break;
    }
    return '=';

    /*
    case '3':
    case 'x':
    case 'd':
#ifdef NETSNMP_WITH_OPAQUE_SPECIAL_TYPES
    case 'I':
    case 'U':
    case 'F':
    case 'D':
    */
}

/*****************************************************************/

QString MibNode::typeName() const
{
    switch (node->type) {
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
    case MibTypeUInteger    : return "UInteger32";
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

QString MibNode::syntax() const
{
    QString syntax = typeName();
    if (node->ranges) {
        range_list *rp = node->ranges;
        QStringList ranges;
        while(rp) {
            switch (node->type) {
            case MibTypeInteger:
            case MibTypeInteger32:
                ranges.append( rp->low == rp->high ? QString::number(rp->low) :
                                                  QString("%1..%2").arg(rp->low).arg(rp->high) );
                break;
            case MibTypeUnsigned32:
            case MibTypeOctetStr:
            case MibTypeGauge:
            case MibTypeUInteger:
                ranges.append( rp->low == rp->high ? QString::number(static_cast<unsigned>(rp->low)) :
                                                  QString("%1..%2").arg(static_cast<unsigned>(rp->low)).arg(static_cast<unsigned>(rp->high)) );
                break;
            }
            rp = rp->next;
        }
        syntax.append( QString(" (%1)").arg(ranges.join(" | ")) );
    }
    return syntax;
}

/*****************************************************************/

QString MibNode::accessName() const
{
    switch (node->access) {
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

QString MibNode::statusName() const
{
    switch (node->status) {
    case MibStatusMandatory  : return "mandatory";
    case MibStatusOptional   : return "optional";
    case MibStatusObsolete   : return "obsolete";
    case MibStatusDeprecated : return "deprecated";
    case MibStatusCurrent    : return "current";
    }
    return QString();
}

/*****************************************************************/

QString MibNode::enums() const
{
    QStringList result;
    enum_list *idx = node->enums;
    while (idx) {
        result.append( QString("%1 (%2)").arg(idx->label).arg(idx->value) );
        idx = idx->next;
    }
    return result.join(", ");
}

/*****************************************************************/

QString MibNode::indexes() const
{
    QStringList result;
    index_list *idx = node->indexes;
    while(idx) {
        result.append(idx->ilabel);
        idx = idx->next;
    }
    return result.join(", ");
}

/*****************************************************************/

QString MibNode::varbinds() const
{
    QStringList result;
    varbind_list *idx = node->varbinds;
    while(idx) {
        result.append(idx->vblabel);
        idx = idx->next;
    }
    return result.join(", ");
}

/*****************************************************************/

QString MibNode::description() const
{
    QString description(node->description);
    QRegularExpression re("^\\s+", QRegularExpression::MultilineOption);
    return description.remove(re);
}

/*****************************************************************/

MibNode MibNode::getRoot()
{
    MibNode rootNode = get_tree_head();
    if (!rootNode.isValid()) {
        NetSNMP::initSnmp(); // TODO remove to erase snmp.h include
        rootNode = read_all_mibs();
    }
    return rootNode;
}

/*****************************************************************/

MibNode MibNode::findByOid(const MibOid &mibOid)
{
    return get_tree(mibOid.numOid, mibOid.length, get_tree_head());
}

/*****************************************************************/

MibNode MibNode::findNode(const QString &label)
{
    return find_tree_node(label.toLocal8Bit(), -1);
}

/*****************************************************************/

void MibNode::clearTreeFlags()
{
    clear_tree_flags(get_tree_head());
}

/*****************************************************************/

bool MibNode::addMibDir(const QString &mibDir)
{
    if (!mibDir.isEmpty()) {
        return add_mibdir(mibDir.toLatin1());
    }
    return false;
}

/*****************************************************************/

MibNode MibNode::readMib(const QString &mibFile)
{
    if (mibFile.isEmpty()) {
        if (get_tree_head() == nullptr) {
            // snmp_read_mib: initializing MIB"
            netsnmp_init_mib();
        }
    } else {
        // snmp_read_mib: reading MIB: " << mibFile
        if (mibFile != MIB_NODE_ALL) {
            read_mib(mibFile.toLocal8Bit());
        } else {
            read_all_mibs();
        }
    }
    return get_tree_head();
}

/*****************************************************************/

MibNode MibNode::readModule(const QString &module)
{
    if (module.isEmpty() || module == MIB_NODE_ALL) {
        read_all_mibs();
    } else {
        netsnmp_read_module(module.toLocal8Bit());
    }
    return get_tree_head();
}

/*****************************************************************/
