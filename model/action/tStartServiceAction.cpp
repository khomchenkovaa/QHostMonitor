#include "tStartServiceAction.h"

namespace SDPO {

/******************************************************************/

StartServiceAction::StartServiceAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::ServiceStart);
    b_ConnectAs = false;
}

/******************************************************************/

void StartServiceAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Do nothig
}

/******************************************************************/

QStringList StartServiceAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Comp: %1").arg(a_StartServiceOn));
    result.append(QString("Service: %1").arg(a_ServiceName));
    result.append(QString("Parameters: %1").arg(a_Parameters));
    result.append(QString("Connect: %1").arg(b_ConnectAs?"Yes":"No"));
    result.append(QString("Username: %1").arg(a_ConnectAsLogin));
    return result;
}

/******************************************************************/

TestAction *StartServiceAction::clone()
{
    StartServiceAction *result = new StartServiceAction();
    copyProperties(result);
    result->setStartServiceOn(a_StartServiceOn);
    result->setServiceName(a_ServiceName);
    result->setParameters(a_Parameters);
    result->setConnectAs(b_ConnectAs);
    result->setConnectAsLogin(a_ConnectAsLogin);
    result->setConnectAsPassword(a_ConnectAsPassword);
    return result;
}

/******************************************************************/

}// namespace SDPO
