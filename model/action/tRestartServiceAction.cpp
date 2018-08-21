#include "tRestartServiceAction.h"

namespace SDPO {


RestartServiceAction::RestartServiceAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::ServiceRestart);
        b_DoNotStartService = false;
        b_ConnectAs = false;
}

/******************************************************************/

void RestartServiceAction::run(TTest *test)
{
    Q_UNUSED(test)
        // Do nothig
}

/******************************************************************/

QStringList RestartServiceAction::description(bool isBad)
{
        QStringList result = TestAction::description(isBad);
        result.append(QString("Comp: %1").arg(a_RestartServiceOn));
        result.append(QString("Service: %1").arg(a_ServiceName));
        result.append(QString("Connect: %1").arg(b_ConnectAs?"Yes":"No"));
        result.append(QString("Username: %1").arg(a_ConnectAsLogin));
        return result;
}

/******************************************************************/

TestAction *RestartServiceAction::clone()
{
        RestartServiceAction *result = new RestartServiceAction();
        copyProperties(result);
        result->setRestartServiceOn(a_RestartServiceOn);
        result->setServiceName(a_ServiceName);
        result->setDoNotStartService(b_DoNotStartService);
        result->setConnectAs(b_ConnectAs);
        result->setConnectAsLogin(a_ConnectAsLogin);
        result->setConnectAsPassword(a_ConnectAsPassword);
        return result;
}

/******************************************************************/

} // namespace SDPO
