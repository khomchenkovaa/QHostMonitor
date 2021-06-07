#include "monitoringTask.h"

/******************************************************************/

MonitoringTask::MonitoringTask(SDPO::TestMethod *testMethod, QObject *parent)
    : QObject(parent)
    , m_TestMethod(testMethod)
    , m_Canceled(false)
{
    connect(m_TestMethod, &QObject::destroyed, this, &MonitoringTask::canceled);
}

/******************************************************************/

void MonitoringTask::run()
{
    if (m_Canceled) return;
    m_TestMethod->run();
}

/******************************************************************/

void MonitoringTask::canceled()
{
    m_Canceled = true;
}

/******************************************************************/
