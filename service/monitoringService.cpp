#include "monitoringService.h"
#include <QThreadPool>
#include "monitoringTask.h"
#include "tTest.h"
#include "utils.h"

#include <QDebug>

namespace SDPO {

/***********************************************/

MonitoringService::MonitoringService(int threadCount, QObject *parent) :
    ManageableService(parent)
{
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
    qDebug() << "Run test" << item->getName();
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
