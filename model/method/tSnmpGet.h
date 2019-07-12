/*!
 * \class SDPO::TSnmpGet
 * \brief The SNMP test allows you to control parameters of network devices
 *
 * The Simple Network Management Protocol is the Internet standard protocol for exchanging management information between management console applications and managed entities (hosts, routers, bridges, hubs).
 * Using this powerful test HostMonitor can control many different parameters of network devices.
 * In addition to the common test parameters, the SNMP test has the following options:
 *
 * <b> Agent address </b>
 *
 * Here you should provide a string specifying either a dotted-decimal IP address (e.g. 195.168.10.10)
 * or a host name that can be resolved to an IP address, an IPX address (in 8.12 notation),
 * or anEthernet address.
 * Also you may provide IPv6 addresses (e.g. fe80::370:ff56:fed5:22) and specify hostname with suffixes ::ipv4 or ::ipv6 (e.g. www.google.com::ipv4 or www.6bone.net::ipv6).
 * If you specify hostname without any suffix, HostMonitor will try to resolve name into IP address using IPv4 protocol.
 * If name cannot be resolved by IPv4 protocol, HostMonitor will try to use IPv6 protocol.
 * If you specify hostname with ::ipv4 (or ::ipv6) suffix, HostMonitor will use IPv4 (or IPv6) protocol only.
 *
 * Also you may specify port that is used by target SNMP agent.
 * This parameter is optional; port number has to be provided after a colon following the address of SNMP agent. (E.g. 195.168.10.10:161).
 * You cannot specify port number when target host specified by IPv6 address.
 *
 * <b> SNMP profile </b>
 *
 * Choose profile that stores credentials necessary for communication with SNMP agent.
 * You may select profile from drop-down list or click button beside the list to bring up SNMP Credentials dialog.
 *
 * \b Timeout
 *
 * This is the amount of time in milliseconds the program will wait for a response from the server before the request fails.
 *
 * \b Retries
 *
 * Specifies the communications retry count.
 *
 * <b> OID (object identifier) </b>
 *
 * The name that uniquely identifies the object for testing.
 * For example OID "1.3.6.1.2.1.2.1.0" represents the number of network interfaces on which your system can send/receive IP datagrams;
 * OID "1.3.6.1.2.1.6.9.0" represents the number of TCP connections for which the current state is either ESTABLISHED or CLOSE-WAIT; etc.
 * To get a list of valid OIDs for your SNMP enabled devices you should contact the vendor of the device.
 * They should be able to give you a MIB file that contains all the OIDs for the device.
 * If you cannot contact the vendor, try to find the file on the Internet.
 * Numerous free resources offer wide lists of MIB files for various devices (e.g. http://www.mibdepot.com/index.shtml)
 *
 * to be continued...
 *
 */

#ifndef TSNMPGET_H
#define TSNMPGET_H

#include "tTestMethod.h"

namespace SDPO {

class TSnmpGet : public TTestMethod
{
    Q_OBJECT

public:
    enum Condition {
        LessThan,MoreThan,EqualTo,DifferentFrom,
        Contain,NotContain,
        IncreaseBy,DecreaseBy,ChangeBy,
        IncByPercent,DecByPercent,ChangeByPercent,
        IncSec,DecSec,ChangeSec
    };
    Q_ENUMS(Condition)

private:

    Q_PROPERTY(QString HostAddr READ getHost)
    Q_PROPERTY(QString MibNameShort READ getMibName)

    AUTO_PROPERTY(QString, Host)
    AUTO_PROPERTY(QString, Community)
    AUTO_PROPERTY(QString, MibOid)
    AUTO_PROPERTY(QString, MibName)
    AUTO_PROPERTY(QString, OidFullName)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(int, Retries)
    AUTO_PROPERTY(QString, Value)
    AUTO_PROPERTY(QString, Version)

    Condition a_Condition;

public:    
    explicit TSnmpGet(QObject *parent = nullptr);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // getters and setters
    Condition getCondition() const { return a_Condition; }
    void setCondition(const Condition value) { a_Condition = value; }

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE;
    virtual void parseResult(QString data) Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

    // helpers
    QString conditionToString(Condition cond) const;
    Condition conditionFromString(QString condStr, Condition condDefault) const;
};

} // namespace SDPO

#endif // TSNMPGET_H
