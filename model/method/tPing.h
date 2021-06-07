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
 * <b> Alert if loss ratio N% (or more)</b>
 *
 * A packet loss threshold can be specified for a Ping test, based on which the test status is determined.
 *
 * <b> Display mode </b>
 *
 * Select 1 of 3 options that determine what information HostMonitor will display in the Reply field
 * \li <tt>Reply time</tt> - the "Reply" field will represent average reply time.
 * \li <tt>% of lost</tt> - display percentage of lost packets
 * \li <tt>% of received</tt> - display percentage of received packets
 *
 * HostMonitor may set 6 statuses for Ping tests:
 * \li <tt>"Ok"</tt> - this status used when "Jitter" option is enabled and Jitter time within specified limit (when "Alert if lost ratio" option enabled, it should be within specified limit as well)
 * \li <tt>"Host is alive"</tt> - this status used when "Jitter" option was not enabled and loss ratio within specified limit
 * \li <tt>"Bad"</tt> - this status means either Jitter or Loss ratio is out of the limits
 * \li <tt>"No answer"</tt> - HostMonitor sets "no answer" status when does not receive any response from target system
 * \li <tt>"Unknown host"</tt> - host name could not be resolved to IP address
 * \li <tt>"Unknown"</tt> - test performed by Remote Monitoring Agent and there is some RMA related error (e.g. HostMonitor cannot connect to the agent)
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

#include "testmethod.h"

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

class TPing : public TestMethod
{
    Q_OBJECT
    Q_CLASSINFO("name", "Ping")
    Q_CLASSINFO("text", "Ping test")
    Q_CLASSINFO("icon", ":/img/test/ping.png")
    Q_CLASSINFO("active", "yes")
    Q_CLASSINFO("testname", "%TestMethod% %host%")
    Q_CLASSINFO("comment", "Ping %host%")
    Q_CLASSINFO("description", "The ping command verifies connections to remote computers, routers and other network components by sending ICMP (Internet Control Message Protocol) echo packets to the remote component and listening for echo reply packets. It`s best to use the Ping method to check a remote connection in general. To check specific services and conditions, HostMonitor provides a number of special test types.")

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
    explicit TPing(QString addr, QObject *parent = nullptr);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE;
    virtual void parseResult(QString data) Q_DECL_OVERRIDE;

    virtual TestMethod *clone() Q_DECL_OVERRIDE;

private: // functions
    QString displayModeToString(DisplayMode mode);
    bool errorScan(const QString &line, TestResult &result);
    bool getPercentLossStatistics(const QString &line, PingStat &stat);
    bool getRoundTrip(const QString &line, PingStat &stat);

};

} // namespace SDPO

#endif // TPING_H
