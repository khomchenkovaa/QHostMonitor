#ifndef RCISERVER_H
#define RCISERVER_H

#include "servers/tcp/tcpserver.h"
#include "hmListService.h"

namespace SDPO {

class RCIServer : public TCPServer
{
    Q_OBJECT

    HMListService *m_HML;

public:
    explicit RCIServer(HMListService *hml, QObject *parent = nullptr);
    ~RCIServer();

public slots:
    void accept(qintptr handle, TCPRunnable *runnable);

};

} // namespace SDPO

#endif // RCISERVER_H
