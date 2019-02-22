#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QTcpSocket>
#include <QTime>

namespace SDPO {

/**
 * @brief The TCPConnection class
 * @details The tcp connection wraps the socket and performs operations
 */
class TCPConnection : public QObject
{
    Q_OBJECT
public:
    explicit TCPConnection(QObject *parent = nullptr);
    ~TCPConnection();

    int idleTime(); //! The number of seconds the socket has been idle

signals:
    void opened(); //! Emitted when the connection is opened
    void closed(); //! Emitted when the connection has closed

public slots:
    virtual void quit();                     //! Called when the runnable quits
    virtual void accept(qintptr descriptor); //! Called when the client should be accepted
    virtual void connected();                //! Called when the client is connected
    virtual void disconnected();             //! Called when the client has disconnected
    virtual void readyRead();                //! Called when the client has data ready to read
    virtual void bytesWritten(qint64 bytes); //! Called when the client has written bytes
    virtual void stateChanged(QAbstractSocket::SocketState socketState); //! Called when the clients state has changed
    virtual void error(QAbstractSocket::SocketError socketError);        //! Called when there is a socket error on the client

protected:
    QList<QTcpSocket*> sockets; //! List of sockets used for this connection
    QTime activity;             //! Last time the socket was active

    QTcpSocket* createSocket(); //! Creates the client socket
    void active();              //! Updates the last activity time
};

} // namespace SDPO

#endif // TCPCONNECTION_H
