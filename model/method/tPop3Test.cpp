#include "tPop3Test.h"

namespace SDPO {

TPop3Test::TPop3Test(QObject *parent) :
    TTestMethod(TMethodID::POP3, parent)
{
    a_Server = QString();
    a_Port = 110;
    a_Login = QString("");
    a_TLS = QString("none");
    a_Password = QString("");
    a_Timeout = 60;
    b_AlertMessage = false;
    a_Messages = 100;
    b_AlertSize = false;
    a_Size = 50;
}

/******************************************************************/

void TPop3Test::run()
{
    m_Result.status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TPop3Test::clone()
{
    TPop3Test *result = new TPop3Test(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Server = a_Server;
    result->a_Port = a_Port;
    result->a_Login = a_Login;
    result->a_TLS = a_TLS;
    result->a_Password = a_Password;
    result->a_Timeout = a_Timeout;
    result->b_AlertMessage = b_AlertMessage;
    result->a_Messages = a_Messages;
    result->b_AlertSize = b_AlertSize;
    result->a_Size = a_Size;
    return result;
}

/******************************************************************/

QString TPop3Test::getTestMethod() const
{
    return QString("POP3: %1").arg(a_Server);
}

/******************************************************************/

QString TPop3Test::getTestedObjectInfo() const
{
    return QString("POP3 test (%1)").arg(a_Server);
}

/******************************************************************/

} // namespace SDPO
