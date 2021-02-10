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
    default: break;
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
 * \brief initSnmp is equivalent to calling the snmp library init_snmp
 */
void NetSNMP::initSnmp(const QString& appName)
{
    snmp_set_do_debugging(1);
    snmp_set_mib_warnings(0);
    snmp_set_mib_errors(0);
    snmp_set_save_descriptions(1);
    init_snmp(appName.toLatin1().data());
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
        if (!MibNode::addMibDir(mibDir)) return false;
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
        if (!MibNode::readMib(mibFile)) return false;
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
        if (!MibNode::readModule(module)) return false;
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

QString NetSNMP::pError(const QString &progString)
{
    int xerr = snmp_errno; /*MTCRITICAL_RESOURCE */
    QString str = snmp_api_errstring(xerr);
    return QString("%1: %2").arg(progString, str);
}

/*****************************************************************/
