#ifndef TODBCQUERY_H
#define TODBCQUERY_H

#include "tTestMethod.h"

namespace SDPO {

class TOdbcQuery : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Path READ getSqlQuery)
    Q_PROPERTY(QString Object READ getDataSource())

    AUTO_PROPERTY(QString, DataSource)
    AUTO_PROPERTY(QString, Login)
    AUTO_PROPERTY(QString, Password)
    BOOL_PROPERTY(ExecuteQuery)
    AUTO_PROPERTY(QString, SqlQuery)
    BOOL_PROPERTY(TestAlert)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(int, AlertRow)
    AUTO_PROPERTY(int, AlertCol)
    AUTO_PROPERTY(int, CriteriaMode)
    AUTO_PROPERTY(QString, CriteriaValue)
    AUTO_PROPERTY(QString, UnavailableStatus)

public:
    explicit TOdbcQuery(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // TODBCQUERY_H
