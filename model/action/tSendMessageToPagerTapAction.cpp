#include "tSendMessageToPagerTapAction.h"

namespace SDPO {

/******************************************************************/

SendMessageToPagerTapAction::SendMessageToPagerTapAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::MsgPagerTap);
    a_MaxCharacter = 40;
    a_Parity = "E,7,1";
}

/******************************************************************/

void SendMessageToPagerTapAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Do nothig
}

/******************************************************************/

QStringList SendMessageToPagerTapAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("AccessNum: %1").arg(a_AccessNumber));
    result.append(QString("Password: %1").arg(a_Password));
    result.append(QString("BlockSize: %1").arg(a_MaxCharacter));
    result.append(QString("Parity: %1").arg(a_Parity));
    result.append(QString("PagerID: %1").arg(a_PagerId));
    return result;
}

/******************************************************************/

TestAction *SendMessageToPagerTapAction::clone()
{
    SendMessageToPagerTapAction *result = new SendMessageToPagerTapAction();
    copyProperties(result);
    result->setAccessNumber(a_AccessNumber);
    result->setPassword(a_Password);
    result->setMaxCharacter(a_MaxCharacter);
    result->setParity(a_Parity);
    result->setPagerId(a_PagerId);
    result->setMsgTemplate(a_MsgTemplate);
    return result;
}

/******************************************************************/

} // namespace SDPO
