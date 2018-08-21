#ifndef TTEST_H
#define TTEST_H

#include "PropertyHelper.h"
#include "utils.h"
#include <QDateTime>
#include <QVariant>
#include <QMetaEnum>
#include <QPair>
#include "tEnums.h"
#include "tNode.h"
#include "tAgent.h"
#include "tSchedule.h"
#include "method/tTestMethod.h"

namespace SDPO {

class TTest;
class TestAction;

typedef QPair<TTest*,int> TTestPair;

class TTest : public TNode
{
    Q_OBJECT

    static int failureCount;

    BOOL_PROPERTY(Enabled)
    BOOL_PROPERTY(Paused)

    // Log & Reports options
    BOOL_PROPERTY(UseCommonLog)
    AUTO_PROPERTY(int, CommonLogMode)
    BOOL_PROPERTY(UsePrivateLog)
    AUTO_PROPERTY(int, PrivateLogMode)
    BOOL_PROPERTY(ExcludeFromHtmlReport)
    BOOL_PROPERTY(ExcludeFromWmlReport)
    BOOL_PROPERTY(ExcludeFromDbfReport)

    // Dependencies
    AUTO_PROPERTY(int, DependencyMode)
    QList<TTestPair> m_masterTests;
    AUTO_PROPERTY(QString, DependencyCondition)
    AUTO_PROPERTY(QString, DependencyOtherwiseStatus)
    BOOL_PROPERTY(SynchronizeCounters)
    BOOL_PROPERTY(SynchronizeStatusAlerts)

    // Optional status propcessing
    BOOL_PROPERTY(ReverseAlert)
    BOOL_PROPERTY(UnknownIsBad) // Thread unknown status as Bad
    BOOL_PROPERTY(WarningIsBad) // Thread warning status as Bad
    BOOL_PROPERTY(UseWarningScript)
    BOOL_PROPERTY(UseNormalScript)
    BOOL_PROPERTY(TuneUpReply)
    AUTO_PROPERTY(QString, WarningScript)
    AUTO_PROPERTY(QString, NormalScript)
    AUTO_PROPERTY(QString, TuneUpScript)

    TTestMethod *m_test;
    TAgent* m_agent;
    TSchedule &m_schedule;
    QList<TNode*> m_links;

public:
    // TTest methods
    TTestMethod *test() const { return m_test; }
    void setTest(TTestMethod *test);

    // TAgent methods
    TAgent* agent() { return m_agent; }
    void setAgent(TAgent* value) { m_agent = value; }

    // Schedule methods
    void setRegularSchedule(const int interval, const QString schedName);
    void setIrregularSchedule(const int mode, const int schedDay, const QTime schedTime);
    void setByExpressionSchedule(const QString expr1, const QString expr2);
    int scheduleMode() const { return (int)m_schedule.getMode(); }
    int scheduleDay() const { return m_schedule.getScheduleDay(); }
    QTime scheduleTime() const { return m_schedule.getScheduleTime(); }
    QString scheduleExpr1() const { return m_schedule.getScheduleExpr1(); }
    QString scheduleExpr2() const { return m_schedule.getScheduleExpr2(); }

    // Links methods
    void addLink(TNode *node);
    int linkCount();
    QList<TNode *> links();
    void removeLink(TNode *node);

    // Dependencies
    QList<QPair<TTest*, int>> getMasterTests() const { return m_masterTests; }
    void setMasterTests(const QList<QPair<TTest*, int>> value) { m_masterTests.clear(); m_masterTests.append(value);  }

    /****************************************************
     *                 Test properties                  *
     ****************************************************/
private:
    // Represents the name of the test
    Q_PROPERTY(QString TestName READ testName)
    Q_PROPERTY(QString HostName READ testName)

    // Represents all numbers in the name of the test
    Q_PROPERTY(QString HostID READ hostId)

    // Represents unique ID of the test. TestID is always unique within an HML file
    Q_PROPERTY(QString TestID READ getID)

    // The time between two consecutive checks defined for the test
    Q_PROPERTY(QString Interval READ scheduleInterval)
    Q_PROPERTY(int Interval_Sec READ interval)
    Q_PROPERTY(int Interval_Min READ scheduleIntervalMin)

    // Name of a schedule assigned to the test
    Q_PROPERTY(QString ScheduleName READ scheduleName)

