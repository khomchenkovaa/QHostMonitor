#ifndef TELNETSERVER_H
#define TELNETSERVER_H

#include <QVector>
#include <QTcpServer>
#include <QThread>
#include <QDateTime>

#include "telnetWorker.h"

namespace SDPO {

struct RciSettings {
    QString address;
    quint16 port;
    int     timeout;
};

class TelnetServer: public QTcpServer
{
    Q_OBJECT

    QDateTime   m_StartedAt;
    int         m_ActiveConnections;
    int         m_ServedConnections;
    RciSettings m_RCI;

    int                    m_ThreadCount;
    QVector<QThread*>      m_Threads;
    QVector<TelnetWorker*> m_Workers;
    int                    m_RRCounter;

public:
    TelnetServer(QObject * parent = nullptr);
    ~TelnetServer();

    bool listen(quint16 port = 23);

    void setRciSettings(const RciSettings &value) { m_RCI = value; }
    RciSettings rciSettings() const { return m_RCI; }

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

};

} // namespace SDPO

#endif // TELNETSERVER_H
