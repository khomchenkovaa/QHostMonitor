#include "tOracle.h"

#include <QSqlDatabase>
#include <QSqlError>

namespace SDPO {

/******************************************************************/

TOracle::TOracle(QObject *parent) :
    TTestMethod(TMethodID::Oracle, parent)
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
    QString newReply = "No driver";
    float newReplyFloat = 0.0;
    int newReplyInt = 0;
    TestStatus newStatus = TestStatus::Unknown;

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

TTestMethod *TOracle::clone()
{
    TOracle *result = new TOracle(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
    // test specific
    result->a_Database = a_Database;
    result->a_Login = a_Login;
    result->a_Password = a_Password;
    return result;
}

/******************************************************************/

} // namespace SDPO
