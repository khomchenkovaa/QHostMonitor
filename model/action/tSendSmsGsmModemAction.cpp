#include "tSendSmsGsmModemAction.h"

namespace SDPO {

/******************************************************************/

SendSmsGsmModemAction::SendSmsGsmModemAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::MsgSmsGsm);
    a_MsgClass = "0..Display immediately";
}

/******************************************************************/

void SendSmsGsmModemAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Do nothig
}

/******************************************************************/

QStringList SendSmsGsmModemAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Phone: %1").arg(a_DestPhone));
    result.append(QString("Msg class: %1").arg(a_MsgClass));
    result.append(QString("Message: %1").arg(a_MsgTemplate));
    return result;
}

/******************************************************************/

TestAction *SendSmsGsmModemAction::clone()
{
    SendSmsGsmModemAction *result = new SendSmsGsmModemAction();
    copyProperties(result);
    result->setDestPhone(a_DestPhone);
    result->setMsgClass(a_MsgClass);
    result->setMsgTemplate(a_MsgTemplate);
    return result;
}

/******************************************************************/

} // namespace SDPO
