#ifndef TSENDDATATOTCPUDPPORTACTION_H
#define TSENDDATATOTCPUDPPORTACTION_H

#include "tTestAction.h"

namespace SDPO {

class SendDataToTcpUdpPortAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, Server) // Server
    AUTO_PROPERTY(QString, Protocol) // Protocol
    AUTO_PROPERTY(int, Port) // Port
    AUTO_PROPERTY(QString, InitPacket) // Init packet to sent
    AUTO_PROPERTY(int, WaitForAnswer) // Wait for answer
    AUTO_PROPERTY(QString, FinalPacket) // Final packet to send

public:
    explicit SendDataToTcpUdpPortAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TSENDDATATOTCPUDPPORTACTION_H
