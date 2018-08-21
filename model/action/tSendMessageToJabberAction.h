#ifndef TSENDMESSAGETOJABBERACTION_H
#define TSENDMESSAGETOJABBERACTION_H

#include "tTestAction.h"

namespace SDPO {
class SendMessageToJabberAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, SendMessage) // Send message to (Jabber account)
    AUTO_PROPERTY(QString, MsgTemplate) // Message template

public:
    explicit SendMessageToJabberAction(QObject *parent = 0);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TSENDMESSAGETOJABBERACTION_H
