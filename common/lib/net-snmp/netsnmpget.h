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

    void setHost(const QString& host);
    void setProfile(const SnmpProfile& profile);
    void setTimeout(const int timeout);
    void setRetries(const int retries);

    SnmpValue get(const QString& oidStr);
    QList<SnmpValue> getNext(const QString &oidStr, int cnt=1);
    QList<SnmpValue> getRow(const QString &oidStr);

private:
    void snmpSessionInit(SnmpSession *session);
    void snmpSessionLogError(int priority, const QString& prog, SnmpSession *ss);

private:
    QString     m_Host;
    SnmpVersion m_Version;
    QString     m_Community;
    int         m_Timeout;
    int         m_Retries;

};

} // namespace SDPO

#endif // SDPO_SNMPGET_H
