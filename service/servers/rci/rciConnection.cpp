#include "rciConnection.h"
#include "qSimpleCrypt.hpp"

#include <QDebug>

using namespace SDPO;

/***********************************************/

RCIConnection::RCIConnection(HMListService *hml, QObject *parent) :
    TCPConnection (parent),
    m_HMScriptRunner(*new HMScriptRunner(hml, this))
{
}

/***********************************************/

RCIConnection::~RCIConnection()
{
    delete &m_HMScriptRunner;
}

/***********************************************/

void RCIConnection::readyRead()
{
    TCPConnection::readyRead();

    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    if(!socket) return;

    QByteArray data = socket->readAll();
//    SimpleCrypt crypt(128);
//    qDebug() << "Encrypted:" << data;
//    QString decrypted = crypt.decryptToString(data);
//    qDebug() << "Decrypted:" << decrypted;
    m_HMScriptRunner.setScript(data);

    QByteArray response;
    bool result = m_HMScriptRunner.run();

    response.append(result?"Done\n":"Fail\n");
    foreach(QString line, m_HMScriptRunner.scriptErrors()) {
        response.append(line + "\n");
    }

    socket->write(response);
    socket->waitForBytesWritten();
    //socket->close();
}

/***********************************************/
