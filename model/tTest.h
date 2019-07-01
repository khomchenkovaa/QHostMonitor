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
#include "tTestMethod.h"

namespace SDPO {

class TTest;
class TestAction;

typedef QPair<TTest*,int> TTestPair;

struct TAcknowledge {
    QDateTime at;
    QString   by;
    QString   comment;
    int       time;
    int       recurrences;

    TAcknowledge() {
        clear();
    }

    void clear() {
        at = QDateTime::currentDateTime();
        by = QString();
        comment = QString();
        time = 0;
        recurrences = 0;
    }
};

struct TStatistics {
    qint64    currentDuration;
    QDateTime previousTime;
    qint64    previousDuration;
    QDateTime changedTime;
    int       changesCnt;
    int       totalTests;
    qint64    totalTime;
    int       failedCnt;
    int       passedCnt;
    int       unknownCnt;
    qint64    aliveTime;
    qint64    deadTime;
    qint64    unknownTime;
    double    avgReply;
    double    minReply;
    double    maxReply;

    TStatistics() {
        clear();
    }

    void clear() {
        currentDuration = 0;
        previousTime = QDateTime();
        previousDuration = 0;
        changedTime = QDateTime();
        changesCnt = 0;
        totalTests = 0;
        totalTime = 0;
        failedCnt = 0;
        passedCnt = 0;
        unknownCnt = 0;
        aliveTime = 0;
        deadTime = 0;
        unknownTime = 0;
        avgReply = 0.0;
        minReply = 0.0;
        maxReply = 0.0;
    }

    double aliveRatio() const {
        return totalTime? (100.0 * aliveTime / totalTime) : 0.0;
    }

    double deadRatio() const {
        return totalTime? (100.0 * deadTime / totalTime) : 0.0;
    }

    double unknownRatio() const {
        return totalTime? (100.0 * unknownTime / totalTime) : 0.0;
    }
};

struct TRecurences {
    int       currentStatus;
    int       currentSimpleStatus;
    int       suggestedSimpleStatus;
    int       failure;

    TRecurences() {
        clear();
    }

    void clear() {
        currentStatus = 0;
        currentSimpleStatus = 0;
        suggestedSimpleStatus = 0;
        failure = 0;
    }
};

class TTest : public TNode
{
    Q_OBJECT

    static int failureCount;

    TTestMethod  *m_TMethod;
    TAgent       *m_agent;
    TSchedule     m_schedule;
    QList<TNode*> m_links;
    AUTO_PROPERTY(QString, RelatedURL)

    BOOL_PROPERTY(Enabled)
    BOOL_PROPERTY(Paused)
    AUTO_PROPERTY(QString, PauseComment)

    AUTO_PROPERTY(int, AlertProfileID)

    // Log & Reports options
    BOOL_PROPERTY(UseCommonLog)
    AUTO_PROPERTY(int, CommonLogMode)
    BOOL_PROPERTY(UsePrivateLog)
    AUTO_PROPERTY(int, PrivateLogMode)
    AUTO_PROPERTY(QString, PrivateLog)
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

    // results
    TTestResult m_CurrentState;
    TTestResult m_SuggestedState;
    TTestResult m_SuggestedLastState;
    TTestResult m_LastState;
    TTestResult m_PreviousState;

    bool m_Acknowledged;
    TAcknowledge m_Acknowledge;

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

    TStatistics m_Stat;
    TRecurences m_Recurences;

public:
    // TTest methods
    TTestMethod *method() const { return m_TMethod; }
    void setMethod(TTestMethod *testMethod);

    // TAgent methods
    TAgent* agent() { return m_agent; }
    void setAgent(TAgent* value) { m_agent = value; }

