/*!
 * \class SDPO::TPing
 * \brief The Ping method checks a remote connection
 *
 * The ping command verifies connections to remote computers, routers and other network components by sending ICMP (Internet Control Message Protocol) echo packets to the remote component and listening for echo reply packets.
 * It's best to use the Ping method to check a remote connection in general.
 * To check specific services and conditions, HostMonitor provides a number of special test types.
 *
 * In addition to the common test parameters, the Ping test has the following options:
 *
 * \b Address
 *
 * Here you should provide the domain name (e. g. <tt>www.yahoo.com</tt>) or IP address (e. g. <tt>204.71.200.68</tt>) of the host that you wish to monitor.
 * Also you may provide IPv6 addresses (e.g. <tt>fe80::370:ff56:fed5:22</tt>) and specify hostname with suffixes <tt>::ipv4</tt> or <tt>::ipv6</tt> (e.g. <tt>www.google.com::ipv4</tt> or <tt>www.6bone.net::ipv6</tt>).
 *
 * If you specify hostname without any suffix, HostMonitor will try to resolve name into IP address using IPv4 protocol.
 * If name cannot be resolved by IPv4 protocol, HostMonitor will try to use IPv6 protocol.
 * If you specify hostname with <tt>::ipv4</tt> (or <tt>::ipv6</tt>) suffix, HostMonitor will use IPv4 (or IPv6) protocol only.
 *
 * \b Note: on Windows NT 4.0, Windows 2000 and Windows XP SP1 IPv6 protocol is not supported. You may use menu <em>Tools -> Local Info</em> to check is your system IPv6 ready.
 *
 * Also, a range of IPv4 addresses (e.g. <tt>10.10.1.100 – 10.10.1.254</tt>) rather than a single address can be specified.
 * In this case, HostMonitor will create a separate test for each of the addresses within that range.
 *
 * \b Timeout
 *
 * Specify a timeout interval in milliseconds.
 *
 * <b> Packet size </b>
 *
 * Specify the size of ECHO packets. This parameter is optional.
 * If its value is 0 (default value), HostMonitor will use global Packet Size parameter specified on <em>Ping/Trace</em> page in the <em>Options</em> dialog.
 *
 * \b Packets
 *
 * Specify the number of ECHO packets.
 *
 * <b> Don’t fragment </b>
 *
 * This option tells HostMonitor to set “Do Not Fragment” bit on the ping packet.
 *
 * <b> Time to Live </b>
 *
 * Time to Live parameter is common for all Ping tests; specify this parameters on <em>Ping/Trace page</em> in the <em>Options</em> dialog.
 *
 * <b> Status is bad when N (or more) % of packet lost </b>
 *
 * A packet loss threshold can be specified for a Ping test, based on which the test status is determined.
 * That is, in HostMonitor version 1.xx a test was considered failed if no echo packets were received (100% loss).
 * Now you can set the packet loss limit.
 *
 * <b> Display mode </b>
 *
 * Select 1 of 3 options that determine what information HostMonitor will display in the Reply field
 * \li <tt>Reply time</tt> - the "Reply" field will represent average reply time.
 * \li <tt>% of lost</tt> - display percentage of lost packets
 * \li <tt>% of received</tt> - display percentage of received packets
 */
/*
 * Other pingers: src: http://www.true-random.com/homepage/projects/pinger/index.html
 * arping - uses ARP
 * bing - does ICMP pings plus computing point to point throughput
 * dhcping - uses DHCP
 * echoping - uses TCP or UDP
 * fping - does ping to a list of targets
 * httping - uses HTTP
 * mailping - uses SMTP (and TCP)
 * oping - can send ICMP packets to multiple hosts in parallel and wait for all ECHO_RESPONSE packets to arrive
 * paping - uses TCP/IP
 * pathping - shows more information than ping and it's a Microsoft Windows program, similar to traceroute
 * ping6 - uses IPv6
 * smtpping - uses SMTP
 */
#ifndef TPING_H
#define TPING_H

#include "tTestMethod.h"

#define PING_COMMAND  "/bin/ping -n -U"
#define PING6_COMMAND "/bin/ping6 -n -U"

namespace SDPO {

struct PingStat {
    int transmitted;
    int received;
    int percentLoss;
    double rttMin;
    double rttAvg;
    double rttMax;

    PingStat() {
        transmitted = 0;
        received = 0;
        percentLoss = 200;
        rttMin = -1.0;
        rttAvg = -1.0;
        rttMax = -1.0;
    }
};

class TPing : public TTestMethod
{
    Q_OBJECT

public:
    //! Display mode enum
    enum DisplayMode {
        Time,     //!< Reply time - the "Reply" field will represent average reply time.
        Lost,     //!< % of lost - display percentage of lost packets
        Received  //!< % of received - display percentage of received packets
    };
    Q_ENUMS(DisplayMode)

    enum PingProtocol { Unknown, IPV4, IPV6 };

private:
    Q_PROPERTY(QString Host READ getAddress)
    Q_PROPERTY(QString HostAddr READ getAddress)

    AUTO_PROPERTY(QString, Address)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(int, PacketSize)
    AUTO_PROPERTY(int, Packets)
    BOOL_PROPERTY(DontFragment)
    AUTO_PROPERTY(int, TimeToLive)
    AUTO_PROPERTY(int, BadCriteria)
    AUTO_PROPERTY(DisplayMode, DisplayMode)

public:
    explicit TPing(QString addr, QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const;
    virtual QString getTestedObjectInfo() const;

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE;
    virtual void parseResult(QString data) Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

private: // functions
    QString displayModeToString(DisplayMode mode);
    bool errorScan(const QString &line, TTestResult &result);
    bool getPercentLossStatistics(const QString &line, PingStat &stat);
    bool getRoundTrip(const QString &line, PingStat &stat);


};

} // namespace SDPO

#endif // TPING_H
