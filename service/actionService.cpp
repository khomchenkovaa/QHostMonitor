#include "actionService.h"
#include "utils.h"
#include "actionTask.h"
#include "sdpoTestActions.h"
#include "hmScriptRunner.h"
#include "gData.h"

#include <QDebug>

namespace SDPO {

/***********************************************/

ActionService::ActionService(HMListService *hml, LogService *log, QObject *parent) :
    ManageableService(parent),
    m_HML(hml),
    m_Log(log)
{
    connect(m_HML, SIGNAL(testUpdated(TNode*)), SLOT(runActions(TNode*)));
    connect(m_HML, SIGNAL(alertsEnabled(bool)), SLOT(setRunningState(bool)));
    connect(m_HML, SIGNAL(alertsPaused(int)), SLOT(pause(int)));
    connect(m_Log, SIGNAL(logAlert(int,TTest*,bool)), SLOT(runProfile(int,TTest*,bool)));
    connect(this, SIGNAL(stateChanged(QString,bool)), SLOT(runProfile(QString,bool)));
}

/***********************************************/

ActionService::~ActionService()
{
    Utils::DestructorMsg(this);
}

/***********************************************/

void ActionService::clear()
{
    disconnect(this, SLOT(runActions(TTest*)));
}

/***********************************************/

void ActionService::runActions(TNode *item)
{
    checkState(isRunning());

    if(!isRunning()) return;

    TTest *test = qobject_cast<TTest*>(item);
    if (test->getAlertProfileID() == -1) {
        return;
    }

    if (test->simpleStatusID() == SimpleStatusID::DOWN) {
        runProfile(test->getAlertProfileID(), test, true);
    }
    if (test->simpleStatusID() == SimpleStatusID::UP) { //! TODO информирование только один раз
        runProfile(test->getAlertProfileID(), test, false);
    }
}

/***********************************************/

void ActionService::runProfile(const int profileId, TTest *test, const bool isBad)
{
    if (profileId < 0 || profileId >= GData::actionProfiles.count()) {
        return;
    }

    GActionProfile curProfile = GData::actionProfiles.at(profileId);

    if (isBad) {
        foreach(TestAction *action, curProfile.onBad) {
            tryToRun(test, action);
        }
    } else {
        foreach(TestAction *action, curProfile.onGood) {
            tryToRun(test, action);
        }
    }
}

/***********************************************/

void ActionService::runProfile(QString profile, const bool isStarted)
{
    int profileId = GData::getActionProfileIdx(profile);
    if (profileId == -1) return;
    GActionProfile curProfile = GData::actionProfiles.at(profileId);
    if (isStarted) {
        foreach(TestAction *action, curProfile.onGood) {
            qDebug() << "Action on service started:" << action->getName();
            //! TODO run action without test
            //tryToRun(test, action);
        }
    } else {
        foreach(TestAction *action, curProfile.onBad) {
            qDebug() << "Action on service stoped:" << action->getName();
            //! TODO run action without test
            //tryToRun(test, action);
        }
    }
}

/***********************************************/

void ActionService::tryToRun(TTest *test, TestAction *action)
{
    if (!action->checkToRun(test)) return;
    if (action->getAction() == TActionID::WinPopup) {
        emit actionWinPopup(test);
    } else if (action->getAction() == TActionID::LogRecord) {
        RecordSdpoLogAction *logRecord = qobject_cast<RecordSdpoLogAction*>(action);
        if (logRecord->isAddCommonLog()) {
            m_Log->writeCommonLog(test);
        }
        if (logRecord->isAddPrivateLog()) {
            m_Log->writePrivateLog(test);
        }
        if (logRecord->isAddSpecificLog()) {
            m_Log->writeSpecificFileLog(test, logRecord->getSpecificLogFile());
        }
    } else if (action->getAction() == TActionID::RunScript) {
        RunHmsScriptAction *scriptAction = qobject_cast<RunHmsScriptAction*>(action);
        QString scriptFile = scriptAction->getScriptFile();
        qDebug() << "About to running script" << scriptFile;
        HMScriptRunner runner(m_HML);
        runner.loadScript(scriptFile);
        if(!runner.run()) {
            qDebug() << runner.scriptErrors();
        }
    } else {
        ActionTask task(test, action, this);
        task.run();
    }
}

/***********************************************/

} // namespace SDPO
