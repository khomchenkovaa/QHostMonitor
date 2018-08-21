#include "tSendSmsSmppAction.h"

namespace SDPO{

/******************************************************************/

SendSmsSmppAction::SendSmsSmppAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::MsgSmsSmpp);
    a_DestTon = "Unknown";
    a_DestNpi = "Unknown";
}

/******************************************************************/

void SendSmsSmppAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Do nothig
}

/******************************************************************/

QStringList SendSmsSmppAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Recipient: %1").arg(a_DestPhone));
    result.append(QString("Mail template: %1").arg(a_MsgTemplate));
    return result;
}

/******************************************************************/

TestAction *SendSmsSmppAction::clone()
{
    SendSmsSmppAction *result = new SendSmsSmppAction();
    copyProperties(result);
    result->setDestPhone(a_DestPhone);
    result->setDestTon(a_DestTon);
    result->setDestNpi(a_DestNpi);
    result->setMsgTemplate(a_MsgTemplate);
    return result;
}

/******************************************************************/

} //namespace SDPO
