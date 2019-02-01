#include "tSqlQueryAction.h"
#include "global/gMacroTranslator.h"
#include "tTest.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace SDPO {

/******************************************************************/

SqlQueryAction::SqlQueryAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::SqlQuery);
}

/******************************************************************/

void SqlQueryAction::run(TTest *test)
{
    QSqlDatabase db = QSqlDatabase::database("actOdbcQuery");
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QODBC", "actOdbcQuery");
    }
    db.setDatabaseName(a_OdbcDataSource);
    db.setUserName(a_Login);
    db.setPassword(a_Password);
    bool ok = db.open();
    if (!ok) {
        return;
    }
    GMacroTranslator translator(a_SqlQuery, test);
    QString sqlScript = translator.translate();
    QSqlQuery query(db);
    bool result = query.exec(sqlScript);
    if (!result) {
        qDebug() << "SQL query action:" + query.lastError().text();
    }
    db.close();
}

/******************************************************************/

QStringList SqlQueryAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("ODBC Source: %1").arg(a_OdbcDataSource));
    result.append(QString("Login: %1").arg(a_Login));
    result.append(QString("SQL query: %1").arg(a_SqlQuery));
    result.append(QString("Timeout: %1").arg(a_Timeout));
    return result;
}

/******************************************************************/

TestAction *SqlQueryAction::clone()
{
    SqlQueryAction *result = new SqlQueryAction();
    copyProperties(result);
    result->setOdbcDataSource(a_OdbcDataSource);
    result->setLogin(a_Login);
    result->setPassword(a_Password);
    result->setSqlQuery(a_SqlQuery);
    result->setTimeout(a_Timeout);
    return result;
}

/******************************************************************/

} //namespace SDPO
