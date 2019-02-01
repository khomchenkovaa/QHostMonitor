#ifndef TMYSQL_H
#define TMYSQL_H

#include "tTestMethod.h"

#define MYSQL_DEFAULT_PORT 3036

namespace SDPO {

class TMySql : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Object READ getDatabase())

    AUTO_PROPERTY(QString, Host)
    AUTO_PROPERTY(int, Port)
    AUTO_PROPERTY(QString, Database)
    AUTO_PROPERTY(QString, Login)
    AUTO_PROPERTY(QString, Password)

public:
    explicit TMySql(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // TMYSQL_H
