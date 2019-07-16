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

    void setPeername(const QString& host);
    void setVersion(SnmpVersion version);
    void setCommunity(const QString& community);
    void setTimeout(const int timeout);
    void setRetries(const int retries);

    bool getColumns(const QString &oidStr);

    QStringList getTableEntries();



private:
    SnmpSession        session, *ss;
    SnmpPdu           *pdu;
    QList<SnmpColumn*> columns;
    oid                root[MAX_OID_LEN];
    size_t             rootlen = MAX_OID_LEN;
};

} // namespace SDPO

#endif // NETSNMPTABLE_H
