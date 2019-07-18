#ifndef NETSNMPSET_H
#define NETSNMPSET_H

#include "snmp.h"

#include <QObject>

namespace SDPO {

class NetSnmpSet : public NetSnmpCommon
{
    Q_OBJECT
public:
    explicit NetSnmpSet(QObject *parent = nullptr);
    ~NetSnmpSet();

    SnmpValue set(const QString& oidStr, const QString& oidValue);
};

} // namespace SDPO

#endif // NETSNMPSET_H