    // Represents a name of the remote agent that performs the test,
    // this variable returns the string "HostMonitor" when the test is performed by HostMonitor
    Q_PROPERTY(QString Agent READ agentName)

    // Name of the action profile
    AUTO_PROPERTY(int, AlertProfileID)
    Q_PROPERTY(QString AlertProfile READ alertProfileName)

    // Represents condition to set “Bad” status.
    // E.g. for Drive Free Space test this macro will represent minimum limit of free space defined for the test;
    // for TCP test it will display timeout;
    // for CPU Usage test it will show maximum limit for CPU usage value.
    Q_PROPERTY(QString AlertThreshold READ alertThreshold)

    // This variable works similar to %AlertThreshold% variable but it returns numeric value only (without any correspondent text comment).
    // E.g. %AlertThreshold% variable may return text like “Absent, MaxAge: 60”
    // when it is used in action triggered by “File/Folder Availability” test method.
    // In the same case %AlertThresholdValue% would return “60”.
    Q_PROPERTY(QString AlertThresholValue READ alertThreshold)

    // Master test name (provides information about 1st master test only)
    Q_PROPERTY(QString MasterTest READ masterTest)

    // Returns list of master tests (items separated by CRLF characters).
    // If test item depends on single master test or does not depend on any test,
    // %MasterTests% and %MasterTest% variables are equivalent
    Q_PROPERTY(QString MasterTests READ masterTests)

    // The specified private log file name
    AUTO_PROPERTY(QString, PrivateLog)

    // Related URL
    AUTO_PROPERTY(QString, RelatedURL)

    // Test's comment (whole comment, all lines separated by CRLF)
    Q_PROPERTY(QString TaskComment READ getComment)

    // Similar to %HostID%, but uses a test's comment instead the test's name
    Q_PROPERTY(QString CommentID READ commentId)

    // The time when the test was created
    Q_PROPERTY(QString CreatedTime READ createdTime)

    // The time when the test was last modified
    Q_PROPERTY(QString ModifiedTime READ modifiedTime)

public:
    QString testName() const;
    QString hostId() const { return testName().remove(QRegExp("[^\\d]+")); }
    QString testMethod() const { return m_test->getTestMethod(); }
    int testMethodId() const { return (int)m_test->getTMethodID(); }
    TMethodID methodId() const { return m_test->getTMethodID(); }
    QString testedObjectInfo() const { return m_test->getTestedObjectInfo(); }
    QString scheduleInterval() const { return m_schedule.intervalAsStr(); }
    void setInterval(const int value) { m_schedule.setInterval(value); }
    int interval() const { return m_schedule.getInterval(); }
    int scheduleIntervalMin() const { return m_schedule.getInterval() / 60; }
    void setScheduleName(const QString value) { m_schedule.setScheduleName(value); }
    QString scheduleName() const { return m_schedule.getScheduleName(); }
    QString alertProfileName() const;
    QString agentName() const { return m_agent->name(); }
    QString alertThreshold() const { return QString(); } //! TODO
    QString masterTest() const { return (m_masterTests.isEmpty()? QString(): m_masterTests.at(0).first->testName()); }
    QString masterTests() const;
    QString commentId() const { return getComment().remove(QRegExp("[^\\d]+")); }
    QString createdTime() const { return getCreatedAt().toString("yyyy.MM.dd hh:mm:ss"); }
    QString modifiedTime() const { return getModifiedAt().toString("yyyy.MM.dd hh:mm:ss"); }


    /****************************************************
     *                Current test state                *
     ****************************************************/
private:
    // Current date and time
    Q_PROPERTY(QDateTime DateTime READ currentDateTime)

    // Current date
    Q_PROPERTY(QDate DATE READ currentDate)

    // Current time
    Q_PROPERTY(QTime TIME READ currentTime)

    // Time when the test was last performed
    QDateTime m_TestTime;
    Q_PROPERTY(QString LastTestTime READ testTime)

    // Represents reply value (depends on the test type:
    // it can be reply time, disk's free space, message from NT Event Log, etc)
    AUTO_PROPERTY(QString, Reply)

    // Represents “Reply” field with some characters replaced by special sequences conforming
    // to C language standards: https://en.wikipedia.org/wiki/Escape_sequences_in_C
    // This variable could be useful for writing Java scripts (e.g. for Custom HTML report) or SQL Query for ODBC log.
    Q_PROPERTY(QString Reply_CStyle READ getReply) //! TODO

