#include "tTestAction.h"
#include <QDebug>

namespace SDPO {

/***********************************************/

TestAction::TestAction(QObject *parent) :
    QObject(parent)
{
    a_Action = TActionID::NoAction;
    a_StartAfter = 1;
    a_Retries = -1;
    a_Mode = TActionMode::Standard;
}

/***********************************************/

TestAction::~TestAction()
{

}

/***********************************************/

void TestAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Do nothig
}

/***********************************************/

QStringList TestAction::description(bool isBad)
{
    QStringList result;
    TAction action = TAction::actionList.at(static_cast<int>(a_Action));
    result.append(QString("Action: %1").arg(action.name));
    if (a_Mode == TActionMode::Standard) {
        result.append(QString("Start after: %1 consecutive '%2' result(s)").arg(a_StartAfter).arg(isBad? "bad":"good"));
        if (a_Retries == -1) {
            result.append(QString("Retries: until status changes"));
        } else {
            result.append(QString("Retries: %1 time(s)").arg(a_Retries));
        }
    } else if (a_Mode == TActionMode::Advanced) {
        result.append(QString("Condition to start:%1").arg(a_Condition));
    } else {
        result.append(QString("Condition to start: Schedule"));
    }
    return result;
}

/***********************************************/

TestAction *TestAction::clone()
{
    TestAction *result = new TestAction();
    copyProperties(result);
    return result;
}

/***********************************************/

void TestAction::copyProperties(TestAction *item)
{
    item->setAction(a_Action);
    item->setName(a_Name);
    item->setAgent(a_Agent);
    item->setStoreResult(b_StoreResult);
    item->setMode(a_Mode);
    item->setStartAfter(a_StartAfter);
    item->setRetries(a_Retries);
    item->setCondition(a_Condition);
}

/***********************************************/

bool TestAction::checkToRun(TTest *test)
{
    if (test->getRecurrences() < a_StartAfter) return false;
    if (a_Retries == -1) return true;
    if (test->getRecurrences() < (a_StartAfter + a_Retries)) return true;
    return false;
}

/***********************************************/

} // namespace SDPO

