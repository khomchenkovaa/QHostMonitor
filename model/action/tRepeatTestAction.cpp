#include "tRepeatTestAction.h"

namespace SDPO {

/******************************************************************/

RepeatTestAction::RepeatTestAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::TestRepeat);
}

/******************************************************************/

void RepeatTestAction::run(TTest *test)
{
    Q_UNUSED(test)
    // TODO RepeatTestAction::run implementation
}

/******************************************************************/

QStringList RepeatTestAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    return result;
}

/******************************************************************/

TestAction *RepeatTestAction::clone()
{
    RepeatTestAction *result = new RepeatTestAction();
    copyProperties(result);
    result->setRepeatTest(b_RepeatTest);
    result->setRecheckTest(b_RecheckTest);
    return result;
}

/******************************************************************/

} // namespace SDPO
