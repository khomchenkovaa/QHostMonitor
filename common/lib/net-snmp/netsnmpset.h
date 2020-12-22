#ifndef NETSNMPSET_H
#define NETSNMPSET_H

#include "netsnmpsession.h"

#include <QObject>

namespace SDPO {

class NetSnmpSet : public QObject
{
    Q_OBJECT

    NetSnmpSession *m_Session;

public:
    explicit NetSnmpSet(QObject *parent = nullptr);
    ~NetSnmpSet();

    SnmpValue set(const QString& oidStr, const QString& oidValue);

    void setDestHost(const QString& host = DEST_HOST_DEFAULT) {
        m_Session->setDestHost(host);
    }
    void setProfile(const SnmpProfile& profile) {
        m_Session->setProfile(profile);
    }
    void setRetries(const int retries) {
        m_Session->setRetries(retries);
    }
};

} // namespace SDPO

#endif // NETSNMPSET_H
