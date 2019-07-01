#ifndef RCISERVER_H
#define RCISERVER_H

#include "servers/tcp/tcpserver.h"
#include "hmListService.h"

namespace SDPO {

class RCIServer : public TCPServer
{
    Q_OBJECT

    HMListService *m_HML;

    bool m_Enabled;
    bool m_LogAccepted;
    bool m_LogAcceptedWatchDog;
    bool m_LogRejected;
    bool m_LogRejectedWatchDog;
    bool m_LogSuccess;
    bool m_LogError;

public:
    explicit RCIServer(HMListService *hml, QObject *parent = nullptr);
    ~RCIServer();

public slots:
    void readSettings();
    void accept(qintptr handle, TCPRunnable *runnable);

};

} // namespace SDPO

#endif // RCISERVER_H
