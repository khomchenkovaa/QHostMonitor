#include "tSendMessageToIcqAction.h"

namespace SDPO {

SendMessageToIcqAction::SendMessageToIcqAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::MsgIcq);
}

void SendMessageToIcqAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Do nothig
}

QStringList SendMessageToIcqAction::description(bool isBad)
{

    QStringList result = TestAction::description(isBad);
    result.append(QString("To ICQ: %1").arg(a_SendMessage));
    result.append(QString("Mail template: %1").arg(a_MsgTemplate));
    return result;
}

TestAction *SendMessageToIcqAction::clone()
{
    SendMessageToIcqAction *result = new SendMessageToIcqAction();
    copyProperties(result);
    result->setSendMessage(a_SendMessage);
    result->setMsgTemplate(a_MsgTemplate);
    return result;
}

} // namespace SDPO
