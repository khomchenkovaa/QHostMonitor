#ifndef RCICONNECTION_H
#define RCICONNECTION_H

#include "servers/tcp/tcpconnection.h"
#include "hmScriptRunner.h"

namespace SDPO {

/**
 * \brief The Remote Contorl Interface Connection class
 * \details The RCI connection wraps the socket and performs operations
 */
class RCIConnection : public TCPConnection
{
    Q_OBJECT

    HMScriptRunner &m_HMScriptRunner;
public:
    explicit RCIConnection(HMListService *hml, QObject *parent = nullptr);
    ~RCIConnection();

protected:
    void readyRead();
};

} // namespace SDPO

#endif // RCICONNECTION_H
