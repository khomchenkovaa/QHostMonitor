#include "tOdbcQuery.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

namespace SDPO {

/******************************************************************/

TOdbcQuery::TOdbcQuery(QObject *parent) :
    TTestMethod(TMethodID::ODBC, parent)
{
    b_ExecuteQuery = false;
    b_TestAlert = false;
    a_AlertRow = 1;
    a_AlertCol = 1;
    a_CriteriaMode = 0;
}

/******************************************************************/

QString TOdbcQuery::getTestMethod() const
{
    return QString("ODBC test");
}

/******************************************************************/

QString TOdbcQuery::getTestedObjectInfo() const
{
    return QString("ODBC %1 test").arg(a_DataSource);
}

/******************************************************************/

void TOdbcQuery::run()
{
    QString newReply = "No answer";
    float newReplyFloat = 0.0;
    int newReplyInt = 0;
    TestStatus newStatus = TestStatus::Unknown;

    QSqlDatabase db = QSqlDatabase::database("testOdbcQuery");
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QODBC", "testOdbcQuery");
    }
    db.setDatabaseName(a_DataSource);
    db.setUserName(a_Login);
    db.setPassword(a_Password);
    bool ok = db.open();
    if (!ok) {
        m_ErrorString = db.lastError().text();
        newStatus = TestStatus::Bad;
        newReply = db.lastError().text();
    } else {
        if (b_ExecuteQuery) {
            QSqlQuery query(db);
            bool result = query.exec(a_SqlQuery);
            if (result) {
                if (b_TestAlert) {
                    if (query.seek(a_AlertRow-1)) {
                        QVariant value = query.value(a_AlertCol-1);
                        if (value.isValid()) {
                            switch (a_CriteriaMode) {
                            case 0: // is < than
                                newStatus = (value.toInt() < a_CriteriaValue.toInt()) ? TestStatus::Bad : TestStatus::Ok;
                                break;
                            case 1: // is > than
                                newStatus = (value.toInt() > a_CriteriaValue.toInt()) ? TestStatus::Bad : TestStatus::Ok;
                                break;
                            case 2: // is = to
                                newStatus = (value.toString() == a_CriteriaValue) ? TestStatus::Bad : TestStatus::Ok;
                                break;
                            case 3: // is <> from
                                newStatus = (value.toString() != a_CriteriaValue) ? TestStatus::Bad : TestStatus::Ok;
                                break;
                            case 4: // containts
                                newStatus = (value.toString().contains(a_CriteriaValue)) ? TestStatus::Bad : TestStatus::Ok;
                                break;
                            case 5: // does not contain
                                newStatus = (value.toString().contains(a_CriteriaValue)) ? TestStatus::Ok : TestStatus::Bad;
                                break;
                            }
                            newReply = value.toString();
                            newReplyInt = value.toInt();
                            newReplyFloat = value.toFloat();
                        } else {
                            newStatus = TEnums::testStatusFromString(a_UnavailableStatus);
                            newReply = "Unavailable";
                        }
                    } else {
                        newStatus = TEnums::testStatusFromString(a_UnavailableStatus);
                        newReply = "Unavailable";
                    }
                } else {
                    newStatus = TestStatus::Ok;
                    newReply = "Query OK";
                }
            } else {
                newStatus = TestStatus::Bad;
                newReply = query.lastError().text();
                m_ErrorString = query.lastError().text();
            }
        } else {
            newStatus = TestStatus::Ok;
            newReply = "Connected";
        }
        db.close();
    }
    m_Status = newStatus;
    m_Reply = newReply;
    m_ReplyDouble = newReplyFloat;
    m_ReplyInt = newReplyInt;

    emit testSuccess();
}

/******************************************************************/

TTestMethod *TOdbcQuery::clone()
{
    TOdbcQuery *result = new TOdbcQuery(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
    // test specific
    result->a_DataSource = a_DataSource;
    result->a_Login = a_Login;
    result->a_Password = a_Password;
    result->b_ExecuteQuery = b_ExecuteQuery;
    result->a_SqlQuery = a_SqlQuery;
    result->b_TestAlert = b_TestAlert;
    result->a_AlertRow = a_AlertRow;
    result->a_AlertCol = a_AlertCol;
    result->a_CriteriaMode = a_CriteriaMode;
    result->a_CriteriaValue = a_CriteriaValue;
    result->a_UnavailableStatus = a_UnavailableStatus;
    return result;
}

/******************************************************************/

} // namespace SDPO
