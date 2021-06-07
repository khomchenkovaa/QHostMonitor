#include "tPerformanceCounter.h"

namespace SDPO {

TPerformanceCounter::TPerformanceCounter(QObject *parent) :
    TestMethod(TMethodID::PerfCounter, parent)
{
    a_CheckCounter = QString();
    a_AlertWhen = QString("is < than");
    a_AlertWhenCounter = 0.00;
    a_DisplayMode = QString("as is");
    b_ConnectAs = false;
    a_Login = QString();
    a_Password = QString();
}

/******************************************************************/

void TPerformanceCounter::run()
{
    m_Result.status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TestMethod *TPerformanceCounter::clone()
{
    TPerformanceCounter *result = new TPerformanceCounter(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_CheckCounter = a_CheckCounter;
    result->a_AlertWhen = a_AlertWhen;
    result->a_AlertWhenCounter = a_AlertWhenCounter;
    result->a_DisplayMode = a_DisplayMode;
    result->b_ConnectAs = b_ConnectAs;
    result->a_Login = a_Login;
    result->a_Password = a_Password;
    return result;
}

/******************************************************************/

QString TPerformanceCounter::getTestMethod() const
{
    return QString("PerfCounter: %1").arg(a_CheckCounter);
}

/******************************************************************/

QString TPerformanceCounter::getTestedObjectInfo() const
{
    return QString("PerfCounter test (%1)").arg(a_CheckCounter);
}

/******************************************************************/

} // namespace SDPO
