#ifndef TPOP3TEST_H
#define TPOP3TEST_H

#include "tTestMethod.h"

namespace SDPO {

class TPop3Test : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getServer())
    Q_PROPERTY(QString Object READ  getLogin())
    Q_PROPERTY(QString TargetPort READ  getPort())

    AUTO_PROPERTY(QString, Server)
    AUTO_PROPERTY(int, Port)
    AUTO_PROPERTY(QString, Login)
    AUTO_PROPERTY(QString, TLS)
    AUTO_PROPERTY(QString, Password)
    AUTO_PROPERTY(int, Timeout)
    BOOL_PROPERTY(AlertMessage)
    AUTO_PROPERTY(int, Messages)
    BOOL_PROPERTY(AlertSize)
    AUTO_PROPERTY(int, Size)

public:
    explicit TPop3Test(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getHost() const { return "localhost"; }

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual TTestMethod *clone() Q_DECL_OVERRIDE;
signals:

public slots:

};

} // namespace SDPO

#endif // TPOP3TEST_H
