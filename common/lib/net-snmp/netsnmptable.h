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

class NetSnmpTable : public NetSnmpCommon
{
    Q_OBJECT
public:
    explicit NetSnmpTable(QObject *parent = nullptr);
    ~NetSnmpTable();

    QList<SnmpColumn*> readColumns(const QString &oidStr);
    QList<QList<SnmpValue> > getTableEntries();

private:

    QList<SnmpColumn*> m_Columns;
    oid                m_Root[MAX_OID_LEN];
    size_t             m_RootLen = MAX_OID_LEN;
};

} // namespace SDPO

#endif // NETSNMPTABLE_H
