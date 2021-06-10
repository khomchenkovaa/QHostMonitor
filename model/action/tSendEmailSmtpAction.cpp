#include "tSendEmailSmtpAction.h"

#include "global/gMacroTranslator.h"
#include "settings.h"

#include "qxtsmtp.h"

#include <QFileInfo>

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
    GMacroTranslator translator(a_BodyTemplate, test);
    QString body = translator.translate();

    QSettings s;
    int tlsIdx = s.value(SKEY_SMTP_SslType1,0).toInt();
    int authIdx = s.value(SKEY_SMTP_Auth1,0).toInt();
    QString serverName = s.value(SKEY_SMTP_Server1,"smtp.mail.yahoo.com").toString();
    quint16 defaultPort = tlsIdx? 465 : 25;
    quint16 serverPort = static_cast<quint16>(s.value(SKEY_SMTP_Port1,defaultPort).toInt());
    QString userName = s.value(SKEY_SMTP_User1).toString();
    QString password = s.value(SKEY_SMTP_Pswd1).toString();

    QxtSmtp smtp;
    switch(authIdx) {
    case 1:
        smtp.setAuthMethodEnabled(QxtSmtp::AuthPlain, true);
        break;
    case 2:
        smtp.setAuthMethodEnabled(QxtSmtp::AuthLogin, true);
        break;
    case 3:
        smtp.setAuthMethodEnabled(QxtSmtp::AuthCramMD5, true);
        break;
    default:
        break;
    }

    if (tlsIdx) {
        smtp.connectToSecureHost(serverName, serverPort);
    } else {
        smtp.connectToHost(serverName, serverPort);
    }
    if (authIdx) {
        smtp.setUsername(userName.toLocal8Bit());
        smtp.setPassword(password.toLocal8Bit());
    }

    // TODO SendEmailSmtpAction::run Test implementation and use backup settings

    QxtMailMessage message;
    message.setSender(a_FromSender);
    message.addRecipient(a_ToRecipients);
    message.setSubject(a_Subject);
    message.setBody(body);
    message.setExtraHeader("Priority", a_Priority);
    if (b_AttachFile && !a_AttachedFileName.isEmpty()) {
        QString fileName = QFileInfo(a_AttachedFileName).fileName();
        QxtMailAttachment attachement = QxtMailAttachment::fromFile(a_AttachedFileName);
        message.addAttachment(fileName, attachement);
    }
    smtp.send(message);
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
    result->setAttachedFileName(a_AttachedFileName);
    return result;
}

/******************************************************************/

} // namespace SDPO
