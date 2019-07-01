#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDebug>
#include <QTcpServer>
#include <QThreadPool>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QTimer>

#include "tcprunnable.h"

namespace SDPO {

/**
 * \brief TCP Server class
 *
 * Seige test = siege 127.0.0.1:2000 -c 1000
 */
class TCPServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit TCPServer(QObject *parent = nullptr);
    ~TCPServer();

    void setMaxThreads(const int value)        { m_ThreadPool.setMaxThreadCount(value); }
    void setMaxConnections(const int value)    { m_MaxConnections = value; }
    void setConnectionTimeout(const int value) { m_ConnectionTimeout = value; }

    virtual void listen(const QHostAddress &address, quint16 port);
    virtual void close();
    virtual quint16 port();

signals:
    void connecting(qintptr handle, TCPRunnable *runnable, TCPConnection* connection);
    void closing();       //! Emitted when the server is closing
    void idle(int value); //! Emitted when idle connections should be removed

public slots:
    void started();  //! Called when a runnable is started on a thread
    void finished(); //! Called when a runnable has finished running on a thread
    void timeout();  //! Called when the servers timers timeout is emitted

protected:
    QThreadPool &m_ThreadPool;
    int m_MaxConnections = 0;              //! The maximum number of connections, Zero is unlimited
    int m_ConnectionTimeout = 0;           //! Time out for idle connections, Zero is never
    QList<TCPRunnable*> m_Runnables;       //! List of runnables that are on different threads
    QTimer m_Timer;                        //! Timer for server operations
    quint16 m_Port = 0;

    virtual void incomingConnection(qintptr handle);            //! Called when a connection is ready to be accepted
    virtual void startRunnable(TCPRunnable *runnable);          //! Connects the runnable and starts it
    virtual void reject(qintptr handle);                        //! Rejects a connection
    virtual int connections();                                  //! Gets the number of connections on all runnables
    virtual void accept(qintptr handle, TCPRunnable *runnable); //! Incomming connection is waiting to be accepted

};

} // namespace SDPO

#endif // TCPSERVER_H
