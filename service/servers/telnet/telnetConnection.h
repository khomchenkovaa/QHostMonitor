#ifndef TELNETCONNECTION_H
#define TELNETCONNECTION_H

#include <QTcpSocket>

namespace SDPO {

class TelnetConnection: public QObject
{
    Q_OBJECT

    QString m_Address;
    quint16 m_Port;

    QTcpSocket m_Client;
    QTcpSocket m_Server;
public:

    TelnetConnection(qintptr socketDescriptor, QString address, quint16 port, QObject* parent = nullptr);

signals:
    void finished();
    void error(QString err);

public slots:
    void client2server();
    void server2client();

    void sendSocksAnsver();

    void onClientDisconnected();
    void onServerDisconnected();

private:
    void done();

};

} // namespace SDPO

#endif // TELNETCONNECTION_H
