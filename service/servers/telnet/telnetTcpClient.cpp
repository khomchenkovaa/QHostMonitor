#include <cstdio>
#include <iostream>

#include <QDebug>

#include "qTelnetServer.h"
#include "telnetTcpServer.h"
#include "telnetTcpClient.h"
#include "telnetLogic.h"

using namespace SDPO;

/***********************************************/

TelnetTCPClient::TelnetTCPClient(qintptr socketDescriptor,TelnetTCPServer* parent )
    : QObject(parent)
{
    strCR = "\r\n";
    strShell = QString(">");
    isAuthenticated = false;
    m_SessionID = socketDescriptor;
    m_Socket = new QTcpSocket(this);
    if(!m_Socket->setSocketDescriptor(m_SessionID)) {
        std::cerr << QTime::currentTime().toString().toStdString() << " "
                  << m_SessionID << " Error binding socket\n";
        return;
    }

    m_TelnetLogic = new TelnetLogic(this);
    slExits << "exit" << ".exit" << "exit()" << "exit;"
            << "quit" << ".quit" << "quit()" << "quit;";

    //connect the signals
    connect( m_Socket, SIGNAL(readyRead()), this, SLOT(SocketReadyRead()), Qt::DirectConnection);
    connect( m_Socket, SIGNAL(disconnected()), this, SLOT(SocketDisconnected()), Qt::DirectConnection);

    std::cout << QTime::currentTime().toString().toStdString() << " "
              << m_SessionID << " Session Connected.\n";

    sendResponse(QString("[ Command Shell ]") + strCR);
    sendResponse(QString("Enter a password: "));

}

/***********************************************/

void TelnetTCPClient::SocketReadyRead()
{
    //Keep adding to the command buffer

    QByteArray Data = m_Socket->readAll();
    m_CommandBuffer.append(Data);

    if ( Data.size() ) {
        if( Data.at(0) == 27 &&
            Data.at(1) == 91 ) {
            if ( Data.at(2) == 65 ) {
                // "UP ARROW RECIEVED";

                /*
                QString strCache = slCacheString.back();
                QString strTrim = strCache.trimmed().toLatin1();
                 qDebug() << strTrim;

                QByteArray crData;
                crData.push_back( ((char)'\r') );
                crData.push_back( ((char)'\n') );
                Socket->write( crData );

                // QByteArray DownData;
                // DownData.push_back( ((char)27) );
                // DownData.push_back( ((char)91) );
                // DownData.push_back( ((char)66) );
                // Socket->write( DownData ); // down

                // Socket->write( strTrim.toLatin1() );
                */
            }

            if ( Data.at(2) == 66 ) {
                // "DOWN ARROW RECIEVED";
            }
        }
    }

    //Check to see if the CommandBuffer has a command
    if ( ! m_CommandBuffer.endsWith('\n') ) {
        return;
    }

    // push back to cache strings
    if ( slCacheString.size() >= 100 ) {
        slCacheString.pop_front();
    }
    slCacheString.push_back( m_CommandBuffer.trimmed().toLatin1() );

    //Process the command

    if (!isAuthenticated) {
        //Authenticate the client
        if ( Authenticate(m_CommandBuffer) ) {
            sendResponse(QString("success to login.") + strCR);
            sendResponse(strShell);
        } else {
            sendResponse("failed to login. enter password:");
        }

        m_CommandBuffer.clear();
        return;
    }

    DispatchCommand( m_CommandBuffer );
    m_CommandBuffer.clear();

    sendResponse( strShell );
}

/***********************************************/

void TelnetTCPClient::SocketDisconnected()
{
    std::cout << QTime::currentTime().toString().toStdString() << " "
              << m_SessionID << " session disconnected.\n";

    //Cleanup
    m_Socket->deleteLater();
    m_TelnetLogic->deleteLater();
    this->deleteLater();
}

/***********************************************/

void TelnetTCPClient::sendResponse(const char* data)
{
    sendResponse(QString::fromLatin1(data));
}

/***********************************************/

void TelnetTCPClient::sendResponse(QString data)
{
    sendResponse(data.toLatin1());
}

/***********************************************/

void TelnetTCPClient::sendResponse(QByteArray data)
{
    if ( m_Socket == nullptr || !m_Socket->isValid() || !m_Socket->isOpen() ){
        return;
    }

    //Send the data to the client
    m_Socket->write(data);
}

/***********************************************/

void TelnetTCPClient::CloseSocket()
{
    m_Socket->close();
}

/***********************************************/

bool TelnetTCPClient::Authenticate(QString Buffer)
{
    //check the password
    QString ClientPassword = CleanQString( Buffer.trimmed() );

    // convert password to hassed password
    QString strCmp = ClientPassword.toLatin1();

    if (strCmp.isEmpty()) {
        return false;
    }

    QByteArray hash = QCryptographicHash::hash(strCmp.toLatin1(), QCryptographicHash::Sha1);
    QString hashedpass = QString(hash.toBase64());

    // read saved password
    // AUTH: PASSWORD: TODO: decrypt saved password
    QString strHashedPassword = hashedpass;

    if ( hashedpass != strHashedPassword ) { // compare hased password
        return false;
    }

    isAuthenticated = true;
    return isAuthenticated;
}

/***********************************************/

QString TelnetTCPClient::CleanQString(QString toClean)
{
    QString ret;
    ret.clear();
    int count = toClean.size();
    for ( int ic = 0 ; ic < count ; ic ++ ) {
        QChar ch = toClean.at( ic );
        if ( ch.isLetterOrNumber() ) {
            ret = ret.append( ch );
        }
    }
    return ret;
}

/***********************************************/

void TelnetTCPClient::DispatchCommand(QString command)
{
    QString cmd = command.trimmed();

    if (isExit(cmd)) {
        sendResponse( "bye..." );
        m_Socket->close();
        return;
    }

    QString ret = m_TelnetLogic->ProcessCommand( cmd );
    if ( ! ret.isEmpty() ) {
        sendResponse( ret + strCR );
    }
}

/***********************************************/

bool TelnetTCPClient::isExit(QString cmd)
{
    return slExits.contains(cmd,Qt::CaseInsensitive);
}

/***********************************************/



