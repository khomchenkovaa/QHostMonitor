#ifndef TNTPTEST_H
#define TNTPTEST_H

#include "tTestMethod.h"

namespace SDPO {

class TNtpTest : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getServer())
    Q_PROPERTY(QString TargetPort READ  getPort())

    AUTO_PROPERTY(QString, Server)
    AUTO_PROPERTY(int, Port)
    AUTO_PROPERTY(int, Retries)
    AUTO_PROPERTY(int, Timeout)
    BOOL_PROPERTY(AlertWhen)
    AUTO_PROPERTY(int, Sec)
    AUTO_PROPERTY(QString, DisplayMode)

public:
    explicit TNtpTest(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

signals:

public slots:

};

} //namespace SDPO

#endif // TNTPTEST_H
