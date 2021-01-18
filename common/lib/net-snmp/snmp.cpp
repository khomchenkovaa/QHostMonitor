#include "snmp.h"
#include "oidstring.h"
#include "netsnmpsession.h"

#include <QRegularExpression>

#include <QDebug>

#define MAX_TYPE_NAME_LEN 32
#define STR_BUF_SIZE (MAX_TYPE_NAME_LEN * MAX_OID_LEN)

#define USE_NUMERIC_OIDS 0x08
#define NON_LEAF_NAME 0x04
#define USE_LONG_NAMES 0x02
#define FAIL_ON_NULL_IID 0x01
#define NO_FLAGS 0x00

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
    return get_tree(mibOid.numOid, mibOid.length, get_tree_head());;
}

/*****************************************************************/

MibNode MibNode::findNode(const QString &label)
{
    return find_tree_node(label.toLatin1(), -1);
}

/*****************************************************************/

void MibNode::clearTreeFlags()
{
    clear_tree_flags(get_tree_head());
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
            .arg(nameAsStr(), dataTypeName(), val);
}

/*****************************************************************/

SnmpValue SnmpValue::fromVar(SnmpVar var)
{
    SnmpValue result;
    result.setName(var.mibOid());
    result.type = var.type();
    result.mibNode = MibNode::findByOid(result.name);
    result.val = var.value().toString();

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
// NetSnmp Core
/*****************************************************************/

bool NetSNMP::autoInitMib = true;
bool NetSNMP::useLongNames = false;
int NetSNMP::useSprintValue = 0;
int NetSNMP::useEnums = 0;
int NetSNMP::useNumeric = 0;
MibNode NetSNMP::mibRoot;
int NetSNMP::verbose = 0;
int NetSNMP::debugging = 0;
int NetSNMP::dumpPacket = 0;
int NetSNMP::saveDescriptions = 0;
int NetSNMP::bestGuess = 0;
int NetSNMP::nonIncreasing = 0;
int NetSNMP::replaceNewer = 0;

/*****************************************************************/

void NetSNMP::registerDebugTokens(const QString &tokens)
{
    debug_register_tokens(tokens.toLatin1().data());
    snmp_set_do_debugging(1);
}

/*****************************************************************/

QVariant NetSNMP::getEnv(const QString &name)
{
    return QString(netsnmp_getenv(name.toLatin1().data()));
}

/*****************************************************************/

int NetSNMP::setEnv(const QString &envName, const QVariant &envVal, int overwrite)
{
    return netsnmp_setenv(envName.toLatin1().data(),
                          envVal.toString().toLatin1().data(),
                          overwrite);
}

/*****************************************************************/
/*!
 * \brief initMib is equivalent to calling the snmp library init_mib if Mib is NULL
 * if Mib is already loaded this function does nothing
 */
void NetSNMP::initMib()
{
    initSnmp(SNMP_INIT_DEFAULT_NAME);
}


/*****************************************************************/
/*!
 * \brief NetSNMP::addMibDirs adds directories to search path when a module is requested to be loaded
 * \param mibDirs - thelist of dirs
 * \return success or not
 */
bool NetSNMP::addMibDirs(const QStringList &mibDirs)
{
    initSnmp(SNMP_INIT_DEFAULT_NAME);
    foreach(const QString& mibDir, mibDirs) {
        if (!addMibDir(mibDir)) return false;
    }
    return true;
}

/*****************************************************************/
/*!
 * \brief NetSNMP::addMibFiles adds mib definitions to currently loaded mib database from file(s) supplied
 * \param mibFiles - the list of files
 * \return success or not
 */
bool NetSNMP::addMibFiles(const QStringList &mibFiles)
{
    initSnmp(SNMP_INIT_DEFAULT_NAME);
    foreach(const QString& mibFile, mibFiles) {
        if (!readMib(mibFile)) return false;
    }
    return true;
}

/*****************************************************************/
/*!
 * \brief loadModules adds mib module definitions to currently loaded mib database.
 * Modules will be searched from previously defined mib search dirs
 * Passing and arg of 'ALL' will cause all known modules to be loaded
 * \param mibModules the list of modules.
 * \return success or not
 */
bool NetSNMP::loadModules(const QStringList &mibModules)
{
    initSnmp(SNMP_INIT_DEFAULT_NAME);
    foreach(const QString& module, mibModules) {
        if (!readModule(module)) return false;
    }
    return true;
}

/*****************************************************************/
/*!
 * \brief Translate object identifier(tag or numeric) into alternate representation
 * \details Translate object identifier(tag or numeric) into alternate representation
 * (i.e., sysDescr => '.1.3.6.1.2.1.1.1' and '.1.3.6.1.2.1.1.1' => sysDescr)
 * when NetSNMP::useLongNames or second arg is non-zero the translation will return longer textual identifiers (e.g., system.sysDescr).
 * An optional third argument of non-zero will cause the module name to be prepended to the text name (e.g. 'SNMPv2-MIB::sysDescr').
 * If no Mib is loaded when called and NetSNMP::autoInitMib is enabled then the Mib will be loaded. Will return 'undef' upon failure.
 * \param obj object identifier
 * \param toLongName use long name flag
 * \param includeModuleName include module name flag
 * \return translation result
 */
QString NetSNMP::translateObj(const QString &obj, bool toLongName, bool includeModuleName)
{
    bool longNames = toLongName || useLongNames;
    OidString oidString(obj);
    if (oidString.isEmpty()) {
        return QString();
    }
    QString result;
    QRegularExpression re("(\\.\\d+)*$");
    QRegularExpressionMatch reMatch = re.match(obj);

    if (oidString.isNumeric()) {
       result = oidString.translateToTag(longNames, autoInitMib, includeModuleName);
    } else if (reMatch.hasMatch() && bestGuess == 0) {
        QString tail = reMatch.captured(1);
        QString name = obj;
        name.chop(tail.size());
        result = oidString.translateToOid(autoInitMib, 0);
        if (!result.isEmpty()) result.append(tail);
    } else if (bestGuess) {
        result = oidString.translateToOid(autoInitMib, bestGuess);
    }

    return result;
}

/*****************************************************************/
/*!
 * \brief NetSNMP::get short form of NetSnmpSestion::get method
 * Sometimes quicker to code but is less efficient since the Session is created and destroyed with each call.
 * Takes all the parameters of both NetSnmpSestion constructor and NetSnmpSestion::get
 * \param map paremeters
 * \return The list of values
 */
QList<SnmpValue> NetSNMP::get(const QVariantMap &map)
{
    NetSnmpSession sess(map);
    return sess.get(map);
}

/*****************************************************************/

QString NetSNMP::pError(const QString &progString)
{
    int xerr = snmp_errno; /*MTCRITICAL_RESOURCE */
    QString str = snmp_api_errstring(xerr);
    return QString("%1: %2").arg(progString, str);
}

/*****************************************************************/

void NetSNMP::initSnmp(const QString &appName)
{
    librariesInit(appName);
}

/*****************************************************************/

void NetSNMP::librariesInit(const QString &appName)
{
    static bool haveInited = false;

    if (haveInited)
        return;
    haveInited = 1;

    SOCK_STARTUP;

    netsnmp_ds_set_boolean(NETSNMP_DS_LIBRARY_ID,
                           NETSNMP_DS_LIB_QUICK_PRINT, 1);
//    snmp_set_mib_warnings(0);
//    snmp_set_mib_errors(0);
    snmp_set_save_descriptions(1);
    init_snmp(appName.toLatin1());

    netsnmp_ds_set_boolean(NETSNMP_DS_LIBRARY_ID,
                           NETSNMP_DS_LIB_DONT_BREAKDOWN_OIDS, 1);
    netsnmp_ds_set_int(NETSNMP_DS_LIBRARY_ID,
                       NETSNMP_DS_LIB_PRINT_SUFFIX_ONLY, 1);
    netsnmp_ds_set_int(NETSNMP_DS_LIBRARY_ID,
                       NETSNMP_DS_LIB_OID_OUTPUT_FORMAT, NETSNMP_OID_OUTPUT_SUFFIX);
}

/*****************************************************************/

bool NetSNMP::addMibDir(const QString &mibDir)
{
    int result = 0;      /* Avoid use of uninitialized variable below. */
    if (!mibDir.isEmpty()) {
        result = add_mibdir(mibDir.toLatin1());
    }
    if (result) {
       if (verbose) qWarning() << "snmp_add_mib_dir: Added mib dir" <<  mibDir;
    } else {
       if (verbose) qWarning() << "snmp_add_mib_dir: Failed to add" << mibDir;
    }
    return result;
}

/*****************************************************************/

bool NetSNMP::readMib(const QString &mibFile)
{
    if (mibFile.isEmpty()) {
        if (get_tree_head() == NULL) {
            if (verbose) qWarning() << "snmp_read_mib: initializing MIB";
            netsnmp_init_mib();
            if (get_tree_head()) {
                if (verbose) qWarning() << "done";
            } else {
                if (verbose) qWarning() << "failed";
            }
        }
    } else {
        if (verbose) qWarning() << "snmp_read_mib: reading MIB: " << mibFile;
        if (mibFile != "ALL") {
            read_mib(mibFile.toLatin1());
        } else {
            read_all_mibs();
        }
        if (get_tree_head()) {
            if (verbose) qWarning() << "done";
        } else {
            if (verbose) qWarning() << "failed";
        }
    }
    return get_tree_head();
}

/*****************************************************************/

bool NetSNMP::readModule(const QString &module)
{
    if (module == "ALL") {
        read_all_mibs();
    } else {
        netsnmp_read_module(module.toLatin1());
    }
    if (get_tree_head()) {
       if (verbose) qWarning() << "Read " << module;
    } else {
       if (verbose) qWarning() <<"Failed reading " << module;
    }
    return get_tree_head();
}

/*****************************************************************/



