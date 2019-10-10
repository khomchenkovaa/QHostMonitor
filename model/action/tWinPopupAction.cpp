#include "tWinPopupAction.h"

namespace SDPO {

/******************************************************************/

WinPopupAction::WinPopupAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::WinPopup);
}

/******************************************************************/

void WinPopupAction::run(TTest* test)
{
    Q_UNUSED(test)
    // Action runs from ActionService
}

/******************************************************************/

QStringList WinPopupAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    return result;
}

/******************************************************************/

TestAction *WinPopupAction::clone()
{
    WinPopupAction* result = new WinPopupAction();
    copyProperties(result);
    return result;
}

/******************************************************************/

} // namespace SDPO
