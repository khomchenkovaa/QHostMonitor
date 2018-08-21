#ifndef TSENDMESSAGETOICQACTION_H
#define TSENDMESSAGETOICQACTION_H

#include "tTestAction.h"

namespace SDPO {

class SendMessageToIcqAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, SendMessage) // Send message to ICQ (UIN)
    AUTO_PROPERTY(QString, MsgTemplate) // Message template

public:
    explicit SendMessageToIcqAction(QObject *parent = 0);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TSENDMESSAGETOICQACTION_H
