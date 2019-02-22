#include "rciServer.h"
#include "rciConnection.h"
#include "utils.h"

#include <QThread>
#include <QDebug>

using namespace SDPO;

/***********************************************/

RCIServer::RCIServer(HMListService *hml, QObject *parent) : TCPServer(parent),
    m_HML(hml)
{
}

/***********************************************/

RCIServer::~RCIServer()
{
    Utils::DestructorMsg(this);
    m_HML = nullptr;
}

/***********************************************/

void RCIServer::accept(qintptr handle, TCPRunnable *runnable)
{
    qDebug() << this << "Called in HTTP Server";
    qDebug() << this << "accepting" << handle << "on" << runnable;

    RCIConnection *connection = new RCIConnection(m_HML);

    if(!connection) {
        qCritical() << this << "could not find connection to accept connection: " << handle;
        return;
    }

    qDebug() << this << "accepting" << handle;
    emit connecting(handle,runnable,connection);
}

/***********************************************/
