#ifndef TNTEVENTLOG_H
#define TNTEVENTLOG_H

#include "testmethod.h"

namespace SDPO {

class TNtEventLog : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getComputerUnc())
    Q_PROPERTY(QString Path READ  getLog())
    Q_PROPERTY(QString Object READ  getEventSource())

    BOOL_PROPERTY(LogSource)
    BOOL_PROPERTY(AlertCondition)
    BOOL_PROPERTY(ConnectAs)
    AUTO_PROPERTY(QString, Compatibility)
    AUTO_PROPERTY(QString, ComputerUnc)
    AUTO_PROPERTY(QString, Log)
    AUTO_PROPERTY(QString, EventSource)
    AUTO_PROPERTY(QString, Computer)
    AUTO_PROPERTY(QString, EventType)
    AUTO_PROPERTY(QString, EventId)
    AUTO_PROPERTY(QString, Description)
    BOOL_PROPERTY(ConnectToRemote)
    AUTO_PROPERTY(QString, Login)
    AUTO_PROPERTY(QString, Password)

public:
    explicit TNtEventLog(QObject *parent = 0);


    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual TestMethod *clone() Q_DECL_OVERRIDE;

signals:

public slots:

};

} // namespace SDPO

#endif // TNTEVENTLOG_H
