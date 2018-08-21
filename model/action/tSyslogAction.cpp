#include "tSyslogAction.h"

namespace SDPO {

/******************************************************************/

SyslogAction::SyslogAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::Syslog);
}

/******************************************************************/

void SyslogAction::run(TTest *test)
{
    Q_UNUSED(test)
}

/******************************************************************/

QStringList SyslogAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Host: %1").arg(a_Server));
    result.append(QString("Port: %1").arg(a_Port));
    result.append(QString("Facility: %1").arg(a_Facility));
    result.append(QString("Severity: %1").arg(a_Severity));
    result.append(QString("LogMessage: %1").arg(a_Message));
    return result;
}

/******************************************************************/

TestAction *SyslogAction::clone()
{
    SyslogAction *result = new SyslogAction();
    copyProperties(result);
    result->setServer(a_Server);
    result->setPort(a_Port);
    result->setMessage(a_Message);
    result->setSeverity(a_Severity);
    result->setFacility(a_Facility);
    return result;
}

/******************************************************************/

} // namespace SDPO
