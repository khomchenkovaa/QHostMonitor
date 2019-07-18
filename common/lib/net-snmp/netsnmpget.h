#ifndef SDPO_SNMPGET_H
#define SDPO_SNMPGET_H

#include "snmp.h"

#include <QObject>

namespace SDPO {

class NetSnmpGet : public NetSnmpCommon
{
    Q_OBJECT
public:
    explicit NetSnmpGet(QObject *parent = nullptr);
    ~NetSnmpGet();

    SnmpValue get(const QString& oidStr);
    QList<SnmpValue> getNext(const QString &oidStr, int cnt=1);
    QList<SnmpValue> getRow(const QString &oidStr);
};

} // namespace SDPO

#endif // SDPO_SNMPGET_H
