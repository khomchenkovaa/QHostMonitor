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

QString MibNode::name() const
{
    return QString("%1::%2").arg(moduleName(), label());
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

QString MibNode::oid() const
{
    QString oid = QString(".%1").arg(node->subid);
    MibTree *oidNode = node;
    while ((oidNode = oidNode->parent)) {
        oid = QString(".%1").arg(oidNode->subid) + oid;
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
        NetSNMP::init();
        mRoot.node = read_all_mibs();
    }
    return mRoot;
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

void NetSNMP::init(const QString sessName)
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

/*****************************************************************/
// NetSnmpCommon
/*****************************************************************/

NetSnmpCommon::NetSnmpCommon(QObject *parent)
    : QObject(parent),
      m_Host("localhost"),
      m_Version(SNMPv2c),
      m_Community("public"),
      m_Timeout(2000),
      m_Retries(1)
{
    NetSNMP::init();
}

/*****************************************************************/

void NetSnmpCommon::setProfile(const SnmpProfile &profile)
{
    m_Version   = profile.version;
    m_Community = profile.community;

    if (profile.version == SNMPv3) {
        //! TODO fields for SNMPv3
    }
}

/*****************************************************************/

void NetSnmpCommon::snmpSessionInit(SnmpSession *session)
{
    snmp_sess_init(session); // setup defaults
    session->peername      = m_Host.toLatin1().data();
    session->version       = static_cast<long>(m_Version);
    session->community     = reinterpret_cast<u_char*>(m_Community.toLocal8Bit().data());
    session->community_len = static_cast<size_t>(m_Community.size());
    session->retries       = m_Retries;
}

/*****************************************************************/

QString NetSnmpCommon::snmpSessionLogError(int priority, const QString &prog, SnmpSession *ss)
{
    Q_UNUSED(priority)
    char *err;
    snmp_error(ss, nullptr, nullptr, &err);
    QString result(err);
    qDebug() << prog << ": " << err;
//    snmp_log(priority, "%s: %s\n", static_cast<const char *>(prog.toLatin1()), err);
    SNMP_FREE(err);
    return result;
}

/*****************************************************************/

