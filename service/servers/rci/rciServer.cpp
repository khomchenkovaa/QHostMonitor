#include "rciServer.h"
#include "rciConnection.h"
#include "utils.h"
#include "gSettings.h"

#include <QThread>
#include <QDebug>

using namespace SDPO;

/***********************************************/

RCIServer::RCIServer(HMListService *hml, QObject *parent) : TCPServer(parent),
    m_HML(hml)
{
    setMode(TCPServer::MODE_THREADED);
    readSettings();
    if(m_Enabled) {
        listen(QHostAddress::Any, m_Port);
    }
}

/***********************************************/

RCIServer::~RCIServer()
{
    Utils::DestructorMsg(this);
    m_HML = nullptr;
}

/***********************************************/

void RCIServer::readSettings()
{
    QSettings s;
    m_Enabled = s.value(SKEY_RCI_Enabled, false).toBool();
    m_Port = static_cast<quint16>(s.value(SKEY_RCI_Port, 1054).toInt());
    setMaxConnections(s.value(SKEY_RCI_MaxClients, 16).toInt());
    setConnectionTimeout(s.value(SKEY_RCI_Timeout, 300000).toInt());
    m_LogAccepted = s.value(SKEY_RCI_LogAccepted, false).toBool();
    m_LogAcceptedWatchDog = s.value(SKEY_RCI_LogAcceptedWatchDog, false).toBool();
    m_LogRejected = s.value(SKEY_RCI_LogRejected, false).toBool();
    m_LogRejectedWatchDog = s.value(SKEY_RCI_LogRejectedWatchDog, false).toBool();
    m_LogSuccess = s.value(SKEY_RCI_LogSuccess, false).toBool();
    m_LogError = s.value(SKEY_RCI_LogError, false).toBool();
}

/***********************************************/

void RCIServer::accept(qintptr handle, TCPRunnable *runnable)
{
    RCIConnection *connection = new RCIConnection(m_HML);

    if(!connection) {
        reject(handle);
        qCritical() << this << "could not find connection to accept connection: " << handle;
        return;
    }

    qDebug() << this << "accepting" << handle;
    emit connecting(handle,runnable,connection);
}

/***********************************************/
