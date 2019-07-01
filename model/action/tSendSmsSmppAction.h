#ifndef TSENDSMSSMPPACTION_H
#define TSENDSMSSMPPACTION_H

#include "tTestAction.h"

namespace SDPO {

class SendSmsSmppAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, DestPhone) // Destination phone (number)
    AUTO_PROPERTY(QString, DestTon) // Destination TON
    AUTO_PROPERTY(QString, DestNpi) // Destination NPI
    AUTO_PROPERTY(QString, MsgTemplate) // Message template

public:
    explicit SendSmsSmppAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} //namespace SDPO

#endif // TSENDSMSSMPPACTION_H
