#include "tInterbase.h"

#include <QSqlDatabase>
#include <QSqlError>

namespace SDPO {

/******************************************************************/

TInterbase::TInterbase(QObject *parent) :
    TTestMethod(TMethodID::Interbase, parent)
{
    a_Protocol = "TCP";
}

/******************************************************************/

void TInterbase::run()
{
    QString newReply = "No driver";
    float newReplyFloat = 0.0;
    int newReplyInt = 0;
    TestStatus newStatus = TestStatus::Unknown;

    if (QSqlDatabase::isDriverAvailable("QIBASE")) {
        QSqlDatabase db = QSqlDatabase::database("testInterbase");
        if (!db.isValid()) {
            db = QSqlDatabase::addDatabase("QIBASE", "testInterbase");
        }
        db.setHostName(a_Host);
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

TTestMethod *TInterbase::clone()
{
    TInterbase *result = new TInterbase(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
    // test specific
    result->a_Host = a_Host;
    result->a_Protocol = a_Protocol;
    result->a_Database = a_Database;
    result->a_Login = a_Login;
    result->a_Password = a_Password;
    return result;
}

/******************************************************************/

QString TInterbase::getTestMethod() const
{
    return QString("Interbase test");
}

/******************************************************************/

QString TInterbase::getTestedObjectInfo() const
{
    return QString("Check Interbase server %1").arg(a_Database);
}

/******************************************************************/

} // namespace SDPO
