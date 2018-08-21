#include "tSendMessageToPagerSnppAction.h"

namespace SDPO {

/******************************************************************/

SendMessageToPagerSnppAction::SendMessageToPagerSnppAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::MsgPagerSnpp);
    a_Port = 444;
    b_Alert = false;
    b_LoginAs = false;
    a_Level = "Normal";
}

/******************************************************************/

void SendMessageToPagerSnppAction::run(TTest *test)
{
    Q_UNUSED(test)
     // Do nothig
}

/******************************************************************/

QStringList SendMessageToPagerSnppAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Server: %1").arg(a_Server));
    result.append(QString("Port: %1").arg(a_Port));
    result.append(QString("Login: %1").arg(b_LoginAs?"Yes":"No"));
    if (b_LoginAs) {
       result.append(QString("Login id: %1").arg(a_LoginAsLogin));
        }
    result.append(QString("Mail templates: %1").arg(a_MailTemplate));
    result.append(QString("Level: %1").arg(a_Level));
    result.append(QString("AleUrt: %1").arg(b_Alert?"Yes":"No"));
    return result;
}

/******************************************************************/

TestAction *SendMessageToPagerSnppAction::clone()
{
    SendMessageToPagerSnppAction *result = new SendMessageToPagerSnppAction();
    copyProperties(result);
    result->setPagerID(a_PagerID);
    result->setMailTemplate(a_MailTemplate);
    result->setLevel(a_Level);
    result->setAlert(b_Alert);
    result->setServer(a_Server);
    result->setPort(a_Port);
    result->setLoginAs(b_LoginAs);
    result->setLoginAsLogin(a_LoginAsLogin);
    result->setLoginAsPassword(a_LoginAsPassword);
    return result;
}

/******************************************************************/

} //namespace SDPO
