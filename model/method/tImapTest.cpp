#include "tImapTest.h"

namespace SDPO {

/******************************************************************/

TImapTest::TImapTest(QObject *parent) :
    TTestMethod(TMethodID::IMAP, parent)
{
    a_Server = QString("");
    a_Port = 143;
    a_Login = QString("");
    a_Tls = QString("none");
    a_Password = QString();
    a_Timeout = 60;
    b_CheckMailbox = false;
    a_MessageFolder = QString("Inbox");
    a_MessageStatus = QString("All message");
    a_MessageAlert = QString("Allert when size of all messages bigger than");
    a_MessageSize = 0;
}

/******************************************************************/

void TImapTest::run()
{
    m_Status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TImapTest::clone()
{
    TImapTest *result = new TImapTest(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
    // test specific
    result->a_Server = a_Server;
    result->a_Port = a_Port;
    result->a_Login = a_Login;
    result->a_Tls = a_Tls;
    result->a_Password = a_Password;
    result->a_Timeout = a_Timeout;
    result->b_CheckMailbox = b_CheckMailbox;
    result->a_MessageFolder = a_MessageFolder;
    result->a_MessageStatus = a_MessageStatus;
    result->a_MessageAlert = a_MessageAlert;
    result->a_MessageSize = a_MessageSize;
    return result;
}

/******************************************************************/

QString TImapTest::getTestMethod() const
{
    return QString("IMAP: %1").arg(a_Server);
}

/******************************************************************/

QString TImapTest::getTestedObjectInfo() const
{
    return QString("IMAP test (%1)").arg(a_Server);
}

/******************************************************************/

} // namespace SDPO
