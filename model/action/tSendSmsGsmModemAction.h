#ifndef TSENDSMSGSMMODEMACTION_H
#define TSENDSMSGSMMODEMACTION_H

#include "tTestAction.h"

namespace SDPO {

class SendSmsGsmModemAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, DestPhone) // Dest. phone
    AUTO_PROPERTY(QString, MsgClass) // Msg. class
    AUTO_PROPERTY(QString, MsgTemplate) // Msg. template

public:
    explicit SendSmsGsmModemAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TSENDSMSGSMMODEMACTION_H
