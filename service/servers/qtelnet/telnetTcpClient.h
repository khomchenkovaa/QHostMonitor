// QTelnetServer, MIT License
// https://github.com/j2doll/QTelnetServer

#ifndef TELNETTCPCLIENT_H
#define TELNETTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDir>
#include <QByteArray>
#include <QCryptographicHash>
#include <QProcess>
#include <QSettings>
#include <QFileInfo>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QString>
#include <QStringList>

namespace SDPO {

class TelnetLogic;
class QTelnetServer;
class TelnetTCPServer;

class TelnetTCPClient : public QObject
{
    Q_OBJECT

public:

    explicit TelnetTCPClient(qintptr socketDescriptor, TelnetTCPServer *parent = nullptr);

    /*!
    * Returns the socket ID
    */
    qintptr ID() { return m_SessionID; }

signals:

public slots:

    /*!
    * Gets the request from the client
    */
    void SocketReadyRead();

    /*!
    * Slot for the TCP socket disconnected() signal
    */
    void SocketDisconnected();

    /*!
    * Sends the response to the client socket
    * @param data The QByteArray to send
    */
    void sendResponse(QByteArray data);

    /*!
    * Sends the response to the client socket
    * @param data The QString to send
    */
    void sendResponse(QString data);

    /*!
    * Sends the response to the client socket
    * @param data The char array to send
    */
    void sendResponse(const char* data);

    /*!
    * Closes the socket
    */
    void CloseSocket();

protected:

    qintptr m_SessionID;     //! The Socket ID
    QTcpSocket *m_Socket;    //! The TCP Socket
    QString m_CommandBuffer; //! The buffer holding the command
    bool isAuthenticated;    //! Determines if the client is authenticated
    QString m_Banner;        //! The welcome banner and password prompt
    TelnetLogic *m_TelnetLogic;
    QString strCR; // carriage return
    QString strShell; // shell character >
    QString strPasswordHash;
    QStringList slCacheString;
    QStringList slExits;

protected:

    /*!
    * Sends the response to the client socket
    * @param Buffer The data buffer
    */
    bool Authenticate(QString Buffer);

    //
    QString CleanQString(QString toClean);

    //
    void DispatchCommand(QString command);

    //
    bool isExit(QString cmd);

};

} // namespace SDPO

#endif // TELNETTCPCLIENT_H
