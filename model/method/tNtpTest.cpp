#include "tNtpTest.h"

namespace SDPO {

TNtpTest::TNtpTest(QObject *parent) :
    TTestMethod(TMethodID::NTP, parent)
{
    a_Server = QString("");
    a_Port = 123;
    a_Retries = 3;
    a_Timeout = 5;
    b_AlertWhen = false;
    a_Sec = 10;
    a_DisplayMode = QString("Reply time");

}

/******************************l************************************/

void TNtpTest::run()
{
    m_Status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TNtpTest::clone()
{
    TNtpTest *result = new TNtpTest(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
    // test specific
    result->a_Server = a_Server;
    result->a_Port = a_Port;
    result->a_Retries = a_Retries;
    result->a_Timeout = a_Timeout;
    result->b_AlertWhen = b_AlertWhen;
    result->a_Sec = a_Sec;
    result->a_DisplayMode = a_DisplayMode;
    return result;
}

/******************************************************************/

QString TNtpTest::getTestMethod() const
{
    return QString("NTP: %1").arg(a_Server);
}

/******************************************************************/

QString TNtpTest::getTestedObjectInfo() const
{
    return QString("NTP test (%1)").arg(a_Server);
}

/******************************************************************/

} // namespace SDPO
