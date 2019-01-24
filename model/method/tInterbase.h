#ifndef TINTERBASE_H
#define TINTERBASE_H

#include "tTestMethod.h"

namespace SDPO {

class TInterbase : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Object READ getDatabase())

    AUTO_PROPERTY(QString, Host)
    AUTO_PROPERTY(QString, Database)
    AUTO_PROPERTY(QString, Login)
    AUTO_PROPERTY(QString, Password)
    AUTO_PROPERTY(QString, Protocol)

public:
    explicit TInterbase(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // TINTERBASE_H
