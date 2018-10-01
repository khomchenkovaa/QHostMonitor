#include "tMsSql.h"

#include <QSqlDatabase>
#include <QSqlError>

namespace SDPO {

/******************************************************************/

TMsSql::TMsSql(QObject *parent) :
    TTestMethod(TMethodID::MSSQL, parent)
{
    a_Server = QString("");
    a_Database = QString("");
    a_Login = QString("");
    a_Password = QString("");
}

/******************************************************************/

void TMsSql::run()
{
    QString newReply = "No driver";
    float newReplyFloat = 0.0;
    int newReplyInt = 0;
    TestStatus newStatus = TestStatus::Unknown;

    if (QSqlDatabase::isDriverAvailable("QODBC")) {
        QSqlDatabase db = QSqlDatabase::database("testMsSQL");
        if (!db.isValid()) {
            db = QSqlDatabase::addDatabase("QODBC", "testMsSQL");
            db.setConnectOptions("SQL_ATTR_ODBC_VERSION=SQL_OV_ODBC3");
        }
        QString odbcDriver = "SQL Server"; // 2005
//        QString odbcDriver = "SQL Server Native Client 10.0"; // 2008
//        QString odbcDriver = "SQL Server Native Client 11.0"; // 2012

        QString dbName = QString("DRIVER={%1};SERVER=%2;DATABASE=%3;UID=%4;Port=1433;PWD=%5;WSID=.")
                .arg(odbcDriver).arg(a_Server).arg(a_Login).arg(a_Password);
        db.setDatabaseName(dbName);
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

/******************************************************************/

TTestMethod *TMsSql::clone()
{
    TMsSql *result = new TMsSql(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
    // test specific
    result->a_Server = a_Server;
    result->a_Database = a_Database;
    result->a_Login = a_Login;
    result->a_Password = a_Password;
    return result;
}

/******************************************************************/

QString TMsSql::getTestMethod() const
{
    return QString("MS SQL %1").arg(a_Server);
}

/******************************************************************/

QString TMsSql::getTestedObjectInfo() const
{
    return QString("Check MS SQL server (%1)").arg(a_Server);
}

/******************************************************************/

} // namespace SDPO