    // Represents actual numeric value of Reply field as a real number.
    // E.g. for the Reply field containing ’12.01 Kb’, %Reply_Number% will return ‘12298.24’.
    // It returns zero when the content of the field is a string that cannot be converted into a number.
    AUTO_PROPERTY(double, Reply_Number)

    // Represents actual numeric value of reply field as an integer number.
    // E.g. for the Reply field containing ’12.01 Kb’, %Reply_Integer% will return ‘12298’.
    // It returns zero when the content of the field is a string that cannot be converted into a number.
    AUTO_PROPERTY(int, Reply_Integer)

    TestStatus m_Status;
    // Status of the test (text) !!!
    Q_PROPERTY(QString Status READ status)
    // A 2 digits number that represents status of the test !!!!
    Q_PROPERTY(QString StatusID READ statusID)

    SimpleStatusID m_SimpleStatusID;
    // Return one of the following text values:
    // • "UP" for good statuses (Host is Alive, Ok);
    // • "DOWN" for any bad status (No answer, Bad, Bad Contents);
    // for Warning status when “Treat Warning as Bad” option is enabled;
    // for Unknown status when “Treat Unknown as Bad” option is enabled
    // • "UNKNOWN" if status of the test is “Unknown” or “Unknown host” and “Treat Unknown as Bad” option is disabled;
    // variable also returns “UNKNOWN” for statuses like WaitForMaster, OutOfSchedule, Paused.
    // • “WARNING” when status of the test is “Warning” and  “Treat Warning as Bad” option is disabled!
    Q_PROPERTY(QString SimpleStatus READ simpleStatus)

    // The number of consecutive test probes resulting in the same status as the current one
    AUTO_PROPERTY(int, CurrentStatusIteration)

    // Similar to %CurrentStatusIteration% but this counter is resetted by HostMonitor when test status changes from “bad” to “good”,
    // from “good” to unknown or warning and vice versa.
    // While changes between “Ok”, “Host is alive” and “Normal” statuses do not reset the counter,
    // changes between “Bad” and “No answer” do not reset the counter either.
    // “Threat Unknown status as Bad” and “Treat Warning status as Bad” options determine behaviour of the counter for Unknown and Warning statuses.
    // In other words: %CurrentStatusIteration% relates to %Status% while %Recurrences% relates to %SimpleStatus%.
    // This is important counter, you probably will use this counter for “advanced” actions.
    AUTO_PROPERTY(int, Recurrences)

    // Represents the duration of current (simple) status of the test
    qint64 m_CurrentStatusDuration;
    // shows time interval in "[N days] HH:MM:SS" format
    Q_PROPERTY(QString CurrentStatusDuration READ currentStatusDuration)
    // shows time in seconds
    Q_PROPERTY(qint64 CurrentStatusDuration_sec READ getCurrentStatusDurationSec)

    // This variable allows you to use unique failure ID as parameter of the actions.
    // HostMonitor assigns unique failure ID for each failed test and keeps the same ID when test fails several times in a row
    // (note: “failure” conditions may depend on “Treat Unknown as Bad” or “Treat Warning as Bad” test properties).
    // HostMonitor assigns different IDs for different test items;
    // it assigns new unique ID when test restores “good” status and then fails again.
    // HostMonitor sets %FailureID% variable to 0 when test has “good” status.
    AUTO_PROPERTY(int, FailureID)

    // While %FailureID% variable represents unique failure ID for each current problem,
    // %LastFailureID% returns ID of previous failure of the test
    AUTO_PROPERTY(int, LastFailureID)

    // Represents comment specified for test item when operator paused test execution
    AUTO_PROPERTY(QString, PauseComment)

public:
    QDateTime currentDateTime() const { return QDateTime::currentDateTime(); }
    QDate currentDate() const { return QDate::currentDate(); }
    QTime currentTime() const { return QTime::currentTime(); }
    QDateTime getTestTime() const { return m_TestTime; }
    QString testTime() const { return m_TestTime.toString("yyyy.MM.dd hh:mm:ss"); }
    QString status() const;
    TestStatus getStatusID() const;
    int statusID() const { return (int)getStatusID(); }
    QString simpleStatus() const { return TEnums::simpleStatus(m_SimpleStatusID); }
    SimpleStatusID simpleStatusID() const { return m_SimpleStatusID; }
    QString currentStatusDuration() const { return Utils::getTimeFromMs(m_CurrentStatusDuration); }
    qint64 getCurrentStatusDurationSec() const { return m_CurrentStatusDuration / 1000; }

