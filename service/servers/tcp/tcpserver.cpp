#include "tcpserver.h"

using namespace SDPO;

/*****************************************************************/

TCPServer::TCPServer(QObject *parent) :
    QTcpServer(parent),
    m_ThreadPool(*new QThreadPool(this)),
    m_ThreadMode(MODE_SINGLE)
{
    connect(&m_Timer,&QTimer::timeout,this,&TCPServer::timeout);
}

/*****************************************************************/

TCPServer::~TCPServer()
{
}

/*****************************************************************/

void TCPServer::listen(const QHostAddress &address, quint16 port)
{
    if(!QTcpServer::listen(address,port)) {
        qCritical() << this << errorString();
        return;
    }

    switch (m_ThreadMode) {
    case MODE_SINGLE:
        startSingle();
        break;
    case MODE_POOLED:
        startPooled();
        break;
    case MODE_THREADED:
        startThreaded();
        break;
    }

    m_Timer.start(1000);
}

/*****************************************************************/

void TCPServer::close()
{
    emit closing();
    m_ThreadPool.deleteLater();
    QTcpServer::close();
    m_Timer.stop();
}

/*****************************************************************/

void TCPServer::incomingConnection(qintptr handle)
{
    //Determine if we can accept the connection
    if (m_MaxConnections) {
        int connCount = connections();
        if(connCount >= m_MaxConnections) {
            reject(handle);
            return;
        }
    }

    //Accept the connection
    switch (m_ThreadMode) {
    case MODE_SINGLE:
        acceptSingle(handle);
        break;
    case MODE_POOLED:
        acceptPooled(handle);
        break;
    case MODE_THREADED:
        acceptThreaded(handle);
        break;
    }
}

/*****************************************************************/

void TCPServer::started()
{
    TCPRunnable *runnable = static_cast<TCPRunnable*>(sender());
    if(!runnable) return;
    qDebug() << runnable << "has started";
}

/*****************************************************************/

void TCPServer::finished()
{
    TCPRunnable *runnable = static_cast<TCPRunnable*>(sender());
    if(!runnable) return;
    qDebug() << runnable << "has finished, removing from list";

    m_Runnables.removeAll(runnable);
    runnable->deleteLater();
}

/*****************************************************************/

void TCPServer::timeout()
{
    if(m_ConnectionTimeout) {
        emit idle(m_ConnectionTimeout);
    }
}

/*****************************************************************/

void TCPServer::startRunnable(TCPRunnable *runnable)
{
    if(!runnable) {
        qWarning() << this << "Runnable is null!";
        return;
    }

    m_Runnables.append(runnable);

   // connect(this,&TCPServer::accept, runnable,&TCPRunnable::accept, Qt::QueuedConnection);
    connect(this,&TCPServer::closing,runnable, &TCPRunnable::closing, Qt::QueuedConnection);
    connect(this,&TCPServer::connecting, runnable,&TCPRunnable::connecting, Qt::QueuedConnection);
    connect(this,&TCPServer::idle, runnable, &TCPRunnable::idle, Qt::QueuedConnection);

    connect(runnable,&TCPRunnable::started, this, &TCPServer::started, Qt::QueuedConnection);
    connect(runnable,&TCPRunnable::finished, this, &TCPServer::finished, Qt::QueuedConnection);

    if(m_ThreadMode == MODE_THREADED) {
        runnable->setThreadedMode(true);
    }

    m_ThreadPool.start(runnable);
}

/*****************************************************************/

void TCPServer::reject(qintptr handle)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(handle);
    socket->close();
    socket->deleteLater();
}

/*****************************************************************/

void TCPServer::acceptSingle(qintptr handle)
{
    //All connections run on a single thread
    if(!m_Runnables.count()) {
        reject(handle);
        qCritical() << this << "no runnables to accept connection: " << handle;
        return;
    }

    TCPRunnable *runnable = m_Runnables.at(0);
    if(!runnable) {
        reject(handle);
        qCritical() << this << "could not find runnable to accept connection: " << handle;
        return;
    }

     accept(handle,runnable);
}

/*****************************************************************/

void TCPServer::acceptPooled(qintptr handle)
{
    //All connection run in a pool of threads

    int previous = 0;
    TCPRunnable *runnable = nullptr;

    foreach(TCPRunnable *item, m_Runnables) {
        int count = item->count();

        if (!count) {
            runnable = item;
            break;
        }

        if (!runnable || count < previous) {
            previous = count;
            runnable = item;
        }
    }

    if(!runnable) {
        reject(handle);
        qWarning() << this << "Could not find runable!";
        return;
    }

    accept(handle,runnable);
}

/*****************************************************************/

void TCPServer::acceptThreaded(qintptr handle)
{
    //Each connection runs in its own thread

    TCPRunnable *runnable = new TCPRunnable();
    if(!runnable) {
        reject(handle);
        qWarning() << this << "Could not create runable!";
        return;
    }

    startRunnable(runnable);
    accept(handle,runnable);
}

/*****************************************************************/

void TCPServer::startSingle()
{
    m_ThreadPool.setMaxThreadCount(1);
    m_ThreadPool.setExpiryTimeout(-1);
    TCPRunnable *runnable = new TCPRunnable();
    if (runnable) {
        runnable->setAutoDelete(false);
        startRunnable(runnable);
    }
}

/*****************************************************************/

void TCPServer::startPooled()
{
    for(int i = 0; i < m_ThreadPool.maxThreadCount(); i++) {
        TCPRunnable *runnable = new TCPRunnable();
        if (runnable) {
            runnable->setAutoDelete(false);
            startRunnable(runnable);
        }
    }
}

/*****************************************************************/

void TCPServer::startThreaded()
{
    // Do nothing
}

/*****************************************************************/

int TCPServer::connections()
{
    int result = 0;
    foreach(TCPRunnable *item, m_Runnables) {
        result += item->count();
    }

    return result;
}

/*****************************************************************/

void TCPServer::accept(qintptr handle, TCPRunnable *runnable)
{
    TCPConnection *connection = new TCPConnection;
    if(!connection) {
        reject(handle);
        qCritical() << this << "could not find connection to accept connection: " << handle;
        return;
    }

    emit connecting(handle,runnable,connection);
}

/*****************************************************************/
