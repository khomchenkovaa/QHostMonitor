#include "tLdapTest.h"

namespace SDPO {

TLdapTest::TLdapTest(QObject *parent) :
    TestMethod(TMethodID::Ldap, parent)
{
    a_Host = QString("");
    a_Port = 389;
    a_Timeout = 60;
    a_Login = QString();
    a_Password = QString();
    b_CheckPerformSearch = false;
    a_BaseObject = QString();
    a_ResLimit = 0;
    a_SearchFilter = QString();
}

/******************************************************************/

void TLdapTest::run()
{
    m_Result.status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TestMethod *TLdapTest::clone()
{
    TLdapTest *result = new TLdapTest(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Host = a_Host;
    result->a_Port = a_Port;
    result->a_Timeout = a_Timeout;
    result->a_Login = a_Login;
    result->a_Password = a_Password;
    result->b_CheckPerformSearch = b_CheckPerformSearch;
    result->a_BaseObject = a_BaseObject;
    result->a_ResLimit = a_ResLimit;
    result->a_SearchFilter = a_SearchFilter;
    return result;
}

/******************************************************************/

QString TLdapTest::getTestMethod() const
{
    return QString("LDAP: %1").arg(a_Host);
}

/******************************************************************/

QString TLdapTest::getTestedObjectInfo() const
{
    return QString("LDAP test (%1)").arg(a_Host);
}

/******************************************************************/

} // namespace SDPO
