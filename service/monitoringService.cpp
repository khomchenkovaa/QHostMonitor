#include "monitoringService.h"
#include <QThreadPool>
#include "monitoringTask.h"
#include "tTest.h"
#include "utils.h"

namespace SDPO {

/***********************************************/

MonitoringService::MonitoringService(HMListService *hml, ActionService *act, int threadCount, QObject *parent) :
    ManageableService(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(threadCount);
    connect(hml, SIGNAL(monitoringStarted(bool)), SLOT(setRunningState(bool)));
    connect(hml, SIGNAL(monitoringPaused(int)), SLOT(pause(int)));
    connect(hml, SIGNAL(readyRun(TNode*)), SLOT(runTest(TNode*)));
    connect(this, SIGNAL(stateChanged(QString,bool)), act, SLOT(runProfile(QString,bool)));
}

/***********************************************/

MonitoringService::~MonitoringService()
{
    Utils::DestructorMsg(this);
}

/***********************************************/

void MonitoringService::clear()
{
    disconnect(this, SLOT(runTest(TNode*)));
    QThreadPool::globalInstance()->clear();
    QThreadPool::globalInstance()->waitForDone(5);
}

/***********************************************/

void MonitoringService::runTest(TNode *item)
{
    if (item->getType() != TNode::TEST) return;
    TTest* test = qobject_cast<TTest*>(item);

    checkState(isRunning());

    if (!isRunning() || !test->isEnabled() || test->isPaused()) {
        test->restart();
        return;
    }

    MonitoringTask *task = new MonitoringTask(test->method());
    QThreadPool::globalInstance()->start(task);
}

/***********************************************/

} // namespace SDPO
