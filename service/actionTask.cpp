#include "actionTask.h"
#include "tTest.h"
#include "tTestAction.h"

namespace SDPO {

/******************************************************************/

ActionTask::ActionTask(TTest *test, TestAction *act, QObject *parent) :
    QObject(parent),
    m_test(test),
    m_action(act)
{
}

/******************************************************************/

void ActionTask::run()
{
    m_action->run(m_test);
}

/******************************************************************/

} // namespace SDPO
