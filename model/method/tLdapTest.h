#ifndef TTLDAPTEST_H
#define TTLDAPTEST_H

#include "tTestMethod.h"

namespace SDPO {

class TLdapTest : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getHost())
    Q_PROPERTY(QString Object READ  getBaseObject())
    Q_PROPERTY(QString TargetPort READ  getPort())

    AUTO_PROPERTY(QString, Host)
    AUTO_PROPERTY(int, Port)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(QString, Login)
    AUTO_PROPERTY(QString, Password)
    BOOL_PROPERTY(CheckPerformSearch)
    AUTO_PROPERTY(QString, BaseObject)
    AUTO_PROPERTY(int, ResLimit)
    AUTO_PROPERTY(QString, SearchFilter)

public:
    explicit TLdapTest(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // getters and setters

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

signals:

public slots:

};

} // namespace SDPO

#endif // TTLDAPTEST_H
