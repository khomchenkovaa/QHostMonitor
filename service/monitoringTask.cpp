#include "monitoringTask.h"

/******************************************************************/

MonitoringTask::MonitoringTask(SDPO::TTestMethod *testMethod, QObject *parent) :
    QObject(parent), m_testMethod(testMethod), m_canceled(false)
{
    connect(m_testMethod, SIGNAL(destroyed()), this, SLOT(canceled()));
}

/******************************************************************/

void MonitoringTask::run()
{
    if (m_canceled) return;
    m_testMethod->run();
}

/******************************************************************/

void MonitoringTask::canceled()
{
    m_canceled = true;
}

/******************************************************************/
