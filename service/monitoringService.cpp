#include "monitoringService.h"
#include <QThreadPool>
#include "monitoringTask.h"
#include "tTest.h"
#include "utils.h"

namespace SDPO {

/***********************************************/

MonitoringService::MonitoringService(int threadCount, QObject *parent) :
    QObject(parent)
{
    b_Paused = false;
    QThreadPool::globalInstance()->setMaxThreadCount(threadCount);
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

    if (!test->isEnabled()) return;
    if (test->isPaused()) return;
    MonitoringTask *task = new MonitoringTask(test->test());
    QThreadPool::globalInstance()->start(task);
}

/***********************************************/

} // namespace SDPO
