#ifndef TDISCONNECTDIALUPCONNECTIONACTION_H
#define TDISCONNECTDIALUPCONNECTIONACTION_H

#include "tTestAction.h"

namespace SDPO {

class DisconnectDialupConnectionAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, DialUpConnection) // Dial-up connection

public:
    explicit DisconnectDialupConnectionAction(QObject *parent = nullptr);
    virtual ~DisconnectDialupConnectionAction() {}

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} //namespace SDPO

#endif // TDISCONNECTDIALUPCONNECTIONACTION_H
