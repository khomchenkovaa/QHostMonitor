#include "telnetTcpClient.h"
#include "telnetTcpServer.h"

#include <iostream>


using namespace SDPO;

/***********************************************/

TelnetTCPServer::TelnetTCPServer(QObject *parent)
    : QTcpServer(parent)
{
}

/***********************************************/

TelnetTCPServer::~TelnetTCPServer()
{
}

/***********************************************/

int TelnetTCPServer::startServer(quint16 port)
{

    if( ! this->listen( QHostAddress::Any, port ) ) {
        std::cerr << " could not start server\n";
        return (-1);
    }

    std::cout
        << QTime::currentTime().toString().toStdString() << " "
        << "listening...\n";

    //notify connected objects
    emit OnStarted();

    return 0;
}

/***********************************************/

void TelnetTCPServer::stopServer()
{
    this->close();

    std::cout << QTime::currentTime().toString().toStdString() << "server stopped\n";

    //notify connected objects
    emit OnStopped();

}

/***********************************************/

bool TelnetTCPServer::setPasswordHash(QString hashedpass)
{
    m_PasswordKey = hashedpass;
    return true;
}

/***********************************************/

void TelnetTCPServer::incomingConnection(qintptr socketDescriptor)
{
    std::cout << QTime::currentTime().toString().toStdString() << " Connecting..." << socketDescriptor << "\n";

    TelnetTCPClient *cClient = new TelnetTCPClient( socketDescriptor, this );

    connect( this,SIGNAL(OnStopped()), cClient, SLOT(CloseSocket()) );
}

/***********************************************/

