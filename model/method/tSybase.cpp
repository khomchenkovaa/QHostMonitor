#include "tSybase.h"

#include <QSqlDatabase>
#include <QSqlError>

namespace SDPO {

/******************************************************************/

TSybase::TSybase(QObject *parent) :
    TTestMethod(TMethodID::Sybase, parent)
{
    a_Server = QString("");
    a_Database = QString("");
    a_Login = QString("");
    a_Password = QString("");
}

/******************************************************************/

QString TSybase::getTestMethod() const
{
    return QString("Sybase %1").arg(a_Server);
}

/******************************************************************/

QString TSybase::getTestedObjectInfo() const
{
    return QString("Check Sybase Adaptive Server (%1)").arg(a_Server);
}

/******************************************************************/

void TSybase::run()
{
    TTestResult result;
    result.reply = "No driver";

    if (QSqlDatabase::isDriverAvailable("QTDS")) {
        QSqlDatabase db = QSqlDatabase::database("testSybase");
        if (!db.isValid()) {
            db = QSqlDatabase::addDatabase("QTDS", "testSybase");
        }
        db.setHostName(a_Server);
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

/******************************************************************/

TTestMethod *TSybase::clone()
{
    TSybase *result = new TSybase(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Server = a_Server;
    result->a_Database = a_Database;
    result->a_Login = a_Login;
    result->a_Password = a_Password;
    return result;
}

/******************************************************************/

} // namespace SDPO
