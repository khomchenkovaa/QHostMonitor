#ifndef SDPO_NET_SNMP_H
#define SDPO_NET_SNMP_H

#include "mibnode.h"
#include "snmpvar.h"
#include "snmppdu.h"

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

/*****************************************************************/

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

class SnmpTransport {
    netsnmp_transport *ptr = nullptr;

public:
    SnmpTransport(void *pointer = nullptr) {
        this->ptr = static_cast<netsnmp_transport*>(pointer);
    }

    QString addrString(const SnmpPdu& pdu) const {
        if (ptr != nullptr &&ptr->f_fmtaddr != nullptr) {
            return ptr->f_fmtaddr(ptr, pdu.ptr->transport_data,
                                       pdu.ptr->transport_data_length);
        }
        return "<UNKNOWN>";
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

    static SnmpValue fromVar(SnmpVar var);
    static SnmpValue fromError(const MibOid& mibOid, const QString& err);
};

typedef QList<SnmpValue> SnmpValueList;
typedef QList<SnmpValueList> SnmpValueTable;

/*****************************************************************/

class NetSNMP {
public:
    static QString appName;      ///< snmp application name
    static bool autoInitMib;     ///< enable automatic MIB loading at session creation time
    static bool useLongNames;    ///< non-zero to prefer longer mib textual identifiers rather than just leaf indentifiers
    static int useSprintValue;   ///< non-zero to enable formatting of response values using the snmp libraries "snprint_value"
    static int useEnums;         ///< non-zero to return integers as enums and allow sets using enums where appropriate
    static int useNumeric;       ///< non-zero to return object tags as numeric OID's instead of converting to textual representations.
    static MibNode mibRoot;      ///< tied hash to access libraries internal mib tree structure parsed in from mib files
    static int mibWarnings;
    static int mibErrors;
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
    static void initSnmp();
    static bool addMibDirs(const QStringList& mibDirs);
    static bool addMibFiles(const QStringList& mibFiles);
    static bool loadModules(const QStringList& mibModules);
    static QString translateObj(const QString& obj, bool toLongName = false, bool includeModuleName = true);

    static QString pError(const QString& progString);
    static QString apiErrstring(int errCode) {
        return snmp_api_errstring(errCode);
    }
};


/*****************************************************************/

} // namespace SDPO

#endif // SDPO_NET_SNMP_H