    // Schedule methods
    TSchedule* schedule() { return &m_schedule; }
    void setRegularSchedule(const int interval, const QString schedName) { m_schedule.setRegular(interval, schedName); }
    void setOncePerDaySchedule(const QTime schedTime) { m_schedule.setOncePerDay(schedTime); }
    void setOncePerWeekSchedule(const int schedDay, const QTime schedTime) { m_schedule.setOncePerWeek(schedDay, schedTime); }
    void setOncePerMonthSchedule(const int schedDay, const QTime schedTime) { m_schedule.setOncePerMonth(schedDay, schedTime); }
    void setByExpressionSchedule(const QString expr1, const QString expr2) { m_schedule.setByExpression(expr1, expr2); }

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
    Q_PROPERTY(int TestID READ getID)

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
    QString testMethod() const { return m_TMethod->getTestMethod(); }
    int testMethodId() const { return static_cast<int>(m_TMethod->getTMethodID()); }
    TMethodID methodId() const { return m_TMethod->getTMethodID(); }
    QString testedObjectInfo() const { return m_TMethod->getTestedObjectInfo(); }
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
    Q_PROPERTY(QString LastTestTime READ testTime)

    // Represents reply value (depends on the test type:
    // it can be reply time, disk's free space, message from NT Event Log, etc)
    Q_PROPERTY(QString Reply READ getReply)

    // Represents “Reply” field with some characters replaced by special sequences conforming
    // to C language standards: https://en.wikipedia.org/wiki/Escape_sequences_in_C
    // This variable could be useful for writing Java scripts (e.g. for Custom HTML report) or SQL Query for ODBC log.
    Q_PROPERTY(QString Reply_CStyle READ getReply) //! TODO

    // Represents actual numeric value of Reply field as a real number.
    // E.g. for the Reply field containing ’12.01 Kb’, %Reply_Number% will return ‘12298.24’.
    // It returns zero when the content of the field is a string that cannot be converted into a number.
    Q_PROPERTY(double Reply_Number READ getReplyNumber)

    // Represents actual numeric value of reply field as an integer number.
    // E.g. for the Reply field containing ’12.01 Kb’, %Reply_Integer% will return ‘12298’.
    // It returns zero when the content of the field is a string that cannot be converted into a number.
    Q_PROPERTY(double Reply_Integer READ getReplyInteger)

    // Status of the test (text) !!!
    Q_PROPERTY(QString Status READ status)

    // A 2 digits number that represents status of the test !!!!
    Q_PROPERTY(int StatusID READ statusID)

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
    Q_PROPERTY(int CurrentStatusIteration READ getCurrentStatusIteration)

    // Similar to %CurrentStatusIteration% but this counter is resetted by HostMonitor when test status changes from “bad” to “good”,
    // from “good” to unknown or warning and vice versa.
    // While changes between “Ok”, “Host is alive” and “Normal” statuses do not reset the counter,
    // changes between “Bad” and “No answer” do not reset the counter either.
    // “Threat Unknown status as Bad” and “Treat Warning status as Bad” options determine behaviour of the counter for Unknown and Warning statuses.
    // In other words: %CurrentStatusIteration% relates to %Status% while %Recurrences% relates to %SimpleStatus%.
    // This is important counter, you probably will use this counter for “advanced” actions.
    Q_PROPERTY(int Recurrences READ getRecurrences)

    // Represents the duration of current (simple) status of the test
    // shows time interval in "[N days] HH:MM:SS" format
    Q_PROPERTY(QString CurrentStatusDuration READ currentStatusDuration)
    // shows time in seconds
    Q_PROPERTY(qint64 CurrentStatusDuration_sec READ getCurrentStatusDurationSec)


public:
    QDateTime currentDateTime() const { return m_CurrentState.date; }
    QDate currentDate() const { return m_CurrentState.date.date(); }
    QTime currentTime() const { return m_CurrentState.date.time(); }
    QDateTime getTestTime() const { return m_CurrentState.date; }
    QString testTime() const { return m_CurrentState.date.toString("yyyy.MM.dd hh:mm:ss"); }
    QString getReply() const { return m_CurrentState.reply; }
    double getReplyNumber() const { return m_CurrentState.replyDouble; }
    double getReplyInteger() const { return m_CurrentState.replyInt; }
    QString status() const;
    TestStatus getStatusID() const;
    int statusID() const { return static_cast<int>(getStatusID()); }
    QString simpleStatus() const { return TEnums::simpleStatus(m_CurrentState.simpleStatus(b_UnknownIsBad, b_WarningIsBad)); }
    SimpleStatusID simpleStatusID() const { return m_CurrentState.simpleStatus(b_UnknownIsBad, b_WarningIsBad); }
    int getCurrentStatusIteration() const { return m_Recurences.currentStatus; }
    int getRecurrences() const { return m_Recurences.currentSimpleStatus; }
    QString currentStatusDuration() const { return Utils::getTimeFromMs(m_Stat.currentDuration); }
    qint64 getCurrentStatusDurationSec() const { return m_Stat.currentDuration / 1000; }

