#ifndef TSENDEMAILSMTPACTION_H
#define TSENDEMAILSMTPACTION_H

#include "tTestAction.h"

namespace SDPO {

class SendEmailSmtpAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, FromSender) // From (sender)
    AUTO_PROPERTY(QString, ToRecipients) // To (recipients)
    AUTO_PROPERTY(QString, Priority) // (RFC 2156) Priority = "normal" / "non-urgent" / "urgent"
    AUTO_PROPERTY(QString, Subject) // Subject
    AUTO_PROPERTY(QString, BodyTemplate) // Body template
    BOOL_PROPERTY(AttachFile) // Attach file
    AUTO_PROPERTY(QString, AttachedFileName) //Attached File Name

public:
    explicit SendEmailSmtpAction(QObject *parent = nullptr);
    virtual ~SendEmailSmtpAction() {}

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

};

} // namespace SDPO

#endif // TSENDEMAILSMTPACTION_H