    /****************************************************
     *                Suggested test state              *
     ****************************************************/
private:
    // Status that will be used for the test item, unless “normal” or “warning” options modify the status.
    // Variable may return one of the following values:
    // Host is alive, Ok, No answer, Bad, Bad contents, Unknown or Unknown host
    TestStatus m_SuggestedStatus;
    Q_PROPERTY(QString SuggestedStatus READ suggestedStatus)

    // Similar to %SimpleStatus% but provides information about “suggested” status
    // (test probe already responded with some result but %Status%, %Reply% and other regular counters not modified yet)
    SimpleStatusID m_SuggestedSimpleStatusID;
    Q_PROPERTY(QString SuggestedSimpleStatus READ suggestedSimpleStatus)

    // Represents “suggested” reply value
    // (“Tune up reply” option allows you to change Reply value after test execution)
    AUTO_PROPERTY(QString, SuggestedReply)

    // Works similar to %Reply_Integer% variable but provides information about "suggested" reply value.
    // E.g. if %SuggestedReply% shows '12.01 Kb', %SuggestedReply_Integer% will return '12298'.
    // This variable returns zero when SuggestedReply is a string that can not be converted into a number
    AUTO_PROPERTY(int, SuggestedReply_Integer)

    // “Suggested” reply value returned by previous check
    AUTO_PROPERTY(QString, SuggestedLastReply)

    // Similar to %Recurrences% counter.
    // Difference is HostMonitor sets this variable before Normal and Warning expressions processing.
    // If you do not use optional status processing or both logical expressions return False,
    // then %Recurrences% will be equivalent to %SuggestedRecurrences%
    AUTO_PROPERTY(int, SuggestedRecurrences)

    // The number of consecutive failed test probes. Shows 0 when test returns “good” result.
    // In contrast to other counters (like %Recurrences%, %CurrentStatusIteration%, %FailedCnt%, etc)
    // that depend on result of optional status processing (Normal and Warning expressions),
    // this counter always tells you about REAL result of test probe.
    // E.g. when test returns “bad” status, HostMonitor increments this variable
    // even if “Use normal status…” option tells HostMonitor to change test status to Normal.
    AUTO_PROPERTY(int, FailureIteration)

public:
    QString suggestedStatus() const { return TEnums::testStatus(m_SuggestedStatus); }
    QString suggestedSimpleStatus() const { return TEnums::simpleStatus(m_SuggestedSimpleStatusID); }

    /****************************************************
     *       Acknowledged Info                          *
     ****************************************************/
private:
    bool m_Acknowledged;

    // Represents the date and time when test status was acknowledged
    // Return empty string for non-acnowledged test items
    QDateTime m_AcknowledgedAt;
    Q_PROPERTY(QString AcknowledgedAt READ acknowledgedAt)

    // Represents the date when test status was acknowledged
    // Return empty string for non-acnowledged test items
    Q_PROPERTY(QString AcknowledgedDate READ acknowledgedDate)

    // Represents the time when test status was acknowledged
    // Return empty string for non-acnowledged test items
    Q_PROPERTY(QString AcknowledgedTime READ acknowledgedTime)

    // Shows the name of the operator who have acknowledged the test status
    // Return empty string for non-acnowledged test items
    QString m_AcknowlegedBy;
    Q_PROPERTY(QString AcknowledgedBy READ acknowledgedBy)

    // Shows the comment which was provided for "acknowledge" operation
    // Return empty string for non-acnowledged test items
    QString m_AckComment;
    Q_PROPERTY(QString AckComment READ ackComment)

    // Shows time elapsed sinse test failure till status acknowledgement by operator.
    // This variable returns time in hh:mm:ss format;
    // it may return empty string when test has Ok status;
    // variable returns "not acknowledged" string when test has Bad or Unknown not acknowledged status
    qint64 m_AckResponseTime;
    Q_PROPERTY(QString AckResponseTime READ ackResponseTime)

