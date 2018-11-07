/* CPU Usage test checks the percentage of CPU utilization for the local or remote machine.
 * This test can monitor hosts with the following operational systems:
 * • Microsoft Windows NT 4.0, Windows 2000, Windows XP Professional, Windows Server 2003, Windows Vista, Windows Server 2008 and Windows 7;
 * • Novell Netware 4+;
 * • using RMA for UNIX HostMonitor can monitor FreeBSD, Linux, OpenBSD and Solaris systems.
 *
 * In addition to the common test parameters the CPU Usage test has the following options:
 *
 * Computer
 * Specify name of the target computer, it can be:
 * • "<local computer>" or an empty string when using the test for a local machine;
 * • a Universal Naming Convention (UNC) name of the computer (like "\\Server1") when using this test for remote Windows machines;
 * • a server name (like "server1") or NDS tree name (like ".bigcompany.ifx.department2.sever1") when using this test for Novell Netware server.
 *
 * OS
 * Select the type of OS on the target computer (Windows, Novell Netware or UNIX)
 *
 * Alert when CPU usage more than
 * HostMonitor will mark the host as "Bad" and start alert actions when the percentage of CPU usage becomes more than specified.
 *
 * Connect as
 * To check CPU usage on remote Windows system you may mark this option and provide a username and password for a connection to the target computer.
 *
 * Note #1: To monitor CPU utilization on a remote Windows NT* system, make sure you have the Remote Registry service started on the remote system (to monitor processes HostMonitor must have access to the registry).
 * Windows NT 4.0 does not have this service installed by default; however you can find this service in the Resource Kit for Windows NT 4.0.
 * Also to use this test for remote Windows computers you must have the permissions to do that (administrator privilege on the remote computer).
 * Here "Windows NT" means system based on NT technology, including Microsoft Windows NT 4.0, Windows 2000, Windows XP, Windows Vista, Windows Server 2003, Windows Server 2008, Windows 7.
 *
 * Note #2: To check Novell Netware servers, HostMonitor uses the functionality of the Novell Netware client.
 * Therefore, the Novell Netware client software has to be installed on the machine where HostMonitor is running.
 *
 * Note #3: To check UNIX systems you may use Remote Monitoring Agent installed on UNIX-machine.
 * Current version of RMA does not use "Computer", "OS" and "Connect as" parameters of the test and checks the system where agent is running.
 */
#ifndef IOCPUUSAGECONVERTER_H
#define IOCPUUSAGECONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_COMPUTER    "Computer"
#define SP_OS          "OS"
#define SP_MAXCPUUSAGE "MaxCPUUsage"
#define SP_USERNAME    "Username"
#define SP_PASSWORD    "Password"

namespace SDPO {

class IOCPUUsageConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOCPUUsageConverter(QObject *parent = 0);

virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IOCPUUSAGECONVERTER_H
