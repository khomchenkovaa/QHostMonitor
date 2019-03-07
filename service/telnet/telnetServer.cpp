#include "telnetServer.h"
#include "telnetWorker.h"

using namespace SDPO;

/******************************************************************/

TelnetServer::TelnetServer(QObject * parent) :
        QTcpServer(parent)
{

}

/******************************************************************/

TelnetServer::~TelnetServer()
{

}

/******************************************************************/

bool TelnetServer::listen(quint16 port)
{
    if (QTcpServer::listen(QHostAddress::Any,port)) {
        m_StartedAt = QDateTime::currentDateTime();
        m_ActiveConnections = 0;
        m_ServedConnections = 0;
        return true;
    }
    return false;
}

/******************************************************************/

void TelnetServer::incomingConnection(qintptr socketDescriptor)
{
    QThread* thread = new QThread(this);
    TelnetWorker* worker = new TelnetWorker(socketDescriptor, m_RCI.address, m_RCI.port, m_RCI.timeout);
    worker->moveToThread(thread);
    connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

/******************************************************************/
