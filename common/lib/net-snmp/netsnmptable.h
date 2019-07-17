#ifndef NETSNMPTABLE_H
#define NETSNMPTABLE_H

#include "snmp.h"

#include <QObject>

namespace SDPO {

struct SnmpColumn {
    oid     subid;
    QString label;
    QString fmt;
};

class NetSnmpTable : public QObject
{
    Q_OBJECT
public:
    explicit NetSnmpTable(QObject *parent = nullptr);
    ~NetSnmpTable();

    void setHost(const QString& host);
    void setProfile(const SnmpProfile& profile);
    void setTimeout(const int timeout);
    void setRetries(const int retries);

    QList<SnmpColumn*> readColumns(const QString &oidStr);

    QList<QList<SnmpValue> > getTableEntries();

private:
    void snmpSessionInit(SnmpSession *session);
    void snmpSessionLogError(int priority, const QString& prog, SnmpSession *ss);

private:
    QString            m_Host;
    SnmpVersion        m_Version;
    QString            m_Community;
    int                m_Timeout;
    int                m_Retries;
    QList<SnmpColumn*> m_Columns;
    oid                m_Root[MAX_OID_LEN];
    size_t             m_RootLen = MAX_OID_LEN;
};

} // namespace SDPO

#endif // NETSNMPTABLE_H
