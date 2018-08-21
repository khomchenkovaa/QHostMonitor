#include "actionService.h"
#include "utils.h"
#include "actionTask.h"
#include "action/sdpoTestActions.h"
#include "hmScriptRunner.h"

namespace SDPO {

/***********************************************/

ActionService::ActionService(HMListService *hml, QObject *parent) :
    QObject(parent),
    m_HML(hml)
{
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

void ActionService::tryToRun(TTest *test, TestAction *action)
{
    if (!action->checkToRun(test)) return;
    if (action->getAction() == TActionID::WinPopup) {
        emit actionWinPopup(test);
    } else if (action->getAction() == TActionID::LogRecord) {
        RecordSdpoLogAction *logRecord = qobject_cast<RecordSdpoLogAction*>(action);
        if (logRecord->isAddCommonLog()) {
            emit actionWriteCommonLog(test);
        }
        if (logRecord->isAddPrivateLog()) {
            emit actionWritePrivateLog(test);
        }
        if (logRecord->isAddSpecificLog()) {
            emit actionWriteSpecificFileLog(test, logRecord->getSpecificLogFile());
        }
    } else if (action->getAction() == TActionID::RunScript) {
        RunHmsScriptAction *scriptAction = qobject_cast<RunHmsScriptAction*>(action);
        QString scriptFile = scriptAction->getScriptFile();
        qDebug() << "About to running script" << scriptFile;
        HMScriptRunner runner(m_HML,scriptFile);
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
