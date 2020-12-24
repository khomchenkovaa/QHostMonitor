#ifndef NETSNMPTABLE_H
#define NETSNMPTABLE_H

#include "netsnmpsession.h"

namespace SDPO {

class NetSnmpTable : public QObject
{
    Q_OBJECT

    NetSnmpSession    *m_Session;

public:
    explicit NetSnmpTable(QObject *parent = nullptr);
    ~NetSnmpTable();

    QList<SnmpColumn*> readColumns(const QString &oidStr);
    QList<QList<SnmpValue> > getTableEntries();

    void setDestHost(const QString& host = DEST_HOST_DEFAULT) {
        m_Session->setDestHost(host);
    }
    void setProfile(const SnmpProfile& profile) {
        m_Session->setProfile(profile);
    }
    void setRetries(const int retries) {
        m_Session->setRetries(retries);
    }
private:
    QList<SnmpColumn*> m_Columns;
    oid                m_Root[MAX_OID_LEN];
    size_t             m_RootLen = MAX_OID_LEN;
};

} // namespace SDPO

#endif // NETSNMPTABLE_H
