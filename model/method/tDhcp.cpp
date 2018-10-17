#include "tDhcp.h"

namespace SDPO {

/******************************************************************/

TDhcp::TDhcp(QObject *parent) :
    TTestMethod(TMethodID::DHCP, parent)
{
    a_Host = QString();
    a_Timeout = 5000;
    a_RequestIp = QString("<current local IP>");
}

/******************************************************************/

void TDhcp::run()
{
    m_Result.status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TDhcp::clone()
{
    TDhcp *result = new TDhcp(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Host = a_Host;
    result->a_Timeout = a_Timeout;
    result->a_RequestIp = a_RequestIp;
    return result;
}

/******************************************************************/

QString TDhcp::getTestMethod() const
{
    return QString("DHCP: %1").arg(a_Host);
}

/******************************************************************/

QString TDhcp::getTestedObjectInfo() const
{
    return QString("DHCP test (%1)").arg(a_Host);
}

/******************************************************************/

} // namespace SDPO
