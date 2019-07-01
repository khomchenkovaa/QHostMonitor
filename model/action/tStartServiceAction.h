#ifndef TSTARTSERVICEACTION_H
#define TSTARTSERVICEACTION_H

#include "tTestAction.h"

namespace SDPO {

class StartServiceAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, StartServiceOn) // Start service on
    AUTO_PROPERTY(QString, ServiceName) // Service name
    AUTO_PROPERTY(QString, Parameters) // Parameters
    BOOL_PROPERTY(ConnectAs) // Connect as
    AUTO_PROPERTY(QString, ConnectAsLogin) // Login
    AUTO_PROPERTY(QString, ConnectAsPassword) // Password

public:
    explicit StartServiceAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

}// namespace SDPO

#endif // TSTARTSERVICEACTION_H
