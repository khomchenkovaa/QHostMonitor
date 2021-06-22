#ifndef TESTMETHOD_H
#define TESTMETHOD_H

#include "PropertyHelper.h"
#include "tEnums.h"

#include <QMap>
#include <QDateTime>
#include <QVariant>

namespace SDPO {

/*****************************************************************/

enum class TMethodID {
    Unknown = -1,   // Not defined
    Ping = 0,       // Ping
    Tcp,            // TCP
    Url,            // URL
    DriveSpace,     // Disk free space [ df -h ]
    FileSize,       // Folder size, [ du -s ]
    FileExists,     // File Availability,
    Externalprg,    // External
    SSH,            // SSH test
    FileCRC,        // File Integrity
    Oracle,         // Oracle
    UNC,            // UNC
    Interbase,      // Interbase
    MSSQL,          // MS_SQL
    MySQL,          // MySQL
    Postgre,        // PGSQL
    Sybase,         // Sybase
    Process,        // Process
    Service,        // Service
    SNMP,           // SNMP_Get
    NTLog,          // NT Event Log
    CPU,            // CPU Usage
    CompareFiles,   // File Compare
    ODBC,           // ODBC
    SMTP,           // SMTP
    POP3,           // POP3
    IMAP,           // IMAP
    DNS,            // DNS
    Ldap,           // LDAP
    Trace,          // Trace
    CountFiles,     // Count Files
    RAS,            // RAS
    PerfCounter,    // Performance Counter
    Script,         // Active Script
    UDP,            // UDP
    NTP,            // NTP
    Radius,         // Radius
    HTTP,           // HTTP
    TextLog,        // Text Log
    ShellScript,    // Shell Script
    TempMonitor,    // Temperature Monitor
    TrafficMonitor, // Network Traffic,
    SNMPtrap,       // SNMP Trap
    WMI,            // WMI
    MailRelay,      // Mail Relay
    DICOM,          // DICOM
    DominantProcess,// Dominant Process
    DHCP,           // DHCP test
    HMmonitor,      // SDPO Monitor
    Nagios          // Nagios plugin
};

typedef QList<TMethodID> TMethodIdList;

/*****************************************************************/

struct TestGroup
{
    int id;
    QString name;
    QString icon;
    int parent;
    QStringList description;

    QString getDescription() const {
        return description.join("\n");
    }
};

/*****************************************************************/

struct TestMethodMetaInfo
{
    TMethodID   id;
    QString     name;
    QString     title;
    QString     text;
    QString     icon;
    QString     html;
    int         parent;
    bool        active;
    QString     namePattern;
    QString     commentPattern;
    QStringList description;

    QString getDescription() const {
        return description.join("\n");
    }
};

/***********************************************/

struct TestResult {
    TestStatus status;
    QVariant   reply;
    QString    replyDesc;
    QString    error;
    QDateTime  date;

    TestResult() {
        clear();
    }

    void clear() {
        status = TestStatus::Unknown;
        reply.clear();
        replyDesc.clear();
        error.clear();
        date = QDateTime::currentDateTime();
    }

    void reverse() {
        switch (status) {
        case TestStatus::HostAlive:   status = TestStatus::Bad; break;
        case TestStatus::NoAnswer:    status = TestStatus::Ok;  break;
        case TestStatus::Ok:          status = TestStatus::Bad; break;
        case TestStatus::Bad:         status = TestStatus::Ok;  break;
        case TestStatus::BadContents: status = TestStatus::Ok;  break;
        default: break;
        }
    }

    SimpleStatusID simpleStatus(const bool unknownIsBad = false, const bool warningIsBad = false) const {
        SimpleStatusID result = SimpleStatusID::UNKNOWN;
        switch (status) {
            case TestStatus::HostAlive:
            case TestStatus::Ok:
            case TestStatus::Normal:
                result = SimpleStatusID::UP;
                break;
            case TestStatus::NoAnswer:
            case TestStatus::Bad:
            case TestStatus::BadContents:
                result = SimpleStatusID::DOWN;
                break;
            case TestStatus::Warning:
                result = SimpleStatusID::WARNING;
                break;
            default:
                break;
        }
        // Unknown, might be processed as “bad” statuses depending on “unknownIsBad” option
        if (unknownIsBad && result==SimpleStatusID::UNKNOWN) result = SimpleStatusID::DOWN;

        // Warning, might be processed as “bad” statuses depending on “warningIsBad” option
        if (warningIsBad && result==SimpleStatusID::WARNING) result = SimpleStatusID::DOWN;
        return result;
    }
};

/*!
 * Base class for all tests
 */
class TestMethod : public QObject
{
    Q_OBJECT

    //! Represents short description of a testing method
    Q_PROPERTY(QString TestMethod READ getTestMethod)

    //! Represents short description of a testing method
    Q_PROPERTY(QString MethodName READ getTestMethodName)

    //! Returns integer number that represents test method (test that has triggered action execution)
    Q_PROPERTY(QString MethodID READ getTestMethodID)

    //! Provides information about tested object,
    //! variable returns string value like <tt>'MS SQL database "MainLog" on 192.168.10.15'</tt>.
    //! This variable offers more information than <tt>%TestMethod%</tt> variable
    Q_PROPERTY(QString TestedObjectInfo READ getTestedObjectInfo)

protected:
    TMethodID  m_TMethodID;
    QString    m_NamePattern;
    QString    m_CommentPattern;
    TestResult m_Result;
    QString    m_Log;

public:
    explicit TestMethod(TMethodID methodId, QObject *parent = nullptr);
    virtual ~TestMethod();

    // properties
    int getTestMethodID() const { return static_cast<int>(m_TMethodID); }
    QString getTestMethodName() const { return metaName(m_TMethodID); }
    virtual QString getTestMethod() const { return metaName(m_TMethodID); }
    virtual QString getTestedObjectInfo() const { return QString(); }

    // getters and setters
    TMethodID getTMethodID() const { return m_TMethodID; }
    void setTMethodID(const TMethodID value) { m_TMethodID = value; }
    QString getNamePattern() const { return m_NamePattern; }
    void setNamePattern(const QString value) { m_NamePattern = value; }
    QString getCommentPattern() const { return m_CommentPattern; }
    void setCommentPattern(const QString value) { m_CommentPattern = value; }
    TestResult getResult() const { return m_Result; }
    QString getLog() const { return m_Log; }

    // command
    virtual void run();
    virtual QString getCommand() const { return QString(); }
    virtual void parseResult(QString data) { m_Result.reply = data; }

    virtual TestMethod *clone();
    QString getDefaultName() const;
    QString getDefaultComments() const;
    virtual QVariantMap toMap() const;

protected:
    QString getTranslated(const QString &name, const bool translate) const;
    void writeLogTitle();

signals:
    void testSuccess();
    void testFailed();
    void testStarted();

public: // static
    static QVector<TestGroup> groups;
    static QVector<TestMethodMetaInfo> metaInfo;
    static TestMethodMetaInfo metaInfoItem(TMethodID methodID);
    static QString metaName(TMethodID methodID);
    static TMethodID methodIdFromString(const QString name);

private:
    QVariantMap setVars(const QStringList &params) const;

};

} // namespace SDPO

#endif // TESTMETHOD_H
