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
    m_Enabled = s.value(SKEY_RCI_Enabled, false).toBool();
    m_Port = static_cast<quint16>(s.value(SKEY_RCI_Port, 1054).toInt());
    m_MaxConnections = s.value(SKEY_RCI_MaxClients, 16).toInt();
    m_ConnectionTimeout = s.value(SKEY_RCI_Timeout, 300000).toInt();
    m_LogAccepted = s.value(SKEY_RCI_LogAccepted, false).toBool();
    m_LogAcceptedWatchDog = s.value(SKEY_RCI_LogAcceptedWatchDog, false).toBool();
    m_LogRejected = s.value(SKEY_RCI_LogRejected, false).toBool();
    m_LogRejectedWatchDog = s.value(SKEY_RCI_LogRejectedWatchDog, false).toBool();
    m_LogSuccess = s.value(SKEY_RCI_LogSuccess, false).toBool();
    m_LogError = s.value(SKEY_RCI_LogError, false).toBool();
}

/***********************************************/
