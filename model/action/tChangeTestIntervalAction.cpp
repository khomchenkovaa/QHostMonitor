#include "tChangeTestIntervalAction.h"

namespace SDPO {

/******************************************************************/

ChangeTestIntervalAction::ChangeTestIntervalAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::TestInterval);
}

/******************************************************************/

void ChangeTestIntervalAction::run(TTest *test)
{
    Q_UNUSED(test)
    // TODO ChangeTestIntervalAction::run implementation
}

/******************************************************************/

QStringList ChangeTestIntervalAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    if(b_RestoreValue)
        result.append(QString("Restore original value"));
    else if(b_SetToTime)
        result.append(QString("Set new interval: %1").arg(a_TimeValueSelect.toString("hh:mm:ss")));
    else if(b_SetToPercent)
        result.append(QString("Change interval: %1").arg(a_Percent));
    return result;
}

/******************************************************************/

TestAction *ChangeTestIntervalAction::clone()
{
    ChangeTestIntervalAction *result = new ChangeTestIntervalAction();
    copyProperties(result);
    result->setRestoreValue(b_RestoreValue);
    result->setSetToTime(b_SetToTime);
    result->setTimeValueSelect(a_TimeValueSelect);
    result->setSetToPercent(b_SetToPercent);
    result->setPercent(a_Percent);
    return result;
}

/******************************************************************/

} // namespace SDPO
