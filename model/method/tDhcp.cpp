#include "tDhcp.h"

#include <QNetworkInterface>
#include <QHostInfo>
#include <QProcess>

#include <QDebug>

namespace SDPO {

/******************************************************************/

TDhcp::TDhcp(QObject *parent) :
    TTestMethod(TMethodID::DHCP, parent)
{
    a_Host = QString();
    a_Timeout = 5; // sec
    a_RequestIp = DHCP_CURRENT_LOCAL_IP;
}

/******************************************************************/

void TDhcp::run()
{
    m_Result.clear();

    QString command = getCommand();
    if (command.isEmpty()) {
        m_Result.error = "Command is empty";
        emit testFailed();
        return;
    }
    qDebug() << "cmd:" << command;

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(command);
    if (!process.waitForStarted()) {
        m_Result.reply = getTestedObjectInfo() + " can not start";
        process.close();
        emit testFailed();
        return;
    }
    if(!process.waitForFinished((a_Timeout + 1) * 1000)) {
        m_Result.reply = getTestedObjectInfo() + " terminated";
        process.close();
        emit testFailed();
        return;
    }
    if( process.exitStatus() == QProcess::NormalExit && !process.exitCode()) {
        m_Result.status = TestStatus::HostAlive;
        emit testSuccess();
    } else {
        QString reply = process.readAll().trimmed();
        if (reply.contains("no answer",Qt::CaseInsensitive)) {
            m_Result.status = TestStatus::NoAnswer;
        } else {
            m_Result.status = TestStatus::Bad;
        }
        m_Result.error = process.errorString();
        emit testFailed();
    }
}

/******************************************************************/

QString TDhcp::getCommand() const
{
    // dhcping -s <Host> -t <Timeout> -c <Request IP>
    QString cmd = "dhcping";
    if (!a_Host.isEmpty()) {
        cmd.append(QString(" -s %1").arg(a_Host));
    }
    if (a_Timeout) {
        cmd.append(QString(" -t %1").arg(a_Timeout));
    }
    if (a_RequestIp.isEmpty() || (a_RequestIp == DHCP_CURRENT_LOCAL_IP) ) {
        QString localIP = currentLocalIP();
        QString macAddress = currentMacAddress();
        if (!macAddress.isEmpty()) {
            cmd.append(QString(" -h %1").arg(macAddress));
        }
        if (!localIP.isEmpty()) {
            cmd.append(QString(" -c %1").arg(localIP));
        }
    } else {
        cmd.append(QString(" -c %1").arg(a_RequestIp));
    }
    return cmd;
}

/******************************************************************/

TTestMethod *TDhcp::clone()
{
    TDhcp *result = new TDhcp(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Host = a_Host;
    result->a_Timeout = a_Timeout;
    result->a_RequestIp = a_RequestIp;
    return result;
}

/******************************************************************/

QString TDhcp::currentLocalIP() const
{
    QString result;

    foreach (const QNetworkInterface &netInterface, QNetworkInterface::allInterfaces()) {
        QNetworkInterface::InterfaceFlags flags = netInterface.flags();
        if( (bool)(flags & QNetworkInterface::IsRunning) && !(bool)(flags & QNetworkInterface::IsLoopBack)){
            foreach (const QNetworkAddressEntry &address, netInterface.addressEntries()) {
                if(address.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                    result = address.ip().toString();
                    qDebug() << "My IP:" << result;
                    // break;
                }
            }
        }
    }
    return result;
}

/******************************************************************/

QString TDhcp::currentMacAddress() const
{
    QString result;
    foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces()) {
        QNetworkInterface::InterfaceFlags flags = networkInterface.flags();
        if( (bool)(flags & QNetworkInterface::IsRunning) && !(bool)(flags & QNetworkInterface::IsLoopBack)){
            result = networkInterface.hardwareAddress();
            qDebug() << "MAC = " << result;
            // break;
        }
    }
    return result;
}

/******************************************************************/

QString TDhcp::getTestMethod() const
{
    return QString("DHCP: %1").arg(a_Host);
}

/******************************************************************/

QString TDhcp::getTestedObjectInfo() const
{
    return QString("DHCP test (%1)").arg(a_Host);
}

/******************************************************************/

} // namespace SDPO
