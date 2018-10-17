#include "tNtEventLog.h"

namespace SDPO {

TNtEventLog::TNtEventLog(QObject *parent) :
    TTestMethod(TMethodID::NTLog, parent)
{
    b_LogSource = true;
    b_AlertCondition = false;
    b_ConnectAs = false;
    a_Compatibility = QString("Linux");
    a_ComputerUnc = QString("localhost");
    a_Log = QString("");
    a_EventSource = QString("");
    a_Computer = QString("Any");
    a_EventType = QString("Any");
    a_EventId = QString("Any");
    a_Description = QString("Any");
    b_ConnectToRemote = false;
    a_Login = QString("");
    a_Password = QString("");
}

/******************************l************************************/

void TNtEventLog::run()
{
    m_Result.status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TNtEventLog::clone()
{
    TNtEventLog *result = new TNtEventLog(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->b_LogSource = b_LogSource;
    result->b_AlertCondition = b_AlertCondition;
    result->b_ConnectAs = b_ConnectAs;
    result->a_Compatibility = a_Compatibility;
    result->a_ComputerUnc = a_ComputerUnc;
    result->a_Log = a_Log;
    result->a_EventSource = a_EventSource;
    result->a_Computer = a_Computer;
    result->a_EventType = a_EventType;
    result->a_EventId = a_EventId;
    result->a_Description = a_Description;
    result->b_ConnectToRemote = b_ConnectToRemote;
    result->a_Login = a_Login;
    result->a_Password = a_Password;
    return result;
}

/******************************************************************/

QString TNtEventLog::getTestMethod() const
{
    return QString("NT Log Localhost: %1\%2").arg(a_Log).arg(a_EventSource);
}

/******************************************************************/

QString TNtEventLog::getTestedObjectInfo() const
{
    return QString("check NT Event Log (:%1)").arg(a_EventSource);
}

/******************************************************************/

} // namespace SDPO
