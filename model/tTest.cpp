#include "tTest.h"
#include "gData.h"
#include "method/sdpoTestMethods.h"
#include "global/gUserVars.h"
#include "global/gMacroTranslator.h"
#include <QScriptEngine>

namespace SDPO {

/***********************************************/

int TTest::failureCount = 0;

/***********************************************/

TTest::TTest(const QString &name, QObject *parent) :
    TNode(name, TNode::TEST, parent),
    m_schedule(* new TSchedule())
{
    m_test = new TTestMethod(TMethodID::Empty);

    setEnabled(true);
    setPaused(false);
    // log & reports
    setUseCommonLog(true);
    setUsePrivateLog(false);
    setCommonLogMode(0);
    setPrivateLogMode(0);
    setExcludeFromHtmlReport(false);
    setExcludeFromWmlReport(false);
    setExcludeFromDbfReport(false);
    // optional status processing
    setReverseAlert(false);
    setUnknownIsBad(false);
    setWarningIsBad(false);
    setUseWarningScript(false);
    setUseNormalScript(false);
    setTuneUpReply(false);

    m_agent = new TAgent(this); //! TODO stub
    a_AlertProfileID = -1;

    resetCurrentTestState();
    resetSuggestedTestState();
    resetAcknowlegedInfo();
    resetPreviousStatusInfo();
    resetStatistics();

    connect(&m_schedule, &TSchedule::activated, this, &TTest::slotTimeout);
}

/***********************************************/

TTest::~TTest()
{
    delete &m_schedule;
    m_links.clear();
    delete m_agent;
    delete m_test;
}

/***********************************************/

QVariant TTest::property(QString name) const
{
    if (name.startsWith("CommentLine")) {
        int idx = name.mid(11).toInt();
        return getCommentLine(idx);
    }
    return QObject::property(name.toLatin1());
}

/***********************************************/

void TTest::addLink(TNode *node)
{
    m_links.append(node);
}

/***********************************************/

int TTest::linkCount()
{
    return m_links.count();
}

/***********************************************/

QList<TNode *> TTest::links()
{
    return m_links;
}

/***********************************************/

void TTest::removeLink(TNode *node)
{
    m_links.removeOne(node); 
}

/******************************************************************/

QVariant TTest::getGlobal(Macro::Variable globalVar) const
{
    MVariablesStruct mvs = TEnums::mVar(globalVar);
    return property(mvs.name.toLatin1());
}

/******************************************************************/

void TTest::onTestPerformed()
{
    // 1. (perform the test)
    // 2. process "Reverse alert" option
    TestStatus newStatus = processReverseAlertOption(m_test->getStatus());

    // 3. set “suggested” macro variables (%SuggestedStatus%, %SuggestedSimpleStatus%, %SuggestedReply%,  %SuggestedRecurrences% and %FailureIteration%)
    // without touching regular counters (%Status%, %Reply%, %Recurrences%, etc);
    setSuggestedVars(newStatus);

    // 4. check "Warning" and "Normal" expressions
    newStatus = processUserStatusExpressions(newStatus);

    // 5. process “Tune up Reply” option
    QString newReply = tuneUpReply(m_test->getReply());

    // 6. modify current test status and statistisc counters (Status, Reply, Alive%, Passed tests, Failed tests, etc)
    dynamicStatistics(newStatus, newReply, m_test->getReplyDouble(), m_test->getReplyInt());

    m_schedule.start();
    emit testDone(this);
}

/******************************************************************/

TestStatus TTest::processReverseAlertOption(const TestStatus originalStatus) const
{
    TestStatus result = originalStatus;
    if(isReverseAlert()) {
        switch (originalStatus) {
        case TestStatus::HostAlive:   result = TestStatus::Bad; break;
        case TestStatus::NoAnswer:    result = TestStatus::Ok;  break;
        case TestStatus::Ok:          result = TestStatus::Bad; break;
        case TestStatus::Bad:         result = TestStatus::Ok;  break;
        case TestStatus::BadContents: result = TestStatus::Ok;  break;
        default: break;
        }
    }
    return result;
}


/******************************************************************/
// Unknown, might be processed as “bad” statuses depending on “unknownIsBad” option

SimpleStatusID TTest::produceSimpleStatus(const TestStatus status) const
{
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
    if (isUnknownIsBad() && result==SimpleStatusID::UNKNOWN) result = SimpleStatusID::DOWN;

    // Warning, might be processed as “bad” statuses depending on “warningIsBad” option
    if (isWarningIsBad() && result==SimpleStatusID::WARNING) result = SimpleStatusID::DOWN;

    return result;
}

/******************************************************************/

void TTest::setSuggestedVars(const TestStatus newStatus)
{
    m_SuggestedStatus = newStatus;
    SimpleStatusID oldSimpleStatus = m_SuggestedSimpleStatusID;
    m_SuggestedSimpleStatusID = produceSimpleStatus(newStatus);
    a_SuggestedLastReply = a_SuggestedReply;
    a_SuggestedReply = m_test->getReply();
    a_SuggestedReply_Integer = m_test->getReplyInt();

    if (oldSimpleStatus == m_SuggestedSimpleStatusID) {
        a_SuggestedRecurrences++;
    } else {
        a_SuggestedRecurrences = 0;
    }

    if (m_SuggestedSimpleStatusID == SimpleStatusID::DOWN) {
        a_FailureIteration++;
    } else {
        a_FailureIteration=0;
    }
}

/******************************************************************/

TestStatus TTest::processUserStatusExpressions(const TestStatus originalStatus)
{
    TestStatus result = originalStatus;
    if (b_UseWarningScript) {
        GMacroTranslator translator(a_WarningScript, this);
        QString script = translator.translate();
        QScriptEngine scriptEngine;
        QScriptValue value = scriptEngine.evaluate(script);
        if (value.isBool() && value.toBool()) {
            result = TestStatus::Warning;
        }
    }

    if (b_UseNormalScript) {
        GMacroTranslator translator(a_NormalScript, this);
        QString script = translator.translate();
        QScriptEngine scriptEngine;
        QScriptValue value = scriptEngine.evaluate(script);
        if (value.isBool() && value.toBool()) {
            result = TestStatus::Normal;
        }
    }
    return result;
}

/******************************************************************/

QString TTest::tuneUpReply(const QString originalReply)
{
    QString result = originalReply;
    if (b_TuneUpReply) {
        GMacroTranslator translator(a_TuneUpScript, this);
        QString script = translator.translate();
        QScriptEngine scriptEngine;
        QScriptValue value = scriptEngine.evaluate(script);
        result = value.toString();
    }
    return result;
}

/******************************************************************/

void TTest::dynamicStatistics(const TestStatus newStatus, const QString newReply, const double newReplyNumber, const int newReplyInt)
{
    // helpers
    QDateTime curTime = currentDateTime();
    QDateTime lastTime = m_TestTime;
    qint64 delta = curTime.toMSecsSinceEpoch() - lastTime.toMSecsSinceEpoch();
    SimpleStatusID newSimpleStatus = produceSimpleStatus(newStatus);
    bool statusChanged = (m_Status != newStatus);
    bool simpleStatusChanged = (m_SimpleStatusID != newSimpleStatus);

    // previous state
    m_LastStatus = m_Status;
    m_LastSimpleStatusID = m_SimpleStatusID;
    a_LastReply = a_Reply;    
    m_LastTestTime = m_TestTime;
    if (simpleStatusChanged) {
        m_PreviousStatusID = m_Status;
        m_PreviousStatusTime = m_StatusChangedTime;
        m_PreviousStatusDuration = m_CurrentStatusDuration;
    }

    // current test state
    m_TestTime = curTime;
    a_Reply = newReply;
    a_Reply_Number = newReplyNumber;
    a_Reply_Integer = newReplyInt;
    m_Status = newStatus;
    m_SimpleStatusID = newSimpleStatus;
    if (statusChanged) {
        a_CurrentStatusIteration = 0;
    } else {
        a_CurrentStatusIteration++;
    }
    if (simpleStatusChanged) {
        a_Recurrences = 0;
        m_CurrentStatusDuration = 0;
        m_StatusChangedTime = curTime;
        a_StatusChangesCnt++;
        if (m_SimpleStatusID == SimpleStatusID::UP) {
            a_LastFailureID = a_FailureID;
            a_FailureID = 0;
        }
        if (m_SimpleStatusID == SimpleStatusID::DOWN) {
            a_FailureID = ++failureCount;
        }
    } else {
        a_Recurrences++;
        m_CurrentStatusDuration = curTime.toMSecsSinceEpoch() - m_StatusChangedTime.toMSecsSinceEpoch();
    }

    // statistical information
    a_TotalTests++;
    m_TotalTime += delta;
    switch (m_SimpleStatusID) {
        case SimpleStatusID::UP:
            a_PassedCnt++;
            m_AliveTime += delta;
            break;
        case SimpleStatusID::WARNING:
        case SimpleStatusID::DOWN:
            m_DeadTime += delta;
            a_FailedCnt++;
            break;
        case SimpleStatusID::UNKNOWN:
            m_UnknownTime += delta;
            a_UnknownCnt++;
            break;
    }

    m_AliveRatio = 100.0 * m_AliveTime / m_TotalTime;
    m_DeadRatio = 100.0 * m_DeadTime / m_TotalTime;
    m_UnknownRatio = 100.0 * m_UnknownTime / m_TotalTime;

    if (m_SimpleStatusID == SimpleStatusID::UP) {
        if (m_MinReply < newReplyNumber) m_MinReply = newReplyNumber;
        if (m_MaxReply > newReplyNumber) m_MaxReply = newReplyNumber;
        m_AverageReply = (m_AverageReply*(a_PassedCnt-1) + newReplyNumber) / a_PassedCnt;
    }
}

/***********************************************/

void TTest::updateSpecificProperties()
{
    const QMetaObject *metaobject = m_test->metaObject();
    int count = metaobject->propertyCount();
    for (int i=0; i<count; ++i) {
        QMetaProperty metaproperty = metaobject->property(i);
        const char *name = metaproperty.name();
        QVariant value = m_test->property(name);
        setProperty(name, value);
    }
}

/***********************************************/

TTest *TTest::clone(const QString &newName)
{
    TTest *result = new TTest(newName, parent());
    // TNode properties
    result->m_Path = m_Path;
    result->m_Comment = m_Comment;
    // TTest properties
    result->b_Enabled = b_Enabled;
    result->b_Paused = b_Paused;
    result->setTest(m_test->clone());
    result->m_agent = m_agent;
    result->a_AlertProfileID = a_AlertProfileID;
    result->a_PrivateLog = a_PrivateLog;
    result->a_RelatedURL = a_RelatedURL;
    // Log & Reports options
    result->b_UseCommonLog = b_UseCommonLog;
    result->a_CommonLogMode = a_CommonLogMode;
    result->b_UsePrivateLog = b_UsePrivateLog;
    result->a_PrivateLogMode = a_PrivateLogMode;
    result->b_ExcludeFromHtmlReport = b_ExcludeFromHtmlReport;
    result->b_ExcludeFromWmlReport = b_ExcludeFromWmlReport;
    result->b_ExcludeFromDbfReport = b_ExcludeFromDbfReport;
    // Dependencies
    result->a_DependencyMode = a_DependencyMode;
    result->m_masterTests.append(m_masterTests);
    result->a_DependencyCondition = a_DependencyCondition;
    result->a_DependencyOtherwiseStatus = a_DependencyOtherwiseStatus;
    result->b_SynchronizeCounters = b_SynchronizeCounters;
    result->b_SynchronizeStatusAlerts = b_SynchronizeStatusAlerts;
    // Optional status propcessing
    result->b_ReverseAlert = b_ReverseAlert;
    result->b_UnknownIsBad = b_UnknownIsBad;
    result->b_WarningIsBad = b_WarningIsBad;
    result->b_UseWarningScript = b_UseWarningScript;
    result->b_UseNormalScript = b_UseNormalScript;
    result->b_TuneUpReply = b_TuneUpReply;
    result->a_WarningScript = a_WarningScript;
    result->a_NormalScript = a_NormalScript;
    result->a_TuneUpScript = a_TuneUpScript;
    // schedule
    switch (m_schedule.getMode()) {
    case TSchedule::Regular:
        result->setRegularSchedule(m_schedule.getInterval(), m_schedule.getScheduleName());
        break;
    case TSchedule::OneTestPerDay:
        result->setIrregularSchedule(0,scheduleDay(),scheduleTime());
        break;
    case TSchedule::OneTestPerWeek:
        result->setIrregularSchedule(1,scheduleDay(),scheduleTime());
        break;
    case TSchedule::OneTestPerMonth:
        result->setIrregularSchedule(2,scheduleDay(),scheduleTime());
        break;
    case TSchedule::ByExpression:
        result->setByExpressionSchedule(scheduleExpr1(),scheduleExpr2());
        break;
    }
    result->updateSpecificProperties();
    return result;
}

/***********************************************/

QString TTest::testName() const
{
    if (getName().isEmpty()) {
        return m_test->getDafaultName();
    }
    return getName();
}

/***********************************************/

QString TTest::alertProfileName() const
{
    if (a_AlertProfileID < 0 || a_AlertProfileID >= GData::actionProfiles.count()) {
        return QString();
    }
    return GData::actionProfiles.at(a_AlertProfileID).name;
}

/***********************************************/

QString TTest::masterTests() const
{
    QString result;
    foreach(const TTestPair &test, m_masterTests) {
        if (!result.isEmpty()) {
            result.append("\n");
        }
        result.append(test.first->testName());
    }
    return result;
}

/******************************************************************/

void TTest::setRegularSchedule(const int interval, const QString schedName)
{
    m_schedule.setRegular(interval, schedName);
}

/******************************************************************/

void TTest::setIrregularSchedule(const int mode, const int schedDay, const QTime schedTime)
{
    switch (mode) {
    case 0: m_schedule.setOneTestPerDay(schedTime); break;
    case 1: m_schedule.setOneTestPerWeek(schedDay, schedTime); break;
    case 2: m_schedule.setOneTestPerMonth(schedDay, schedTime); break;
    }
}

/******************************************************************/

void TTest::setByExpressionSchedule(const QString expr1, const QString expr2)
{
    m_schedule.setByExpression(expr1, expr2);
}

/******************************************************************/

QString TTest::status() const
{
    if (!isEnabled()) return TEnums::testStatus(TestStatus::Disabled);
    if (isPaused()) return TEnums::testStatus(TestStatus::Paused);
    return TEnums::testStatus(m_Status);
}
/******************************************************************/

TestStatus TTest::getStatusID() const
{
    if (!isEnabled()) return TestStatus::Disabled;
    if (isPaused()) return TestStatus::Paused;
    return m_Status;
}

/******************************************************************/

QString TTest::ackResponseTime() const
{
    if (m_SimpleStatusID == SimpleStatusID::UP) return QString();
    if (m_Acknowledged) {
        return Utils::getTimeFromMs(m_AckResponseTime);
    } else {
        return "not acknowledged";
    }
}

/***********************************************/

void TTest::slotTimeout()
{
    emit readyRun(qobject_cast<TNode*>(this));
}

/***********************************************/

void TTest::setTest(TTestMethod *test)
{
    if (m_test == test) return;
    if (m_test) {
        disconnect(m_test,SIGNAL(testSuccess()), this, SLOT(onTestPerformed()));
        disconnect(m_test,SIGNAL(testFailed()), this, SLOT(onTestPerformed()));
        delete m_test;
    }
    m_test = test;
    connect(m_test,SIGNAL(testSuccess()), this, SLOT(onTestPerformed()));
    connect(m_test,SIGNAL(testFailed()), this, SLOT(onTestPerformed()));
}

/***********************************************/

void TTest::resetCurrentTestState()
{
    m_TestTime = QDateTime::currentDateTime();
    a_Reply_Number = 0.0;
    m_Status = TestStatus::NotTested;
    m_SimpleStatusID = SimpleStatusID::UNKNOWN;
    a_CurrentStatusIteration = 0;
    a_Recurrences = 0;
    m_CurrentStatusDuration = 0;
    a_FailureID = 0;
    a_LastFailureID = 0;
}

/***********************************************/

void TTest::resetSuggestedTestState()
{
    m_SuggestedStatus = TestStatus::NotTested;
    m_SuggestedSimpleStatusID = SimpleStatusID::UNKNOWN;
    a_SuggestedReply_Integer = 0;
    a_SuggestedRecurrences = 0;
    a_FailureIteration = 0;
}

/***********************************************/

void TTest::resetAcknowlegedInfo()
{
    m_Acknowledged = false;
    m_AckResponseTime = 0;
    a_AckRecurrences = 0;
}

/***********************************************/

void TTest::resetPreviousStatusInfo()
{
    m_LastStatus = TestStatus::NotTested;
    m_LastSimpleStatusID = SimpleStatusID::UNKNOWN;
    m_PreviousStatusID = TestStatus::NotTested;
    m_PreviousStatusTime = QDateTime::currentDateTime();
    m_PreviousStatusDuration = 0;
}

/***********************************************/

void TTest::resetStatistics()
{
    m_StatusChangedTime = QDateTime::currentDateTime();
    a_StatusChangesCnt = 0;
    a_TotalTests = 0;
    m_TotalTime = 0;
    a_FailedCnt = 0;
    a_PassedCnt = 0;
    a_UnknownCnt = 0;
    m_AliveTime = 0;
    m_DeadTime = 0;
    m_UnknownTime = 0;
    m_AliveRatio = 0.0;
    m_DeadRatio = 0.0;
    m_UnknownRatio = 0.0;
    m_AverageReply = 0.0;
    m_MinReply = 0.0;
    m_MaxReply = 0.0;
}

/***********************************************/

} // namespace SDPO
