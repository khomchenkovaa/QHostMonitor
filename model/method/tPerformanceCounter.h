#ifndef TPERFORMANCECOUNTER_H
#define TPERFORMANCECOUNTER_H

#include "testmethod.h"

namespace SDPO {

class TPerformanceCounter : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getHost())
    Q_PROPERTY(QString Path READ  getCheckCounter())
    Q_PROPERTY(QString Object READ  getCheckCounter())
    Q_PROPERTY(QString Object2 READ  getAlertWhenCounter())
    Q_PROPERTY(QString TestMode READ  getAlertWhen())

    AUTO_PROPERTY(QString, CheckCounter)
    AUTO_PROPERTY(QString, AlertWhen)
    AUTO_PROPERTY(int, AlertWhenCounter)
    AUTO_PROPERTY(QString, DisplayMode)
    BOOL_PROPERTY(ConnectAs)
    AUTO_PROPERTY(QString, Login)
    AUTO_PROPERTY(QString, Password)

public:
    explicit TPerformanceCounter(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getHost() const { return "localhost"; }

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual TestMethod *clone() Q_DECL_OVERRIDE;
signals:

public slots:

};

} // namespace SDPO

#endif // TPERFORMANCECOUNTER_H
