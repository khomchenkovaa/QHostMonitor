#include "rciServer.h"
#include "rciConnection.h"
#include "utils.h"
#include "settings.h"

#include <QThread>
#include <QDebug>

using namespace SDPO;

/***********************************************/

RCIServer::RCIServer(HMListService *hml, QObject *parent) : TCPServer(parent),
    m_HML(hml)
{
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
    m_Enabled             = s.value(SKEY_RCI_Enabled, SVAL_RCI_Enabled).toInt();
    m_Port = static_cast<quint16>(s.value(SKEY_RCI_Port, SVAL_RCI_Port).toInt());
    setMaxConnections      (s.value(SKEY_RCI_MaxClients, SVAL_RCI_MaxClients).toInt());
    setConnectionTimeout   (s.value(SKEY_RCI_Timeout, SVAL_RCI_Timeout).toInt());
    m_LogAccepted         = s.value(SKEY_RCI_LogAccepted, SVAL_RCI_LogAccepted).toInt();
    m_LogAcceptedWatchDog = s.value(SKEY_RCI_LogAcceptedWatchDog, SVAL_RCI_LogAcceptedWatchDog).toInt();
    m_LogRejected         = s.value(SKEY_RCI_LogRejected, SVAL_RCI_LogRejected).toInt();
    m_LogRejectedWatchDog = s.value(SKEY_RCI_LogRejectedWatchDog, SVAl_RCI_LogRejectedWatchDog).toInt();
    m_LogSuccess          = s.value(SKEY_RCI_LogSuccess, SVAL_RCI_LogSuccess).toInt();
    m_LogError            = s.value(SKEY_RCI_LogError, SVAL_RCI_LogError).toInt();
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
