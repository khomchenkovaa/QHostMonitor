#include "tTest.h"
#include "tTestAction.h"
#include "gData.h"
#include "sdpoTestMethods.h"
#include "global/gUserVars.h"
#include "global/gMacroTranslator.h"
#include <QScriptEngine>
#include <QDebug>

namespace SDPO {

/***********************************************/

int TTest::failureCount = 0;

/***********************************************/

TTest::TTest(const int id, const QString &name, QObject *parent) :
    TNode(id, name, TNode::TEST, parent)
{
    m_TMethod = new TestMethod(TMethodID::Empty);

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
    m_Stat.clear();

    connect(&m_schedule, &TSchedule::activated, this, &TTest::slotTimeout);
}

/***********************************************/

TTest::~TTest()
{
    m_links.clear();
    delete m_agent;
    delete m_TMethod;
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
    MVariablesStruct mvs = TMacro::varStruct(globalVar);
    return property(mvs.name.toLatin1());
}

/******************************************************************/

void TTest::onTestPerformed()
{
    // 1. (perform the test)
    TestResult testResult = m_TMethod->getResult();

    // 2. process "Reverse alert" option
    if(b_ReverseAlert) {
        testResult.reverse();
    }

    // 3. set “suggested” macro variables (%SuggestedStatus%, %SuggestedSimpleStatus%, %SuggestedReply%,  %SuggestedRecurrences% and %FailureIteration%)
    // without touching regular counters (%Status%, %Reply%, %Recurrences%, etc);
    setSuggestedVars(testResult);

    // 4. check "Warning" and "Normal" expressions
    processUserStatusExpressions(testResult);

    // 5. process “Tune up Reply” option
    tuneUpReply(testResult);

    // 6. modify current test status and statistisc counters (Status, Reply, Alive%, Passed tests, Failed tests, etc)
    dynamicStatistics(testResult);

    restart();
    qDebug() << "Test:" << getName() << "done" << endl;
    emit testDone(this);
}

/******************************************************************/

void TTest::restart()
{
    m_schedule.start();
}

/******************************************************************/

void TTest::setSuggestedVars(const TestResult testResult)
{
    m_SuggestedLastState = m_SuggestedState;
    m_SuggestedState = testResult;

    if (testResult.simpleStatus(b_UnknownIsBad) == m_SuggestedLastState.simpleStatus(b_UnknownIsBad)) {
        m_Recurences.suggestedSimpleStatus++;
    } else {
        m_Recurences.suggestedSimpleStatus = 0;
    }

    if (testResult.simpleStatus(b_UnknownIsBad) == SimpleStatusID::DOWN) {
        m_Recurences.failure++;
    } else {
        m_Recurences.failure=0;
    }
}

/******************************************************************/

void TTest::processUserStatusExpressions(TestResult &testResult)
{
    if (b_UseWarningScript) {
        GMacroTranslator translator(a_WarningScript, this);
        QString script = translator.translate();
        QScriptEngine scriptEngine;
        QScriptValue value = scriptEngine.evaluate(script);
        if (value.isBool() && value.toBool()) {
            testResult.status = TestStatus::Warning;
        }
    }

    if (b_UseNormalScript) {
        GMacroTranslator translator(a_NormalScript, this);
        QString script = translator.translate();
        QScriptEngine scriptEngine;
        QScriptValue value = scriptEngine.evaluate(script);
        if (value.isBool() && value.toBool()) {
            testResult.status = TestStatus::Normal;
        }
    }
}

/******************************************************************/

void TTest::tuneUpReply(TestResult &testResult)
{
    if (b_TuneUpReply) {
        GMacroTranslator translator(a_TuneUpScript, this);
        QString script = translator.translate();
        QScriptEngine scriptEngine;
        QScriptValue value = scriptEngine.evaluate(script);
        testResult.reply = value.toString();
    }
}

/******************************************************************/

void TTest::dynamicStatistics(const TestResult testResult)
{
    // helpers
    bool statusChanged = (testResult.status != m_CurrentState.status);
    SimpleStatusID simpleStatusID = testResult.simpleStatus(b_UnknownIsBad, b_WarningIsBad);
    bool simpleStatusChanged = (simpleStatusID != m_CurrentState.simpleStatus(b_UnknownIsBad, b_WarningIsBad));
    qint64 delta = testResult.date.toMSecsSinceEpoch() - m_CurrentState.date.toMSecsSinceEpoch();

    // last state
    m_LastState = m_CurrentState;

    // previous state
    if (simpleStatusChanged) {
        m_PreviousState = m_CurrentState;
    }

    // current test state
    m_CurrentState = testResult;

    if (statusChanged) {
        m_Recurences.currentStatus = 0;
    } else {
        m_Recurences.currentStatus++;
    }

    if (simpleStatusChanged) {
        m_Recurences.currentSimpleStatus = 0;
        m_Stat.previousDuration = m_Stat.currentDuration;
        m_Stat.currentDuration = 0;
        m_Stat.previousTime = m_Stat.changedTime;
        m_Stat.changedTime = testResult.date;
        m_Stat.changesCnt++;
        if (simpleStatusID == SimpleStatusID::UP) {
            a_LastFailureID = a_FailureID;
            a_FailureID = 0;
        }
        if (simpleStatusID == SimpleStatusID::DOWN) {
            a_FailureID = ++failureCount;
        }
    } else {
        m_Recurences.currentSimpleStatus++;
        m_Stat.currentDuration = testResult.date.toMSecsSinceEpoch() - m_Stat.changedTime.toMSecsSinceEpoch();
    }

    // statistical information
    m_Stat.totalTests++;
    m_Stat.totalTime += delta;
    switch (simpleStatusID) {
        case SimpleStatusID::UP:
            m_Stat.passedCnt++;
            m_Stat.aliveTime += delta;
            break;
        case SimpleStatusID::WARNING:
        case SimpleStatusID::DOWN:
            m_Stat.deadTime += delta;
            m_Stat.failedCnt++;
            break;
        case SimpleStatusID::UNKNOWN:
            m_Stat.unknownTime += delta;
            m_Stat.unknownCnt++;
            break;
    }

    if (simpleStatusID == SimpleStatusID::UP) {
        if (m_Stat.passedCnt == 1) {
            m_Stat.minReply = testResult.replyDouble;
        } else if (m_Stat.minReply < testResult.replyDouble) {
            m_Stat.minReply = testResult.replyDouble;
        }
        if (m_Stat.maxReply > testResult.replyDouble) {
            m_Stat.maxReply = testResult.replyDouble;
        }
        m_Stat.avgReply = (m_Stat.avgReply*(m_Stat.passedCnt-1) + testResult.replyDouble) / m_Stat.passedCnt;
    }
}

/***********************************************/

void TTest::updateSpecificProperties()
{
    const QMetaObject *metaobject = m_TMethod->metaObject();
    int count = metaobject->propertyCount();
    for (int i=0; i<count; ++i) {
        QMetaProperty metaproperty = metaobject->property(i);
        const char *name = metaproperty.name();
        QVariant value = m_TMethod->property(name);
        setProperty(name, value);
    }
}

/***********************************************/

TTest *TTest::clone(const int newID, const QString &newName)
{
    TTest *result = new TTest(newID, newName, parent());
    // TNode properties
    result->m_Path = m_Path;
    result->m_Comment = m_Comment;
    // TTest properties
    result->b_Enabled = b_Enabled;
    result->b_Paused = b_Paused;
    result->setMethod(m_TMethod->clone());
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
    case TSchedule::OncePerDay:
        result->setOncePerDaySchedule(m_schedule.getScheduleTime());
        break;
    case TSchedule::OncePerWeek:
        result->setOncePerWeekSchedule(m_schedule.getScheduleDay(),m_schedule.getScheduleTime());
        break;
    case TSchedule::OncePerMonth:
        result->setOncePerMonthSchedule(m_schedule.getScheduleDay(),m_schedule.getScheduleTime());
        break;
    case TSchedule::ByExpression:
        result->setByExpressionSchedule(m_schedule.getScheduleExpr1(),m_schedule.getScheduleExpr2());
        break;
    }
    result->updateSpecificProperties();
    return result;
}

