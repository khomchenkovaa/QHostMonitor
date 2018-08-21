#include "tRebootLocalMachineAction.h"

namespace SDPO {

/******************************************************************/

RebootLocalMachineAction::RebootLocalMachineAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::RebootLocal);

}

/******************************************************************/

void RebootLocalMachineAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Do nothing
}

/******************************************************************/

QStringList RebootLocalMachineAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    if(b_Logout)
        result.append(QString("Method: Logout"));
    else if(b_Reboot)
        result.append(QString("Method: Reboot"));
    else if(b_Shutdown)
        result.append(QString("Method: Shutdown"));
    else if(b_PowerOff)
        result.append(QString("Method: PowerOff"));
    result.append(QString("Force: %1").arg(b_ForceProcesses?"Yes":"No"));
    return result;
}

/******************************************************************/

TestAction *RebootLocalMachineAction::clone()
{
    RebootLocalMachineAction *result = new RebootLocalMachineAction();
    copyProperties(result);
    result->setLogout(b_Logout);
    result->setReboot(b_Reboot);
    result->setShutdown(b_Shutdown);
    result->setPowerOff(b_PowerOff);
    result->setForceProcesses(b_ForceProcesses);
    return result;
}

/******************************************************************/

} // namespace SDPO
