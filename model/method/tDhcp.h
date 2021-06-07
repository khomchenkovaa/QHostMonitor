/*!
 * \class SDPO::TDhcp
 * \brief The DHCP test allows you to monitor DHCP servers.
 *
 * HostMonitor verifies the DHCP server by sending request for IP address.
 * HostMonitor sets “Host is alive” status when DHCP server properly responds within specified timeout, whatever it replies with NAK or ACK packet.
 * Otherwise HostMonitor may set “Bad” (invalid reply from server) or “No answer” status.
 *
 * In addition to the common test parameters, the DHCP test has the following options:
 *
 * \b Host
 *
 * This is the domain name or IP address of the machine running the DHCP server that you wish to monitor.
 *
 * \b Timeout
 *
 * This is the amount of time in milliseconds the program will wait for a response from the server before the request fails.
 *
 * <b> Request IP </b>
 *
 * Here you may specify IP address that will be requested or keep default value <current local IP>
 */
/* Realization
 * This test uses dhcping utility.
 * For CentOS 6.* it available form the epel repository (yum install dhcping)
 * don't forget install as setuid root:
 * chmod 4755 /usr/bin/nmap
 *
 * Command:
 * dhcping -s <Host> -t <Timeout> -c <Request IP>
 *
 * Return:
 * 0 - Ok ("Host is alive")
 * 1 - Something wrong
 */

#ifndef TDHCP_H
#define TDHCP_H

#include "testmethod.h"

#define DHCP_CURRENT_LOCAL_IP "<current local IP>"

namespace SDPO {

class TDhcp : public TestMethod
{
    Q_OBJECT

    AUTO_PROPERTY(QString, Host)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(QString, RequestIp)

public:
    explicit TDhcp(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE;

    virtual TestMethod *clone() Q_DECL_OVERRIDE;

    static QString currentLocalIP();
    static QString currentMacAddress();

};

} // namespace SDPO

#endif // TDHCP_H