/***********************************************/

QString TTest::executionLog() const
{
    QString log = m_TMethod->getLog();

    TestResult tmResult = m_TMethod->getResult();
    log.append("\n****** Test Method Result ******\n");
    log.append(QString("* status: %1\n").arg(TEnums::testStatus(tmResult.status)));
    log.append(QString("* reply: %1\n").arg(tmResult.reply));
    log.append(QString("* reply float: %1\n").arg(tmResult.replyDouble));
    log.append(QString("* reply number: %1\n").arg(tmResult.replyInt));
    log.append(QString("* error: %1\n").arg(tmResult.error));
    log.append(QString("* date: %1\n").arg(tmResult.date.toString()));

    log.append("\n****** Test Properties ******\n");
    const QMetaObject *metaobject = metaObject();
    int count = metaobject->propertyCount();
    for (int i=0; i<count; ++i) {
        QMetaProperty metaproperty = metaobject->property(i);
        const char *name = metaproperty.name();
        QVariant value = property(name);
        switch (value.type()) {
        case QVariant::Int :
            log.append(QString("* %1: %2\n").arg(name).arg(value.toInt()));
            break;
        default:
            log.append(QString("* %1: %2\n").arg(name).arg(value.toString()));
        }
    }

    return log;
}

/***********************************************/

