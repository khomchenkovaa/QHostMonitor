#ifndef TSQLQUERYACTION_H
#define TSQLQUERYACTION_H

#include "tTestAction.h"

namespace SDPO {

class SqlQueryAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, OdbcDataSource) // ODBC data source
    AUTO_PROPERTY(QString, Login) // Login
    AUTO_PROPERTY(QString, Password) // Password
    AUTO_PROPERTY(QString, SqlQuery) // Log
    AUTO_PROPERTY(int, Timeout) // Timeout

public:
    explicit SqlQueryAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TSQLQUERYACTION_H
