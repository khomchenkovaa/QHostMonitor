#include "tLogEventAction.h"

namespace SDPO {

/******************************************************************/

LogEventAction::LogEventAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::LogEvent);
}

/******************************************************************/

void LogEventAction::run(SDPO::TTest *test)
{
    Q_UNUSED(test)
    // TODO LogEventAction::run implementation
}

/******************************************************************/

QStringList LogEventAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Computer: %1").arg(a_Computer));
    result.append(QString("Log: %1").arg(a_Log));
    result.append(QString("Source: %1").arg(a_EventSource));
    result.append(QString("Descr: %1").arg(a_Description));
    result.append(QString("Connect: %1").arg(b_ConnectAs?"Yes":"No"));
    result.append(QString("Username: %1").arg(a_Login));
    return result;
}

/******************************************************************/

TestAction *LogEventAction::clone()
{
    LogEventAction *result = new LogEventAction();
    copyProperties(result);
    result->setComputer(a_Computer);
    result->setLog(a_Log);
    result->setEventType(a_EventType);
    result->setEventSource(a_EventSource);
    result->setEventId(a_EventId);
    result->setDescription(a_Description);
    result->setConnectAs(b_ConnectAs);
    result->setLogin(a_Login);
    result->setPassword(a_Password);
    return result;
}

/******************************************************************/

} //namespace SDPO
