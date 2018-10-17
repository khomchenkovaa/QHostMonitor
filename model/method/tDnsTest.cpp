#include "tDnsTest.h"

namespace SDPO {

/******************************************************************/

TDnsTest::TDnsTest(QObject *parent) :
    TTestMethod(TMethodID::DNS, parent)
{
    a_Server = QString();
    a_TimeOut = 50;
    a_Protocol = QString("UDP");
    a_Port = 50;
    a_Request = QString();
    a_RequestType = QString("A");
    b_TestResultFor = false;
    a_TestResult = QString();
}

/******************************************************************/

void TDnsTest::run()
{
    m_Result.status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TDnsTest::clone()
{
    TDnsTest *result = new TDnsTest(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Server = a_Server;
    result->a_TimeOut = a_TimeOut;
    result->a_Protocol = a_Protocol;
    result->a_Port = a_Port;
    result->a_Request = a_Request;
    result->a_RequestType = a_RequestType;
    result->b_TestResultFor = b_TestResultFor;
    result->a_TestResult = a_TestResult;
    return result;
}

/******************************************************************/

QString TDnsTest::getTestMethod() const
{
    return QString("DNS-%1: %2").arg(a_RequestType).arg(a_Server);
}

/******************************************************************/

QString TDnsTest::getTestedObjectInfo() const
{
    return QString("DNS test (%1)").arg(a_Server);
}

/******************************************************************/


} // namespacce SDPO
