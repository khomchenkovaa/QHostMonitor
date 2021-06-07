#include "tPop3Test.h"

#include "qxtpop3.h"

#include <QSslSocket>

namespace SDPO {

TPop3Test::TPop3Test(QObject *parent) :
    TestMethod(TMethodID::POP3, parent)
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
    writeLogTitle();
    TTestResult result;
    QxtPop3 pop;
    pop.sslSocket()->setProtocol(QSsl::TlsV1_0);
    pop.sslSocket()->setPeerVerifyMode(QSslSocket::QueryPeer);
    pop.setUsername(a_Login.toLocal8Bit());
    pop.setPassword(a_Password.toLocal8Bit());
    if (a_TLS == "none") {
        pop.connectToHost(a_Server.toLocal8Bit(), a_Port);
    } else {
        pop.connectToSecureHost(a_Server.toLocal8Bit(), a_Port);
    }
    // TODO TPop3Test::run implementation
    m_Result.status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TestMethod *TPop3Test::clone()
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
