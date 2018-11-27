#include "tSendDataToTcpUdpPortAction.h"

namespace SDPO {

/******************************************************************/

SendDataToTcpUdpPortAction::SendDataToTcpUdpPortAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::SendData);
}

/******************************************************************/

void SendDataToTcpUdpPortAction::run(TTest *test)
{
    Q_UNUSED(test)
}

/******************************************************************/

QStringList SendDataToTcpUdpPortAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Server: %1").arg(a_Server));
    result.append(QString("Port: %1").arg(a_Port));
    result.append(QString("Protocol: %1").arg(a_Protocol));
    result.append(QString("InitPacket: %1").arg(a_InitPacket));
    result.append(QString("WaitDelay: %1").arg(a_WaitForAnswer));
    result.append(QString("FinalPacket: %1").arg(a_FinalPacket));
    return result;
}

/******************************************************************/

SDPO::TestAction *SendDataToTcpUdpPortAction::clone()
{
    SendDataToTcpUdpPortAction *result = new SendDataToTcpUdpPortAction();
    copyProperties(result);
    result->setServer(a_Server);
    result->setPort(a_Port);
    result->setProtocol(a_Protocol);
    result->setInitPacket(a_InitPacket);
    result->setWaitForAnswer(a_WaitForAnswer);
    result->setFinalPacket(a_FinalPacket);
    return result;
}

/******************************************************************/

} // namespace SDPO
