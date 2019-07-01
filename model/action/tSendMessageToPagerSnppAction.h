#ifndef TSENDMESSAGETOPAGERSNPPACTION_H
#define TSENDMESSAGETOPAGERSNPPACTION_H

#include "tTestAction.h"

namespace SDPO {

class SendMessageToPagerSnppAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, PagerID) // PagerID
    AUTO_PROPERTY(QString, MailTemplate) // MailTemplate
    AUTO_PROPERTY(QString, Level) // Level
    BOOL_PROPERTY(Alert) // Alert
    AUTO_PROPERTY(QString, Server) // Server
    AUTO_PROPERTY(int, Port) // Port
    BOOL_PROPERTY(LoginAs) // LoginAs
    AUTO_PROPERTY(QString, LoginAsLogin) // LoginAsLogin
    AUTO_PROPERTY(QString, LoginAsPassword) // LoginAsPassword

public:
    explicit SendMessageToPagerSnppAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

};

} // namespace SDPO

#endif // TSENDMESSAGETOPAGERSNPPACTION_H


