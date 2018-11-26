#include "manageableService.h"

namespace SDPO {

/***********************************************/

ManageableService::ManageableService(QObject *parent) :
    QObject(parent),
    m_Running(true),
    m_Paused(false),
    m_PausedTo(QDateTime::currentDateTime()),
    m_UseStartAction(false),
    m_UseStopAction(false)
{
}

/***********************************************/

bool ManageableService::isRunning() const
{
    return m_Running && !m_Paused;
}

/***********************************************/

bool ManageableService::checkState(bool oldState)
{
    if (m_Paused) {
        m_Paused = QDateTime::currentDateTime() < m_PausedTo;
    }
    bool newState = isRunning();

    if (newState != oldState) {
        emit stateChanged(newState?m_StartAction:m_StopAction, newState);
    }
    return newState;
}

/***********************************************/

void ManageableService::setRunningState(bool value)
{
    bool oldState = isRunning();
    m_Running = value;
    checkState(oldState);
}

/***********************************************/

void ManageableService::setPaused(bool value, const QDateTime date)
{
    bool oldState = isRunning();
    m_Paused = value;
    m_PausedTo = date;
    checkState(oldState);
}

/***********************************************/

void ManageableService::setUseStartAction(bool value, const QString action)
{
    m_UseStartAction = value;
    m_StartAction = action;
}

/***********************************************/

void ManageableService::setUseStopAction(bool value, const QString action)
{
    m_UseStopAction = value;
    m_StopAction = action;
}

/***********************************************/

void ManageableService::pause(int interval)
{
    QDateTime dt = QDateTime::currentDateTime();
    setPaused(true, dt.addSecs(interval * 60));
}

/***********************************************/

} // namespace SDPO
