#include "tDialupToTheNetworkAction.h"

namespace SDPO {

/******************************************************************/

DialupToTheNetworkAction::DialupToTheNetworkAction(QObject *parent) :
    TestAction(parent)

{
    setAction(TActionID::DialUpConnect);
}

/******************************************************************/

void DialupToTheNetworkAction::run(TTest *test)
{
    Q_UNUSED(test)
    // TODO DialupToTheNetworkAction::run implementation
}

/******************************************************************/

QStringList DialupToTheNetworkAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Connection: %1").arg(a_DialUpConnection));
    result.append(QString("User name: %1").arg(a_UserName));
    result.append(QString("Save password: %1").arg(b_SavePassword?"Yes":"No"));
    result.append(QString("Show window: %1").arg(b_ShowDialUpWindow?"Yes":"No"));
    result.append(QString("Redials: %1").arg(a_Retries));
    return result;
}

/******************************************************************/

TestAction *DialupToTheNetworkAction::clone()
{
    DialupToTheNetworkAction *result = new DialupToTheNetworkAction();
    copyProperties(result);
    result->setDialUpConnection(a_DialUpConnection);
    result->setUserName(a_UserName);
    result->setPassword(a_Password);
    result->setSavePassword(b_SavePassword);
    result->setShowDialUpWindow(b_ShowDialUpWindow);
    result->setRetries(a_Retries);
    return result;
}

/******************************************************************/

} // namespace SDPO
