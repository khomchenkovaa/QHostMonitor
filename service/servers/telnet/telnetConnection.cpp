#include <cstdint>

#include <QtCore/QDebug>
#include <QtCore/QtEndian>
#include <QHostAddress>

#include "telnetConnection.h"

using namespace SDPO;

TelnetConnection::TelnetConnection(qintptr socketDescriptor, QString address, quint16 port, QObject* parent) :
        QObject(parent),
        m_Address(address),
        m_Port(port)
{
    m_Client.setSocketDescriptor(socketDescriptor);
    m_Server.connectToHost(m_Address, m_Port);

    connect(&m_Client, &QTcpSocket::readyRead, this, &TelnetConnection::client2server);
    connect(&m_Client, &QTcpSocket::disconnected, this, &TelnetConnection::onClientDisconnected);
    connect(&m_Server, &QTcpSocket::connected, this, &TelnetConnection::sendSocksAnsver);
    connect(&m_Server, &QTcpSocket::readyRead, this, &TelnetConnection::server2client);
    connect(&m_Server, &QTcpSocket::disconnected, this, &TelnetConnection::onServerDisconnected);
}

void TelnetConnection::sendSocksAnsver()
{
    m_Client.write("Welcome to Telnet Service\n");
    m_Client.flush();
}

void TelnetConnection::client2server()
{
    m_Server.write(m_Client.readAll());
}

void TelnetConnection::server2client()
{
    m_Client.write(m_Server.readAll());
}

void TelnetConnection::onClientDisconnected()
{
    m_Server.flush();
    done();
}

void TelnetConnection::onServerDisconnected()
{
    m_Client.flush();
    done();
}

void TelnetConnection::done()
{
    m_Client.close();
    m_Server.close();
    emit finished();
}
