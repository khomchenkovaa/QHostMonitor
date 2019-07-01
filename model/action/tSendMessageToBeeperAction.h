#ifndef TSENDMESSAGETOBEEPERACTION_H
#define TSENDMESSAGETOBEEPERACTION_H

#include "tTestAction.h"

namespace SDPO {

class SendMessageToBeeperAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, Beeper) // Beeper
    AUTO_PROPERTY(int, Delay) // Delay
    AUTO_PROPERTY(QString, SendMessage) // Send Message
    AUTO_PROPERTY(QString, TerminationString) // Termination String

public:
    explicit SendMessageToBeeperAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TSENDMESSAGETOBEEPERACTION_H
