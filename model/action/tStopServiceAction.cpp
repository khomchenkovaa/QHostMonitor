#include "tStopServiceAction.h"

namespace SDPO {

/*****************************************************************/

StopServiceAction::StopServiceAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::ServiceStop);
    b_ConnectAs = false;
}

/*****************************************************************/

void StopServiceAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Do nothig
}

/*****************************************************************/

QStringList StopServiceAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Comp: %1").arg(a_StopServiceOn));
    result.append(QString("Service: %1").arg(a_ServiceName));
    result.append(QString("Parameters: %1").arg(a_Parameters));
    result.append(QString("Connect: %1").arg(b_ConnectAs?"Yes":"No"));
    result.append(QString("Username: %1").arg(a_ConnectAsLogin));
    return result;
}

/*****************************************************************/

TestAction *StopServiceAction::clone()
{
    StopServiceAction *result = new StopServiceAction();
    copyProperties(result);
    result->setStopServiceOn(a_StopServiceOn);
    result->setServiceName(a_ServiceName);
    result->setParameters(a_Parameters);
    result->setConnectAs(b_ConnectAs);
    result->setConnectAsLogin(a_ConnectAsLogin);
    result->setConnectAsPassword(a_ConnectAsPassword);
    return result;
}

/*****************************************************************/

} // namespace SDPO
