#ifndef TMETHOD_H
#define TMETHOD_H

#include <QString>
#include <QIcon>
#include <QVector>

namespace SDPO {

/*****************************************************************/

enum class TMethodID {
    Ping = 0, // Ping
    TCP, // TCP
    URL, // URL
    DriveSpace, // Disk free space [ df -h ]
    FileSize, // Folder size, [ du -s ]
    FileExists, // File Availability,
    Externalprg, // External
    SSH, // SSH test
    FileContents, // File Integrity
    Oracle, // Oracle
    UNC, // UNC
    Interbase, // Interbase
    MSSQL, // MS_SQL
    MySQL, // MySQL
    Postgre, // PGSQL
    Sybase, // Sybase
    Process, // Process
    Service, // Service
    SNMP, // SNMP_Get
    NTLog, // NT Event Log
    CPU, // CPU Usage
    FileCompare,
    ODBC, // ODBC
    SMTP, // SMTP
    POP3, // POP3
    IMAP, // IMAP
    DNS, // DNS
    Ldap, // LDAP
    Trace, // Trace
    CountFiles, // Count Files
    RAS, // RAS
    PerfCounter, // Performance Counter
    Script, // Active Script
    UDP, // UDP
    NTP, // NTP
    Radius, // Radius
    HTTP, // HTTP
    TextLog, // Text Log
    ShellScript, // Shell Script
    TempMonitor, // Temperature Monitor
    TrafficMonitor, // Network Traffic,
    SNMPtrap,
    WMI,
    MailRelay,
    DICOM,
    DominantProcess,
    DHCP,
    HMmonitor,
    Empty
};

class TGroup
{
public:
    int id;
    QString name;
    QIcon icon;
    int parent;
    QStringList description;

    static QVector<TGroup> tGroupList;
};


class TMethod
{
public:
    TMethodID id;
    QString name;
    QString title;
    QString text;
    QIcon icon;
    int parent;
    bool active;
    QString namePattern;
    QString commentPattern;
    QStringList description;

    static QVector<TMethod> tMethodList;


    static QString toName(TMethodID method);
    static TMethodID fromString(const QString name);
};

} // namespace SDPO

#endif // TMETHOD_H
