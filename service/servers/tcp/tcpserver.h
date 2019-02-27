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
 * \details Runs in three modes
 * \li Single - The connectoions share a single thread
 * \li Pooled - The connections share a comon pool of threads
 * \li Threaded - The connections run in their own thread
 *
 * Seige test = siege 127.0.0.1:2000 -c 1000
 */
class TCPServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit TCPServer(QObject *parent = nullptr);
    ~TCPServer();

    /**
     * \brief The ThreadMode enum
     */
    enum ThreadMode {
        MODE_SINGLE = 0,    /**< All connections run on a single thread */
        MODE_POOLED = 1,    /**< All connections run in a pool of threads */
        MODE_THREADED = 2   /**< All connections run in their own thread */
    };

    void setMaxThreads(const int value)        { m_ThreadPool.setMaxThreadCount(value); }
    void setMaxConnections(const int value)    { m_MaxConnections = value; }
    void setConnectionTimeout(const int value) { m_ConnectionTimeout = value; }
    void setMode(const ThreadMode value)       { m_ThreadMode = value; }

    /**
     * \brief Listens for incomming connections
     * \param address The address to listen on
     * \param port The port to listen on
     */
    void listen(const QHostAddress &address, quint16 port);
    void close();               //! Closes the server, any connections will quit

signals:
    /**
     * \brief Emitted when an incomming connection is waiting to be accepted
     * \param handle The socket descriptor
     * \param runnable The runnable to accept the connection
     * \param connection The connection to accept
     */
    void connecting(qintptr handle, TCPRunnable *runnable, TCPConnection* connection);
    void closing();       //! Emitted when the server is closing
    void idle(int value); //! Emitted when idle connections should be removed

public slots:
    void started();  //! Called when a runnable is started on a thread
    void finished(); //! Called when a runnable has finished running on a thread
    void timeout();  //! Called when the servers timers timeout is emitted

protected:
    QThreadPool &m_ThreadPool;
    ThreadMode m_ThreadMode = MODE_SINGLE; //! The thread mode to run in
    int m_MaxConnections = 0;              //! The maximum number of connections, Zero is unlimited
    int m_ConnectionTimeout = 0;           //! Time out for idle connections, Zero is never
    QList<TCPRunnable*> m_Runnables;       //! List of runnables that are on different threads
    QTimer m_Timer;                        //! Timer for server operations

    virtual void incomingConnection(qintptr handle);            //! Called when a connection is ready to be accepted
    virtual void startRunnable(TCPRunnable *runnable);          //! Connects the runnable and starts it
    virtual void reject(qintptr handle);                        //! Rejects a connection
    virtual void acceptSingle(qintptr handle);                  //! Accepts a connection in MODE_SINGLE
    virtual void acceptPooled(qintptr handle);                  //! Accepts a connection in MODE_POOLED
    virtual void acceptThreaded(qintptr handle);                //! Accepts a connection in MODE_THREADED
    virtual void startSingle();                                 //! Starts the runnables in MODE_SINGLE
    virtual void startPooled();                                 //! Starts the runnabled in MODE_POOLED
    virtual void startThreaded();                               //! Starts the runnabled in MODE_THREADED
    virtual int connections();                                  //! Gets the number of connections on all runnables
    virtual void accept(qintptr handle, TCPRunnable *runnable); //! Incomming connection is waiting to be accepted

};

} // namespace SDPO

#endif // TCPSERVER_H