    // Represents the number of test probes which have returned similar (bad or unknown) result
    // after it was already acknowledged. Returns 0 for non-acknowledged test items.
    // For example if the test returned "bad" status during five consecutive probes,
    // then %Recurrences% variable will be equal 5.
    // If the user has acknowledged the bad status after the second probe
    // then %AckRecurrences% will be equal 3 (5-2=3).
    // This variable is useful when you want to configure alert profile to launch different actions
    // for "non-acknowledged" and "acknowledged" test items.
    // E.g. if condition to trigger action execution looks like ('%SimpleStatus%=='DOWN') and (%AckRecurrences%==1),
    // HostMonitor will start action when user confirmed status and test failed once again (after acknowledgement).
    AUTO_PROPERTY(int, AckRecurrences)

public:
    bool isAcknowledged() const { return m_Acknowledged; }
    QString acknowledgedAt() const { return m_Acknowledged?m_AcknowledgedAt.toString("yyyy.MM.dd hh:mm:ss"):QString(); }
    QString acknowledgedDate() const { return m_Acknowledged?m_AcknowledgedAt.toString("yyyy.MM.dd"):QString(); }
    QString acknowledgedTime() const { return m_Acknowledged?m_AcknowledgedAt.toString("hh:mm:ss"):QString(); }
    QString acknowledgedBy() const { return m_Acknowledged?m_AcknowlegedBy:QString(); }
    QString ackComment() const { return m_Acknowledged?m_AckComment:QString(); }
    QString ackResponseTime() const;

    /****************************************************
     *                  Previous state                  *
     ****************************************************/
    // To explain following variables we need to explain difference between terms “PreviousStatus” and “LastStatus”.
    // “PreviousStatus” is status which test had before current status.
    // “LastStatus” is status which test had after previous check.
    // For example for the  last 5 probes test had following statuses: #1-Bad, #2-Unknown, #3-Ok, #4-Ok, #5-Ok (current status is #5-Ok).
    // In this case “PreviousStatus” is #2-Unknown but “LastStatus” is #4-Ok.
private:
    // Status of the test after previous check (LastStatus)
    TestStatus m_LastStatus;
    Q_PROPERTY(QString LastStatus READ lastStatus)

    // Similar to %SimpleStatus% but provides information about last test status
    SimpleStatusID m_LastSimpleStatusID;
    Q_PROPERTY(QString LastSimpleStatus READ lastSimpleStatus)

    // Reply value returned by previous check
    AUTO_PROPERTY(QString, LastReply)

    QDateTime m_LastTestTime;

    // Represents “LastReply” value returned by previous check with some characters replaced by special sequences conforming to C language standards
    Q_PROPERTY(QString LastReply_CStyle READ getLastReply) //! TODO

    // The status, which the test had before last status change
    TestStatus m_PreviousStatusID;
    Q_PROPERTY(QString PreviousStatus READ previousStatus)

    // Represents time when “PreviousStatus” was assigned to the test
    QDateTime m_PreviousStatusTime;
    Q_PROPERTY(QString PreviousStatusTime READ previousStatusTime)

    // Represents the duration of the "PreviousStatus”.
    qint64 m_PreviousStatusDuration;
    // Shows time interval in “[X days] HH:MM:SS” format.
    Q_PROPERTY(QString PreviousStatusDuration READ previousStatusDuration)
    // Shows time interval in seconds.
    Q_PROPERTY(QString PreviousStatusDuration_Sec READ previousStatusDuration)

public:
    QString lastStatus() const { return TEnums::testStatus(m_LastStatus); }
    SimpleStatusID getLastSimpleStatusID() const { return m_LastSimpleStatusID; }
    QString lastSimpleStatus() const { return TEnums::simpleStatus(m_LastSimpleStatusID); }
    QDateTime getLastTestTime() const { return m_LastTestTime; }
    QString previousStatus() const { return  TEnums::testStatus(m_PreviousStatusID); }
    QString previousStatusTime() const { return m_PreviousStatusTime.toString("hh:mm:ss"); }
    QString previousStatusDuration() const { return Utils::getTimeFromMs(m_PreviousStatusDuration); }
    int previousStatusDuration_Sec() const { return m_PreviousStatusDuration / 1000; }

