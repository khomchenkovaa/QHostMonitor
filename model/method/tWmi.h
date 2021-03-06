#ifndef TWMI_H
#define TWMI_H

#include "testmethod.h"

namespace SDPO {

class TWmi : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Path READ  getQuery())
    Q_PROPERTY(QString Object READ  getQuery())
    Q_PROPERTY(QString Object2 READ  getAlertIfCount())
    Q_PROPERTY(QString TestMode READ  getAlertIfCompare())

    AUTO_PROPERTY(QString, Host)
    AUTO_PROPERTY(QString, NameSpace)
    AUTO_PROPERTY(QString, Query)
    AUTO_PROPERTY(QString, AlertIf)
    AUTO_PROPERTY(QString, AlertIfCompare)
    AUTO_PROPERTY(QString, AlertIfCount)
    AUTO_PROPERTY(QString, IfInstanChanged)

public:
    explicit TWmi(QObject *parent = nullptr);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual TestMethod *clone() Q_DECL_OVERRIDE;

signals:

public slots:

};

} //namespace SDPO

#endif // TWMI_H
