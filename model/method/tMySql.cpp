#include "tMySql.h"

#include <QSqlDatabase>
#include <QSqlError>

namespace SDPO {

/******************************************************************/

TMySql::TMySql(QObject *parent) :
    TestMethod(TMethodID::MySQL, parent)
{
    a_Port = MYSQL_DEFAULT_PORT;
}

/******************************************************************/

QString TMySql::getTestMethod() const
{
    return QString("MySQL test");
}

/******************************************************************/

QString TMySql::getTestedObjectInfo() const
{
    return QString("MySQL database %1 on %2:%3").arg(a_Database).arg(a_Host).arg(a_Port);
}

/******************************************************************/

void TMySql::run()
{
    TestResult result;
    result.reply = "No driver";

    if (QSqlDatabase::isDriverAvailable("QMYSQL")) {
        QSqlDatabase db = QSqlDatabase::database("testMySQL");
        if (!db.isValid()) {
            db = QSqlDatabase::addDatabase("QMYSQL", "testMySQL");
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

TestMethod *TMySql::clone()
{
    TMySql *result = new TMySql(parent());
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
