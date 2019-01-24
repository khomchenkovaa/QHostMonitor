#include "tRebootRemoteSystemAction.h"

namespace SDPO {

/******************************************************************/

RebootRemoteSystemAction::RebootRemoteSystemAction(QObject *parent) :
    TestAction(parent)
{
     setAction(TActionID::RebootRemote);
     a_TimeToDisplay = 6;
     b_ForceProcesses = false;
}

/******************************************************************/

void RebootRemoteSystemAction::run(TTest *test)
{
    Q_UNUSED(test)
 // Do nothig
}

/******************************************************************/

QStringList RebootRemoteSystemAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Comp: %1").arg(a_ComputerName));
    result.append(QString("Message: %1").arg(a_MessageToDisplay));
    result.append(QString("Delay: %1").arg(a_TimeToDisplay));
    result.append(QString("Shutdown: %1").arg(a_Method));
    result.append(QString("Force: %1").arg(b_ForceProcesses?"Yes":"No"));
    return result;
}

/******************************************************************/

TestAction *RebootRemoteSystemAction::clone()
{
    RebootRemoteSystemAction *result = new RebootRemoteSystemAction();
    copyProperties(result);
    result->setComputerName(a_ComputerName);
    result->setMessageToDisplay(a_MessageToDisplay);
    result->setTimeToDisplay(a_TimeToDisplay);
    result->setMethod(a_Method);
    result->setForceProcesses(b_ForceProcesses);
    return result;
}

/******************************************************************/

} // namespace SDPO
