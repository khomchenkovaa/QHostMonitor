#include "tSendEmailSmtpAction.h"

namespace SDPO {

/******************************************************************/

SendEmailSmtpAction::SendEmailSmtpAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::MsgEmail);
    a_Priority = "Priority: Normal";
    a_Subject = "%LastTestTime%%StatusID%";
    b_AttachFile = false;
}

/******************************************************************/

void SendEmailSmtpAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Do nothing
}

/******************************************************************/

QStringList SendEmailSmtpAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("From: %1").arg(a_FromSender));
    result.append(QString("To: %1").arg(a_ToRecipients));
    result.append(QString("Subj: %1").arg(a_Subject));
    result.append(QString("Mail template: %1").arg(a_BodyTemplate));
    return result;
}

/******************************************************************/

TestAction *SendEmailSmtpAction::clone()
{
    SendEmailSmtpAction *result = new SendEmailSmtpAction();
    copyProperties(result);
    result->setFromSender(a_FromSender);
    result->setToRecipients(a_ToRecipients);
    result->setPriority(a_Priority);
    result->setSubject(a_Subject);
    result->setBodyTemplate(a_BodyTemplate);
    result->setAttachFile(b_AttachFile);
    result->setAttachFileSelect(a_AttachFileSelect);
    return result;
}

/******************************************************************/

} // namespace SDPO
