#include "tOracle.h"

#include <QSqlDatabase>
#include <QSqlError>

namespace SDPO {

/******************************************************************/

TOracle::TOracle(QObject *parent) :
    TestMethod(TMethodID::Oracle, parent)
{
}

/******************************************************************/

QString TOracle::getTestMethod() const
{
    return QString("Oracle test");
}

/******************************************************************/

QString TOracle::getTestedObjectInfo() const
{
    return QString("Oracle database %1").arg(a_Database);
}

/******************************************************************/

void TOracle::run()
{
    TestResult result;
    result.reply = "No driver";

    if (QSqlDatabase::isDriverAvailable("QOCI")) {
        QSqlDatabase db = QSqlDatabase::database("testOracle");
        if (!db.isValid()) {
            db = QSqlDatabase::addDatabase("QOCI", "testOracle");
        }
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

TestMethod *TOracle::clone()
{
    TOracle *result = new TOracle(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Database = a_Database;
    result->a_Login = a_Login;
    result->a_Password = a_Password;
    return result;
}

/******************************************************************/

} // namespace SDPO