QString TTest::testName() const
{
    if (getName().isEmpty()) {
        return m_TMethod->getDefaultName();
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

QString TTest::status() const
{
    if (!isEnabled()) return TEnums::testStatus(TestStatus::Disabled);
    if (isPaused()) return TEnums::testStatus(TestStatus::Paused);
    return TEnums::testStatus(m_CurrentState.status);
}

/******************************************************************/

TestStatus TTest::getStatusID() const
{
    if (!isEnabled()) return TestStatus::Disabled;
    if (isPaused()) return TestStatus::Paused;
    return m_CurrentState.status;
}

/******************************************************************/

QString TTest::ackResponseTime() const
{
    if (m_CurrentState.simpleStatus(b_UnknownIsBad, b_WarningIsBad) == SimpleStatusID::UP) {
        return QString();
    }
    if (m_Acknowledged) {
        return Utils::duration(m_Acknowledge.time);
    } else {
        return "not acknowledged";
    }
}

/***********************************************/

void TTest::slotTimeout()
{
    qDebug() << "Test" << getName() << "ready run" << endl;
    emit readyRun(qobject_cast<TNode*>(this));
}

/***********************************************/

void TTest::setMethod(TestMethod *testMethod)
{
    if (m_TMethod == testMethod) return;
    if (m_TMethod) {
        disconnect(m_TMethod,SIGNAL(testSuccess()), this, SLOT(onTestPerformed()));
        disconnect(m_TMethod,SIGNAL(testFailed()), this, SLOT(onTestPerformed()));
        delete m_TMethod;
    }
    m_TMethod = testMethod;
    connect(m_TMethod,SIGNAL(testSuccess()), this, SLOT(onTestPerformed()));
    connect(m_TMethod,SIGNAL(testFailed()), this, SLOT(onTestPerformed()));
}

/***********************************************/

void TTest::resetCurrentTestState()
{
    m_CurrentState.clear();
    a_FailureID = 0;
    a_LastFailureID = 0;
}

/***********************************************/

void TTest::resetSuggestedTestState()
{
    m_SuggestedState.clear();
    m_SuggestedLastState.clear();
}

/***********************************************/

void TTest::resetAcknowlegedInfo()
{
    m_Acknowledged = false;
    m_Acknowledge.clear();
}

/***********************************************/

void TTest::resetPreviousStatusInfo()
{
    m_LastState.clear();
    m_PreviousState.clear();
}

/***********************************************/

} // namespace SDPO
