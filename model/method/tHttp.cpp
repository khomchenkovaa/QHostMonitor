#include "tHttp.h"

namespace SDPO {

THttp::THttp(QObject *parent) :
    TestMethod(TMethodID::HTTP, parent)
{
    a_Proxy = QString("<none>");
    a_Url = QString();
    a_Request = QString("HEADER");
    b_FollowRedirect = false;
    a_Timeout = 0; // Count all files
}

/******************************************************************/

void THttp::run()
{
    m_Result.status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TestMethod *THttp::clone()
{
    THttp *result = new THttp(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Proxy = a_Proxy;
    result->a_Url = a_Url;
    result->a_Request = a_Request;
    result->b_FollowRedirect = b_FollowRedirect;
    result->a_Timeout = a_Timeout;
    return result;
}

/******************************************************************/

QString THttp::getTestMethod() const
{
    return QString("HTTP: %1").arg(a_Url);
}

/******************************************************************/

QString THttp::getTestedObjectInfo() const
{
    return QString("HTTP test (%1)").arg(a_Url);
}

/******************************************************************/


} // namespace SDPO
