#ifndef TDIALUPTOTHENETWORKACTION_H
#define TDIALUPTOTHENETWORKACTION_H

#include "tTestAction.h"

namespace SDPO {

class DialupToTheNetworkAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, DialUpConnection) // Dial-up connection
    AUTO_PROPERTY(QString, UserName) // User name
    AUTO_PROPERTY(QString, Password) // Password
    BOOL_PROPERTY(SavePassword) // Save password
    BOOL_PROPERTY(ShowDialUpWindow) // Show dial-up window
    AUTO_PROPERTY(int, Retries) // Retries


public:
    explicit DialupToTheNetworkAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TDIALUPTOTHENETWORKACTION_H