    /****************************************************
     *                Suggested test state              *
     ****************************************************/
private:
    // Status that will be used for the test item, unless “normal” or “warning” options modify the status.
    // Variable may return one of the following values:
    // Host is alive, Ok, No answer, Bad, Bad contents, Unknown or Unknown host
    Q_PROPERTY(QString SuggestedStatus READ suggestedStatus)

    // Similar to %SimpleStatus% but provides information about “suggested” status
    // (test probe already responded with some result but %Status%, %Reply% and other regular counters not modified yet)
    Q_PROPERTY(QString SuggestedSimpleStatus READ suggestedSimpleStatus)

    // Represents “suggested” reply value
    // (“Tune up reply” option allows you to change Reply value after test execution)
    Q_PROPERTY(QString SuggestedReply READ suggestedReply)

    // Works similar to %Reply_Integer% variable but provides information about "suggested" reply value.
    // E.g. if %SuggestedReply% shows '12.01 Kb', %SuggestedReply_Integer% will return '12298'.
    // This variable returns zero when SuggestedReply is a string that can not be converted into a number
    Q_PROPERTY(int SuggestedReply_Integer READ suggestedReplyInteger)

    // “Suggested” reply value returned by previous check
    Q_PROPERTY(QString SuggestedLastReply READ suggestedLastReply)

    // Similar to %Recurrences% counter.
    // Difference is HostMonitor sets this variable before Normal and Warning expressions processing.
    // If you do not use optional status processing or both logical expressions return False,
    // then %Recurrences% will be equivalent to %SuggestedRecurrences%
    Q_PROPERTY(int SuggestedRecurrences READ getSuggestedRecurrences)

    // The number of consecutive failed test probes. Shows 0 when test returns “good” result.
    // In contrast to other counters (like %Recurrences%, %CurrentStatusIteration%, %FailedCnt%, etc)
    // that depend on result of optional status processing (Normal and Warning expressions),
    // this counter always tells you about REAL result of test probe.
    // E.g. when test returns “bad” status, HostMonitor increments this variable
    // even if “Use normal status…” option tells HostMonitor to change test status to Normal.
    Q_PROPERTY(int FailureIteration READ getFailureIteration)

public:
    QString suggestedStatus() const { return TEnums::testStatus(m_SuggestedState.status); }
    QString suggestedSimpleStatus() const { return TEnums::simpleStatus(m_SuggestedState.simpleStatus(b_UnknownIsBad)); }
    QString suggestedReply() const { return m_SuggestedState.reply; }
    int suggestedReplyInteger() const { return m_SuggestedState.replyInt; }
    QString suggestedLastReply() const { return m_SuggestedLastState.reply; }
    int getSuggestedRecurrences() const { return m_Recurences.suggestedSimpleStatus; }
    int getFailureIteration() const { return m_Recurences.failure; }

    /****************************************************
     *       Acknowledged Info                          *
     ****************************************************/
private:
    // Represents the date and time when test status was acknowledged
    // Return empty string for non-acnowledged test items
    Q_PROPERTY(QString AcknowledgedAt READ acknowledgedAt)

    // Represents the date when test status was acknowledged
    // Return empty string for non-acnowledged test items
    Q_PROPERTY(QString AcknowledgedDate READ acknowledgedDate)

    // Represents the time when test status was acknowledged
    // Return empty string for non-acnowledged test items
    Q_PROPERTY(QString AcknowledgedTime READ acknowledgedTime)

