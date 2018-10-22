#ifndef IOTEXTFILE_H
#define IOTEXTFILE_H

#include "tEnums.h"
#include "method/sdpoTestMethodConverters.h"

QT_BEGIN_NAMESPACE
class QTextStream;
QT_END_NAMESPACE

namespace SDPO {

// Defaults (optional)
static QString DEFAULT_SCHEDULE      = QStringLiteral("DefaultSchedule");
static QString DEFAULT_ALERT_PROFILE = QStringLiteral("DefaultAlertProfile");
static QString DEFAULT_INTERVAL      = QStringLiteral("DefaultInterval");
static QString DEFAULT_COMMENT       = QStringLiteral("DefaultComment");
static QString DEFAULT_FOLDER        = QStringLiteral("DefaultFolder");

// Special commands (optional)
static QString CMD_IMPORT_MODE   = QStringLiteral("ImportMode");
static QString CMD_CREATE_FOLDER = QStringLiteral("CreateFolder");

// Common required parameters
static QString PRM_METHOD = QStringLiteral("Method");
static QString PRM_TITLE  = QStringLiteral("Title");

// Common optional parameters
static QString PRM_LINKED_TO      = QStringLiteral("LinkedTo");
static QString PRM_NAME_PATTERN   = QStringLiteral("NamePattern");
static QString PRM_DEST_FOLDER    = QStringLiteral("DestFolder");
static QString PRM_RM_AGENT       = QStringLiteral("RMAgent");
static QString PRM_COMMENT        = QStringLiteral("Comment");
static QString PRM_CMNT_PATTERN   = QStringLiteral("CmntPattern");
static QString PRM_RELATED_URL    = QStringLiteral("RelatedURL");
static QString PRM_SCHEDULE       = QStringLiteral("Schedule");
static QString PRM_SCHEDULE_MODE  = QStringLiteral("ScheduleMode");
static QString PRM_INTERVAL       = QStringLiteral("Interval");
static QString PRM_SCHEDULE_DAY   = QStringLiteral("ScheduleDay");
static QString PRM_SCHEDULE_TIME  = QStringLiteral("ScheduleTime");
static QString PRM_SCHEDULE_EXPR  = QStringLiteral("ScheduleExpr");
static QString PRM_ALERTS         = QStringLiteral("Alerts");
static QString PRM_REVERSE_ALERT  = QStringLiteral("ReverseAlert");
static QString PRM_UNKNOWN_IS_BAD = QStringLiteral("UnknownIsBad");
static QString PRM_WARNING_IS_BAD = QStringLiteral("WarningIsBad");
static QString PRM_USE_WARNING    = QStringLiteral("UseWarning");
static QString PRM_WARNING_EXPR   = QStringLiteral("WarningExpr");
static QString PRM_USE_NORMAL     = QStringLiteral("UseNormal");
static QString PRM_NORMAL_EXPR    = QStringLiteral("NormalExpr");
static QString PRM_TUNEUP_REPLY   = QStringLiteral("TuneupReply");
static QString PRM_TUNE_REPLY_EXP = QStringLiteral("TuneReplyExp");
static QString PRM_USE_COMMON_LOG = QStringLiteral("UseCommonLog");
static QString PRM_PRIV_LOG       = QStringLiteral("PrivateLog");
static QString PRM_PRIV_LOG_MODE  = QStringLiteral("PrivLogMode");
static QString PRM_COM_LOG_MODE   = QStringLiteral("CommLogMode");
static QString PRM_DEPENDS_ON     = QStringLiteral("DependsOn");
static QString PRM_DEPEND_EXPR    = QStringLiteral("DpExpression");
static QString PRM_DEPEND_EXPR_ID = QStringLiteral("DpExprID");
static QString PRM_DEPEND_STATUS  = QStringLiteral("DpOStatus");
static QString PRM_DEPEND_STAT_ID = QStringLiteral("DpOStatusID");
static QString PRM_SYNC_COUNTERS  = QStringLiteral("SyncCounters");
static QString PRM_SYNC_ALERTS    = QStringLiteral("SyncAlerts");
static QString PRM_MASTER_TEST_ALIVE            = QStringLiteral("MasterTest-Alive");
static QString PRM_MASTER_TEST_ALIVE_OR_UNKNOWN = QStringLiteral("MasterTest-AliveOrUnknown");
static QString PRM_MASTER_TEST_DEAD             = QStringLiteral("MasterTest-DeadOrUnknown");
static QString PRM_MASTER_TEST_DEAD_OR_UNKNOWN  = QStringLiteral("MasterTest-Dead");

class HMListService;
class TNode;
class TTest;

struct IOTextFileCmd {
    int line;
    QString command;
    QString key;
    QString value;

    IOTextFileCmd() {
        line = -1;
    }

    IOTextFileCmd(const QString &key, const QString &value) {
        line = -1;
        this->key = key;
        this->value = value;
        this->command = key + " = " + value;
    }

    IOTextFileCmd(int lineNum, QString &lineRecord) {
        line = lineNum;
        command = lineRecord;
        QStringList record = lineRecord.split("=");
        key = record.at(0).trimmed();
        value = record.at(1).trimmed();
    }
};

class IOTextFile : public QObject
{
    Q_OBJECT

public: // enums
    enum ImportMode { IM_ADD, IM_MODIFY, IM_REPLACE };
    Q_ENUM(ImportMode)

private:
    HMListService *m_HML;

    // defaults
    QString m_fileName;
    QString m_defaultSchedule;
    QString m_defaultAlertProfile;
    int     m_defaultInterval;
    QString m_defaultComment;
    QString m_defaultFolder;
    ImportMode m_ImportMode;

    // helpers
    TTest  *m_curTest;
    IOTestMethodConverter *m_curMethodConverter;
    QMap<QString,IOTextFileCmd> m_testProps;
    QStringList m_linkedTo;
    QStringList m_Breakers;
    QStringList m_ScheduleMode;
    int m_lineCnt;
    int m_foldersCnt;
    int m_testsAdded;
    int m_testsChanged;
    int m_errorsCnt;
    int m_warningsCnt;

    void addTest();
    void setTestProperties();
    void createLinks();
    IOTestMethodConverter *getConverter(TMethodID methodId);
    void writeFolder(QTextStream &out, TNode *parent);
    void writeTest(QTextStream &out, TTest *test);

public:    
    explicit IOTextFile(HMListService *hml, QString fileName, QObject *parent = 0);
    ~IOTextFile();

signals:
    void importMessage(QString message);
    void importMessageAppend(QString append);
    void importDone(int folders, int tests, int changed, int errors, int warnings);

public slots:
    bool validateImportTextFile(QString &errorMsg, int &foldersCnt, int &testsCnt);
    void importTextFile();
    bool exportTextFile(bool incFolder, bool incLinks, int expType);
};

} // namespace SDPO

#endif // IOTEXTFILE_H
