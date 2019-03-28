#ifndef QTELNETSERVER_H
#define QTELNETSERVER_H

#include <QObject>
#include "hmListService.h"

namespace SDPO {

class TelnetTCPServer;

class QTelnetServer : public QObject
{
    Q_OBJECT

    HMListService *m_HML;

    bool m_Enabled;
    quint16 m_Port;
    int m_MaxConnections;
    int m_ConnectionTimeout;
    bool m_LogAccepted;
    bool m_LogAcceptedWatchDog;
    bool m_LogRejected;
    bool m_LogRejectedWatchDog;
    bool m_LogSuccess;
    bool m_LogError;

public:
    explicit QTelnetServer(HMListService *hml = nullptr, QObject *parent = nullptr);
    ~QTelnetServer();
    int start();
    int start(quint16 port = 23);
    void stop();
    QString exec(QString command, QStringList args) const;

public slots:
    void readSettings();

protected:
    TelnetTCPServer *server;
};

} // namespace SDPO

#endif // QTELNETSERVER_H