    // Shows the name of the operator who have acknowledged the test status
    // Return empty string for non-acnowledged test items
    Q_PROPERTY(QString AcknowledgedBy READ acknowledgedBy)

    // Shows the comment which was provided for "acknowledge" operation
    // Return empty string for non-acnowledged test items
    Q_PROPERTY(QString AckComment READ ackComment)

    // Shows time elapsed sinse test failure till status acknowledgement by operator.
    // This variable returns time in hh:mm:ss format;
    // it may return empty string when test has Ok status;
    // variable returns "not acknowledged" string when test has Bad or Unknown not acknowledged status
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
    Q_PROPERTY(int AckRecurrences READ ackRecurrences)

public:
    bool isAcknowledged() const { return m_Acknowledged; }
    QString acknowledgedAt() const { return m_Acknowledged?m_Acknowledge.at.toString("yyyy.MM.dd hh:mm:ss"):QString(); }
    QString acknowledgedDate() const { return m_Acknowledged?m_Acknowledge.at.toString("yyyy.MM.dd"):QString(); }
    QString acknowledgedTime() const { return m_Acknowledged?m_Acknowledge.at.toString("hh:mm:ss"):QString(); }
    QString acknowledgedBy() const { return m_Acknowledged?m_Acknowledge.by:QString(); }
    QString ackComment() const { return m_Acknowledged?m_Acknowledge.comment:QString(); }
    QString ackResponseTime() const;
    int     ackRecurrences() const { return m_Acknowledged?(m_Recurences.currentSimpleStatus - m_Acknowledge.recurrences):0; }

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
    Q_PROPERTY(QString LastStatus READ lastStatus)

    // Similar to %SimpleStatus% but provides information about last test status
    Q_PROPERTY(QString LastSimpleStatus READ lastSimpleStatus)

    // Reply value returned by previous check
    Q_PROPERTY(QString LastReply READ lastReply)

    // Represents “LastReply” value returned by previous check with some characters replaced by special sequences conforming to C language standards
    Q_PROPERTY(QString LastReply_CStyle READ lastReply) //! TODO

    // The status, which the test had before last status change
    Q_PROPERTY(QString PreviousStatus READ previousStatus)

    // Represents time when “PreviousStatus” was assigned to the test
    Q_PROPERTY(QString PreviousStatusTime READ previousStatusTime)

    // Represents the duration of the "PreviousStatus”.
    // Shows time interval in “[X days] HH:MM:SS” format.
    Q_PROPERTY(QString PreviousStatusDuration READ previousStatusDuration)
    // Shows time interval in seconds.
    Q_PROPERTY(QString PreviousStatusDuration_Sec READ previousStatusDuration)

public:
    QString lastStatus() const { return TEnums::testStatus(m_LastState.status); }
    SimpleStatusID getLastSimpleStatusID() const { return m_LastState.simpleStatus(b_UnknownIsBad, b_WarningIsBad); }
    QString lastSimpleStatus() const { return TEnums::simpleStatus(m_LastState.simpleStatus(b_UnknownIsBad, b_WarningIsBad)); }
    QString lastReply() const { return m_LastState.reply; }
    QDateTime getLastTestTime() const { return m_LastState.date; }
    QString previousStatus() const { return  TEnums::testStatus(m_PreviousState.status); }
    QString previousStatusTime() const { return m_Stat.previousTime.toString("hh:mm:ss"); }
    QString previousStatusDuration() const { return Utils::getTimeFromMs(m_Stat.previousDuration); }
    int previousStatusDuration_Sec() const { return m_Stat.previousDuration / 1000; }

    /****************************************************
     *              Statistical information             *
     ****************************************************/
private:
    // The time when the status last changed
    Q_PROPERTY(QString StatusChangedTime READ statusChangedTime)

    // The number of times the status has changed
    Q_PROPERTY(int StatusChangesCnt READ getStatusChangedCnt)

    // Overall tests performed
    Q_PROPERTY(int TotalTests READ getTotalTests)

