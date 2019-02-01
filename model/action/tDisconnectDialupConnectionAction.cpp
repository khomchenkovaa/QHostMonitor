#include "tDisconnectDialupConnectionAction.h"

namespace SDPO {

/******************************************************************/

DisconnectDialupConnectionAction::DisconnectDialupConnectionAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::DialUpDisconnect);
}

/******************************************************************/

void DisconnectDialupConnectionAction::run(TTest *test)
{
    Q_UNUSED(test)
}

/******************************************************************/

QStringList DisconnectDialupConnectionAction::description(bool isBad)
{
        QStringList result = TestAction::description(isBad);
        result.append(QString("Connection: %1").arg(a_DialUpConnection));
        return result;
}

/******************************************************************/

TestAction *DisconnectDialupConnectionAction::clone()
{
    DisconnectDialupConnectionAction *result = new DisconnectDialupConnectionAction();
    copyProperties(result);
    result->setDialUpConnection(a_DialUpConnection);
    return result;
}

/******************************************************************/

} // namepsace SDPO
