#include "tSendMessageToBeeperAction.h"

namespace SDPO {

/******************************************************************/

SendMessageToBeeperAction::SendMessageToBeeperAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::MsgBeeper);
    a_Delay = 1;
}

/******************************************************************/

void SendMessageToBeeperAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Do nothig
}

/******************************************************************/

QStringList SendMessageToBeeperAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Number: %1").arg(a_Beeper));
    result.append(QString("Message: %1").arg(a_SendMessage));
    result.append(QString("TermStr: %1").arg(a_TerminationString));
    result.append(QString("Delay: %1").arg(a_Delay));
    return result;
}

/******************************************************************/

TestAction *SendMessageToBeeperAction::clone()
{
   SendMessageToBeeperAction *result = new SendMessageToBeeperAction();
    copyProperties(result);
    result->setBeeper(a_Beeper);
    result->setSendMessage(a_SendMessage);
    result->setTerminationString(a_TerminationString);
    result->setDelay(a_Delay);
    return result;
}

/******************************************************************/

} // namespace SDPO
