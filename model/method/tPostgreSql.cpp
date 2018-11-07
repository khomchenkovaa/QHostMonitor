#include "tPostgreSql.h"

#include <QSqlDatabase>
#include <QSqlError>

namespace SDPO {

/******************************************************************/

TPostgreSql::TPostgreSql(QObject *parent) :
    TTestMethod(TMethodID::Postgre, parent)
{
    a_Port = POSTGRESQL_DEFAULT_PORT;
}

/******************************************************************/

QString TPostgreSql::getTestMethod() const
{
    return QString("PostgreSQL test");
}

/******************************************************************/

QString TPostgreSql::getTestedObjectInfo() const
{
    return QString("PostgreSQL database %1 on %2:%3").arg(a_Database).arg(a_Host).arg(a_Port);
}

/******************************************************************/

void TPostgreSql::run()
{
    TTestResult result;
    result.reply = "No driver";

    if (QSqlDatabase::isDriverAvailable("QPSQL")) {
        QSqlDatabase db = QSqlDatabase::database("testPostgreSQL");
        if (!db.isValid()) {
            db = QSqlDatabase::addDatabase("QPSQL", "testPostgreSQL");
        }
        db.setHostName(a_Host);
        db.setPort(a_Port);
        db.setDatabaseName(a_Database);
        db.setUserName(a_Login);
        db.setPassword(a_Password);
        bool ok = db.open();
        if (!ok) {
            result.error = db.lastError().text();
            result.status = TestStatus::Bad;
            result.reply = db.lastError().text();
        } else {
            result.status = TestStatus::Ok;
            result.reply = "Connected";
            db.close();
        }
    }
    m_Result = result;

    emit testSuccess();
}

TTestMethod *TPostgreSql::clone()
{
    TPostgreSql *result = new TPostgreSql(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Host = a_Host;
    result->a_Port = a_Port;
    result->a_Database = a_Database;
    result->a_Login = a_Login;
    result->a_Password = a_Password;
    return result;
}

/******************************************************************/

} // namespace SDPO
