#include "tDominantProcess.h"

namespace SDPO {

/******************************************************************/

TDominantProcess::TDominantProcess(QObject *parent) :
    TestMethod(TMethodID::DominantProcess, parent)
{
    a_CheckProcessesOn = QString("localhost");
    a_ExcludeProcesses = QString();
    a_AlertIfCount = 50;
    a_AlertIf = QString("Memory (MB)");
    a_TopProcesses = QString("value, process name, ID");
    b_ConnectAs = false;
    a_Login = QString();
    a_Password = QString();
}

/******************************************************************/

void TDominantProcess::run()
{
    m_Result.status = TestStatus::Ok;
    writeLogTitle();
    m_Log.append("Dominant process method not implemented\n");
    emit testSuccess();
}

/******************************************************************/

TestMethod *TDominantProcess::clone()
{
    TDominantProcess *result = new TDominantProcess(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_CheckProcessesOn = a_CheckProcessesOn;
    result->a_ExcludeProcesses = a_ExcludeProcesses;
    result->a_AlertIfCount = a_AlertIfCount;
    result->a_AlertIf = a_AlertIf;
    result->a_TopProcesses = a_TopProcesses;
    result->b_ConnectAs = b_ConnectAs;
    result->a_Login = a_Login;
    result->a_Password = a_Password;
    return result;
}

/******************************************************************/

QString TDominantProcess::getTestMethod() const
{
    return QString("TopProcesess: <%1> (%2)").arg(a_CheckProcessesOn).arg(a_AlertIf);
}

/******************************************************************/

QString TDominantProcess::getTestedObjectInfo() const
{
    return QString("Dominant processes (<%1>)").arg(a_CheckProcessesOn);
}

/******************************************************************/


} // namespace SDPO
