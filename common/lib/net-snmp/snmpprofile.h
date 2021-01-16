#ifndef SNMPPROFILE_H
#define SNMPPROFILE_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include <QString>
#include <QList>

namespace SDPO {

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


} // namespace SDPO

#endif // SNMPPROFILE_H
