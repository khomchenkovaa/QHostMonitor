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
    QString newReply = "No driver";
    float newReplyFloat = 0.0;
    int newReplyInt = 0;
    TestStatus newStatus = TestStatus::Unknown;

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
            m_ErrorString = db.lastError().text();
            newStatus = TestStatus::Bad;
            newReply = db.lastError().text();
        } else {
            newStatus = TestStatus::Ok;
            newReply = "Connected";
            db.close();
        }
    }
    m_Status = newStatus;
    m_Reply = newReply;
    m_ReplyDouble = newReplyFloat;
    m_ReplyInt = newReplyInt;

    emit testSuccess();
}

TTestMethod *TPostgreSql::clone()
{
    TPostgreSql *result = new TPostgreSql(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
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
