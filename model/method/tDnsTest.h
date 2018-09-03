#ifndef TDNSTEST_H
#define TDNSTEST_H

#include "tTestMethod.h"

namespace SDPO {

class TDnsTest : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getServer())
    Q_PROPERTY(QString TestMode READ  getRequestType())

    AUTO_PROPERTY(QString, Server)
    AUTO_PROPERTY(int, TimeOut)
    AUTO_PROPERTY(QString, Protocol)
    AUTO_PROPERTY(int, Port)
    AUTO_PROPERTY(QString, Request)
    AUTO_PROPERTY(QString, RequestType)
    BOOL_PROPERTY(TestResultFor)
    AUTO_PROPERTY(QString, TestResult)

public:
    explicit TDnsTest(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

signals:

public slots:

};

} // namespace SDPO

#endif // TDNSTEST_H
