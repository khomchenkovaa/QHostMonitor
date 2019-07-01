#ifndef TSTOPSERVICEACTION_H
#define TSTOPSERVICEACTION_H

#include "tTestAction.h"

namespace SDPO {

class StopServiceAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, StopServiceOn) // Stop service on
    AUTO_PROPERTY(QString, ServiceName) // Service name
    AUTO_PROPERTY(QString, Parameters) // Parameters
    BOOL_PROPERTY(ConnectAs) // Connect as
    AUTO_PROPERTY(QString, ConnectAsLogin) // Login
    AUTO_PROPERTY(QString, ConnectAsPassword) // Password

public:
    explicit StopServiceAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} //namespace SDPO

#endif // TSTOPSERVICEACTION_H
