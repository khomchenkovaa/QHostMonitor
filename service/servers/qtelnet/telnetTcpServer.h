#ifndef TELNETTCPSERVER_H
#define TELNETTCPSERVER_H

#include <QTcpServer>

namespace SDPO {

class TelnetTCPServer : public QTcpServer
{
    Q_OBJECT

    QString m_PasswordKey;

public:

    explicit TelnetTCPServer(QObject *parent = nullptr);
    ~TelnetTCPServer();

    int startServer(quint16 port);
    void stopServer();
    bool setPasswordHash(QString hashedpass);

signals:
    void OnStarted(); //! Signal indicates the TCP Server has started
    void OnStopped(); //! Signal indicates the TCP Server has stopped

public slots:

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

};

} // namespace SDPO

#endif // TELNETTCPSERVER_H
