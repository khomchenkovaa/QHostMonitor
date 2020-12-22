#include "snmp.h"
#include <QDebug>

using namespace SDPO;

/*****************************************************************/

MibOid::MibOid(oid *numOID, size_t oid_len)
{
    oidLen = oid_len;
    for (size_t i=0; i<oidLen; ++i) {
        oidNum[i] = numOID[i];
    }
}

/*****************************************************************/

QString MibOid::toString() const
{
    if (hasError()) {
        return oidStr;
    }
    QString result;
    for (size_t i=0; i<oidLen; ++i) {
        result.append(QString(".%1").arg(oidNum[i]));
    }
    return result;
}

/*****************************************************************/

QString MibOid::errString() const
{
    return snmp_api_errstring(errNo);
}

/*****************************************************************/

MibOid MibOid::parse(const QString &oidStr)
{
    MibOid result;
    result.oidStr = oidStr;
    if (!snmp_parse_oid(oidStr.toLatin1(), result.oidNum, &result.oidLen)) {
        result.errNo = snmp_errno;
    }
    return result;
}

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
    int idx = 0;
    MibNode parentNode = parent();
    MibNode child = parentNode.isValid()? parentNode.childList() : getRoot();
    for(; child != parentNode; child = child.nextPeer()) {
        if (!child) {
            break;
        }
        ++idx;
    }
    return idx;
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
    if (node->enums) {
        enum_list *ep = node->enums;
        QStringList enums;
        while (ep) {
            enums.append( QString("%1(%2)").arg(ep->label).arg(ep->value) );
            ep = ep->next;
        }
        syntax.append( QString(" {%1}").arg(enums.join(", ")) );
    }
    return syntax;
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

QString MibNode::description() const
{
    QString description(node->description);
    QRegExp sp("\\s+");
    return description.replace(sp," ");
}

/*****************************************************************/

MibNode MibNode::getRoot()
{
    static MibNode mRoot;
    if (mRoot.node == nullptr) {
        NetSNMP::initMib();
        mRoot.node = read_all_mibs();
    }
    return mRoot;
}

/*****************************************************************/

MibNode MibNode::findByOid(const MibOid &mibOid)
{
    return get_tree(mibOid.oidNum, mibOid.oidLen, get_tree_head());;
}

/*****************************************************************/
// SnmpValue
/*****************************************************************/

void SnmpValue::setName(const MibOid &mibOid)
{
    name = mibOid;
}

/*****************************************************************/

void SnmpValue::setName(oid *numOID, size_t oid_len)
{
    name = MibOid(numOID, oid_len);
}

/*****************************************************************/

QString SnmpValue::nameAsStr() const
{
    return name.toString();
}

/*****************************************************************/

QString SnmpValue::dataTypeName() const
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

QString SnmpValue::toString() const
{
    return QString("[%1] = %2: %3")
            .arg(nameAsStr())
            .arg(dataTypeName())
            .arg(val);
}

/*****************************************************************/

SnmpValue SnmpValue::fromVar(SnmpVariableList *vars)
{
    // TODO display value according to Mib info
    SnmpValue result;
    result.setName(vars->name, vars->name_length);
    result.type = static_cast<SnmpDataType>(vars->type);
    result.mibNode = MibNode::findByOid(result.name);

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
        if (vars->val.bitstring) {
            QByteArray tmp = QByteArray::fromRawData((const char *)vars->val.bitstring, vars->val_len);
            result.val = QString(tmp);
        } else {
            result.val = "nullptr";
        }
        break;
    case SnmpDataOctetString:
        if (vars->val.string) {
            QByteArray tmp = QByteArray::fromRawData((const char *)vars->val.string, vars->val_len);
            result.val = QString(tmp);
            // TODO if OctetString wothout ranges => display as hex
        } else {
            result.val = "nullptr";
        }
        break;
    case SnmpDataIPAddress:
        result.val = NetSNMP::ipToString(vars->val.string, vars->val_len);
        break;
    case SnmpDataObjectId: {
        MibOid oidObj(static_cast<oid*>(vars->val.objid), vars->val_len / sizeof (oid));
        result.val = oidObj.toString();
    } break;
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

SnmpValue SnmpValue::fromError(const MibOid &mibOid, const QString &err)
{
    SnmpValue result;
    result.setName(mibOid);
    result.val = err;
    return result;
}

/*****************************************************************/
// SnmpProfile
/*****************************************************************/

GSnmpCredentials SnmpProfile::credentials;

/*****************************************************************/

SnmpProfile SnmpProfile::findByName(const QString &name)
{
    int idx = defaultIdx(); // not found
    for (int i=0; i< credentials.count(); i++) {
        if (name == credentials.at(i).name) {
            idx = i;
        }
    }
    return credentials.at(idx);
}

/*****************************************************************/

QStringList SnmpProfile::names()
{
    QStringList result;
    foreach(const SnmpProfile& item, credentials) {
        result.append(item.name);
    }
    return result;
}

/*****************************************************************/

int SnmpProfile::defaultIdx()
{
    int idx = -1;
    for (int i=0; i< credentials.count(); i++) {
        if (idx == -1) idx = i;
        if (credentials.at(i).version == SNMPv2c) {
            idx = i;
            break;
        }
    }
    return idx;
}

/*****************************************************************/

void NetSNMP::initMib(const QString sessName)
{
    static bool initialized = false;
    if (!initialized) {
        snmp_set_mib_warnings(0);
        snmp_set_mib_errors(0);
        snmp_set_save_descriptions(1);
        init_snmp(sessName.toLatin1());
        initialized = true;
    }
}

/*****************************************************************/

QString NetSNMP::ipToString(u_char *ip, size_t ip_len)
{
    QStringList result;
    for (size_t i=0; i < ip_len; ++i) {
        result.append(QString::number(ip[i]));
    }
    return result.join('.');
}



