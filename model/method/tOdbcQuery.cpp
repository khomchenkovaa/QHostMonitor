#include "tOdbcQuery.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

namespace SDPO {

/******************************************************************/

TOdbcQuery::TOdbcQuery(QObject *parent) :
    TestMethod(TMethodID::ODBC, parent)
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
    TestResult result;
    result.reply = "No answer";

    QSqlDatabase db = QSqlDatabase::database("testOdbcQuery");
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QODBC", "testOdbcQuery");
    }
    db.setDatabaseName(a_DataSource);
    db.setUserName(a_Login);
    db.setPassword(a_Password);
    bool ok = db.open();
    if (!ok) {
        result.error = db.lastError().text();
        result.status = TestStatus::Bad;
        result.reply = db.lastError().text();
    } else {
        if (b_ExecuteQuery) {
            QSqlQuery query(db);
            bool queryOk = query.exec(a_SqlQuery);
            if (queryOk) {
                if (b_TestAlert) {
                    if (query.seek(a_AlertRow-1)) {
                        QVariant value = query.value(a_AlertCol-1);
                        if (value.isValid()) {
                            switch (a_CriteriaMode) {
                            case 0: // is < than
                                result.status = (value.toInt() < a_CriteriaValue.toInt()) ? TestStatus::Bad : TestStatus::Ok;
                                break;
                            case 1: // is > than
                                result.status = (value.toInt() > a_CriteriaValue.toInt()) ? TestStatus::Bad : TestStatus::Ok;
                                break;
                            case 2: // is = to
                                result.status = (value.toString() == a_CriteriaValue) ? TestStatus::Bad : TestStatus::Ok;
                                break;
                            case 3: // is <> from
                                result.status = (value.toString() != a_CriteriaValue) ? TestStatus::Bad : TestStatus::Ok;
                                break;
                            case 4: // containts
                                result.status = (value.toString().contains(a_CriteriaValue)) ? TestStatus::Bad : TestStatus::Ok;
                                break;
                            case 5: // does not contain
                                result.status = (value.toString().contains(a_CriteriaValue)) ? TestStatus::Ok : TestStatus::Bad;
                                break;
                            }
                            result.reply = value.toString();
                            result.replyInt = value.toInt();
                            result.replyDouble = value.toFloat();
                        } else {
                            result.status = TEnums::testStatusFromString(a_UnavailableStatus);
                            result.reply = "Unavailable";
                        }
                    } else {
                        result.status = TEnums::testStatusFromString(a_UnavailableStatus);
                        result.reply = "Unavailable";
                    }
                } else {
                    result.status = TestStatus::Ok;
                    result.reply = "Query OK";
                }
            } else {
                result.status = TestStatus::Bad;
                result.reply = query.lastError().text();
                result.error = query.lastError().text();
            }
        } else {
            result.status = TestStatus::Ok;
            result.reply = "Connected";
        }
        db.close();
    }
    m_Result = result;

    emit testSuccess();
}

/******************************************************************/

TestMethod *TOdbcQuery::clone()
{
    TOdbcQuery *result = new TOdbcQuery(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
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
