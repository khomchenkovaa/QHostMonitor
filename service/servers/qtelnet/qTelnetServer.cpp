#include "qTelnetServer.h"
#include "telnetTcpServer.h"
#include "settings.h"
#include "utils.h"

#include <QCryptographicHash>

using namespace SDPO;

/***********************************************/

QTelnetServer::QTelnetServer(HMListService *hml, QObject *parent) :
    QObject(parent),
    m_HML(hml)
{
    readSettings();
    server = new TelnetTCPServer(this);
}

/***********************************************/

QTelnetServer::~QTelnetServer()
{
    Utils::DestructorMsg(this);
    m_HML = nullptr;
    server->deleteLater();
}

/***********************************************/

int QTelnetServer::start()
{
    return start(m_Port);
}

/***********************************************/

int QTelnetServer::start(quint16 port)
{
    return server->startServer(port);
}

/***********************************************/

void QTelnetServer::stop()
{
    server->stopServer();
}

/***********************************************/

QString QTelnetServer::exec(QString command, QStringList args) const
{
    if ( !args.count() ) {
         return "Please include the arguments to the command!";
    }

    QString ret = "Not a valid command.";

    //Set the password
    if ( command == "setpassword" ) {
        //Hash the password and then base64 encode it
        QByteArray hash = QCryptographicHash::hash(args.at(0).toLatin1(), QCryptographicHash::Sha1);
        QString hashedpass = QString(hash.toBase64());
        server->setPasswordHash(hashedpass);
        ret = "Password has been set.";
    }

    return ret;
}

/***********************************************/

void QTelnetServer::readSettings()
{
    QSettings s;
    m_Enabled             = s.value(SKEY_RCI_Enabled, SVAL_RCI_Enabled).toInt();
    m_Port = static_cast<quint16>(s.value(SKEY_RCI_Port, SVAL_RCI_Port).toInt());
    m_MaxConnections      = s.value(SKEY_RCI_MaxClients, SVAL_RCI_MaxClients).toInt();
    m_ConnectionTimeout   = s.value(SKEY_RCI_Timeout, SVAL_RCI_Timeout).toInt();
    m_LogAccepted         = s.value(SKEY_RCI_LogAccepted, SVAL_RCI_LogAccepted).toInt();
    m_LogAcceptedWatchDog = s.value(SKEY_RCI_LogAcceptedWatchDog, SVAL_RCI_LogAcceptedWatchDog).toInt();
    m_LogRejected         = s.value(SKEY_RCI_LogRejected, SVAL_RCI_LogRejected).toInt();
    m_LogRejectedWatchDog = s.value(SKEY_RCI_LogRejectedWatchDog, SVAl_RCI_LogRejectedWatchDog).toInt();
    m_LogSuccess          = s.value(SKEY_RCI_LogSuccess, SVAL_RCI_LogSuccess).toInt();
    m_LogError            = s.value(SKEY_RCI_LogError, SVAL_RCI_LogError).toInt();
}

/***********************************************/
