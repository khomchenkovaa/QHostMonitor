#ifndef TLOGEVENTACTION_H
#define TLOGEVENTACTION_H

#include "tTestAction.h"

namespace SDPO {
class LogEventAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, Computer) // Computer
    AUTO_PROPERTY(QString, Log) // Log
    AUTO_PROPERTY(QString, EventType) // EventType
    AUTO_PROPERTY(QString, EventSource) // EventSource
    AUTO_PROPERTY(int, EventId) // EventId
    AUTO_PROPERTY(QString, Description) // Description
    BOOL_PROPERTY(ConnectAs) // ConnectAs
    AUTO_PROPERTY(QString, Login) // Login
    AUTO_PROPERTY(QString, Password) // Password

public:
    explicit LogEventAction(QObject *parent = nullptr);
    virtual ~LogEventAction() {}

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} //namespace SDPO

#endif // TLOGEVENTACTION_H
