#include "tMsSql.h"

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
    m_Status = TestStatus::Ok;
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
    return QString("check MS SQL server (%1)").arg(a_Server);
}

/******************************************************************/

} // namespace SDPO