    /****************************************************
     *              Statistical information             *
     ****************************************************/
private:
    // The time when the status last changed
    QDateTime m_StatusChangedTime;
    Q_PROPERTY(QString StatusChangedTime READ statusChangedTime)

    // The number of times the status has changed
    AUTO_PROPERTY(int, StatusChangesCnt)

    // Overall tests performed
    AUTO_PROPERTY(int, TotalTests)

    // The time the test has been in monitoring
    qint64 m_TotalTime;
    Q_PROPERTY(QString TotalTime READ totalTime)

    // The number of "Bad" test results
    AUTO_PROPERTY(int, FailedCnt)

    // The number of "Good" test results
    AUTO_PROPERTY(int, PassedCnt)

    // The number of "Unknown" test results
    AUTO_PROPERTY(int, UnknownCnt)

    // The overall time the test has had a "Good" status
    qint64 m_AliveTime;
    Q_PROPERTY(QString AliveTime READ aliveTime)

    // The overall time the test has had a "Bad" status
    qint64 m_DeadTime;
    Q_PROPERTY(QString DeadTime READ deadTime)

    // The overall time the test has had an "Unknown" status
    qint64 m_UnknownTime;
    Q_PROPERTY(QString UnknownTime READ unknownTime)

    // "Good" to overall tests ratio, in percent
    double m_AliveRatio;
    Q_PROPERTY(QString AliveRatio READ getAliveRatioAsStr)

    // "Bad" to overall tests ratio, in percent
    double m_DeadRatio;
    Q_PROPERTY(QString DeadRatio READ getDeadRatioAsStr)

    // "Unknown" to overall tests ratio, in percent
    double m_UnknownRatio;
    Q_PROPERTY(QString UnknownRatio READ getUnknownRatioAsStr)

    // The average value of the results obtained
    float m_AverageReply;
    Q_PROPERTY(QString AverageReply READ averageReply)

    // The minimum value of the results obtained
    float m_MinReply;
    Q_PROPERTY(QString MinReply READ minReply)

    // The maximum value of the results obtained
    float m_MaxReply;
    Q_PROPERTY(QString MaxReply READ maxReply)

public:
    QString statusChangedTime() const { return m_StatusChangedTime.toString("yyyy.MM.dd hh:mm:ss"); }
    QString totalTime() const { return Utils::getTimeFromMs(m_TotalTime); }
    QString aliveTime() const { return Utils::getTimeFromMs(m_AliveTime); }
    QString deadTime() const { return Utils::getTimeFromMs(m_DeadTime); }
    QString unknownTime() const { return Utils::getTimeFromMs(m_UnknownTime); }
    double getAliveRatio() const { return m_AliveRatio; }
    QString getAliveRatioAsStr() const { return QString("%1\%").arg(m_AliveRatio); }
    double getDeadRatio() const { return m_DeadRatio; }
    QString getDeadRatioAsStr() const { return QString("%1\%").arg(m_DeadRatio); }
    double getUnknownRatio() const { return m_UnknownRatio; }
    QString getUnknownRatioAsStr() const { return QString("%1\%").arg(m_UnknownRatio); }
    QString averageReply() const { return QString("%1").arg(m_AverageReply); }
    QString minReply() const { return QString("%1").arg(m_MinReply); }
    QString maxReply() const { return QString("%1").arg(m_MaxReply); }

public:

    TTest(const QString &name, QObject *parent = 0);
    ~TTest();

    QVariant property(QString name) const Q_DECL_OVERRIDE;
    virtual QVariant getGlobal(Macro::Variable globalVar) const;
    void updateSpecificProperties();
    TTest *clone(const QString &newName);

public slots:
    void onTestPerformed();
    void slotTimeout();

private:
    TestStatus processReverseAlertOption(const TestStatus originalStatus) const;
    SimpleStatusID produceSimpleStatus(const TestStatus status) const;
    void setSuggestedVars(const TestStatus newStatus);
    TestStatus processUserStatusExpressions(const TestStatus originalStatus);
    QString tuneUpReply(const QString originalReply);
    void dynamicStatistics(const TestStatus newStatus, const QString newReply, const double newReplyNumber, const int newReplyInt);

    void resetCurrentTestState();
    void resetSuggestedTestState();
    void resetAcknowlegedInfo();
    void resetPreviousStatusInfo();
    void resetStatistics();
};

} // namespace SDPO

#endif // TTEST_H
