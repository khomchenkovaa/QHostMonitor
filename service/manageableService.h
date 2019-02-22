#ifndef MANAGEABLESERVICE_H
#define MANAGEABLESERVICE_H

#include <QObject>
#include <QDateTime>

namespace SDPO {

class ManageableService : public QObject
{
    Q_OBJECT
protected:
    bool      m_Running;
    bool      m_Paused;
    QDateTime m_PausedTo;
    bool      m_UseStartAction;
    QString   m_StartAction;
    bool      m_UseStopAction;
    QString   m_StopAction;

public:
    explicit ManageableService(QObject *parent = nullptr);

    bool isPaused() const { return m_Paused; }
    QDateTime pausedTil() const { return m_PausedTo; }
    bool isUseStartAction() const { return m_UseStartAction; }
    QString getStartAction() const { return m_StartAction; }
    bool isUseStopAction() const { return m_UseStopAction; }
    QString getStopAction() const { return m_StopAction; }
    bool isRunning() const;
    bool checkState(bool oldState);

signals:
    void stateChanged(QString action, bool running);

public slots:
    void setRunningState(bool value);
    void setPaused(bool value, const QDateTime date = QDateTime::currentDateTime());
    void setUseStartAction(bool value, const QString action = QString());
    void setUseStopAction(bool value, const QString action = QString());
    void pause(int interval);
};

} // namespace SDPO

#endif // MANAGEABLESERVICE_H
