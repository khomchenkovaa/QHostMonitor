#ifndef SDPO_SNMPGET_H
#define SDPO_SNMPGET_H

#include "snmp.h"

#include <QObject>

namespace SDPO {

class NetSnmpGet : public QObject
{
    Q_OBJECT
public:
    explicit NetSnmpGet(QObject *parent = nullptr);
    ~NetSnmpGet();

    void setPeername(const QString& host);
    void setVersion(SnmpVersion version);
    void setCommunity(const QString& community);
    void setTimeout(const int timeout);
    void setRetries(const int retries);

    SnmpValue get(const QString& oidStr);
    QList<SnmpValue> getNext(const QString &oidStr, int cnt=1);
    QList<SnmpValue> getRow(const QString &oidStr);

private:
    SnmpSession session, *ss;

};

} // namespace SDPO

#endif // SDPO_SNMPGET_H
