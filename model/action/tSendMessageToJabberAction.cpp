#include "tSendMessageToJabberAction.h"

namespace SDPO {

SendMessageToJabberAction::SendMessageToJabberAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::MsgJabber);
}

void SendMessageToJabberAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Do nothig
}

QStringList SendMessageToJabberAction::description(bool isBad)
{

    QStringList result = TestAction::description(isBad);
    result.append(QString("Recipient: %1").arg(a_SendMessage));
    result.append(QString("Mail to admin: %1").arg(a_MsgTemplate));
    return result;
}

TestAction *SendMessageToJabberAction::clone()
{
    SendMessageToJabberAction *result = new SendMessageToJabberAction();
    copyProperties(result);
    result->setSendMessage(a_SendMessage);
    result->setMsgTemplate(a_MsgTemplate);
    return result;
}

} // namespace SDPO