    // The time the test has been in monitoring
    Q_PROPERTY(QString TotalTime READ totalTime)

    // The number of "Bad" test results
    Q_PROPERTY(int FailedCnt READ getFailedCnt)

    // The number of "Good" test results
    Q_PROPERTY(int PassedCnt READ getPassedCnt)

    // The number of "Unknown" test results
    Q_PROPERTY(int UnknownCnt READ getUnknownCnt)

    // The overall time the test has had a "Good" status
    Q_PROPERTY(QString AliveTime READ aliveTime)

    // The overall time the test has had a "Bad" status
    Q_PROPERTY(QString DeadTime READ deadTime)

    // The overall time the test has had an "Unknown" status
    Q_PROPERTY(QString UnknownTime READ unknownTime)

    // "Good" to overall tests ratio, in percent
    Q_PROPERTY(QString AliveRatio READ getAliveRatioAsStr)

    // "Bad" to overall tests ratio, in percent
    Q_PROPERTY(QString DeadRatio READ getDeadRatioAsStr)

    // "Unknown" to overall tests ratio, in percent
    Q_PROPERTY(QString UnknownRatio READ getUnknownRatioAsStr)

    // The average value of the results obtained
    Q_PROPERTY(QString AverageReply READ averageReply)

    // The minimum value of the results obtained
    Q_PROPERTY(QString MinReply READ minReply)

    // The maximum value of the results obtained
    Q_PROPERTY(QString MaxReply READ maxReply)

public:
    QString statusChangedTime() const { return m_Stat.changedTime.toString("yyyy.MM.dd hh:mm:ss"); }
    int getStatusChangedCnt() const { return m_Stat.changesCnt; }
    int getTotalTests() const { return m_Stat.totalTests; }
    QString totalTime() const { return Utils::getTimeFromMs(m_Stat.totalTime); }
    int getFailedCnt() const { return m_Stat.failedCnt; }
    int getPassedCnt() const { return m_Stat.passedCnt; }
    int getUnknownCnt() const { return m_Stat.unknownCnt; }
    QString aliveTime() const { return Utils::getTimeFromMs(m_Stat.aliveTime); }
    QString deadTime() const { return Utils::getTimeFromMs(m_Stat.deadTime); }
    QString unknownTime() const { return Utils::getTimeFromMs(m_Stat.unknownTime); }
    double getAliveRatio() { return m_Stat.aliveRatio(); }
    QString getAliveRatioAsStr() { return QString::number(m_Stat.aliveRatio(),'f',1).append('%'); }
    double getDeadRatio() { return m_Stat.deadRatio(); }
    QString getDeadRatioAsStr() { return QString::number(m_Stat.deadRatio(),'f',1).append('%'); }
    double getUnknownRatio() { return m_Stat.unknownRatio(); }
    QString getUnknownRatioAsStr() { return QString::number(m_Stat.unknownRatio(),'f',1).append('%');}
    QString averageReply() const { return QString("%1").arg(m_Stat.avgReply); }
    QString minReply() const { return QString("%1").arg(m_Stat.minReply); }
    QString maxReply() const { return QString("%1").arg(m_Stat.maxReply); }

public:

    TTest(const int id, const QString &name, QObject *parent = nullptr);
    ~TTest() Q_DECL_OVERRIDE;

    QVariant property(QString name) const Q_DECL_OVERRIDE;
    virtual QVariant getGlobal(Macro::Variable globalVar) const Q_DECL_OVERRIDE;
    void updateSpecificProperties();
    TTest *clone(const int newID, const QString &newName);
    QString executionLog() const;

public slots:
    void onTestPerformed();
    void restart();
    void slotTimeout();

private:
    void setSuggestedVars(const TTestResult testResult);
    void processUserStatusExpressions(TTestResult &testResult);
    void tuneUpReply(TTestResult &testResult);
    void dynamicStatistics(const TTestResult testResult);

    void resetCurrentTestState();
    void resetSuggestedTestState();
    void resetAcknowlegedInfo();
    void resetPreviousStatusInfo();
};

} // namespace SDPO

#endif // TTEST_H
