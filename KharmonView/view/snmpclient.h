#ifndef SNMPCLIENT_H
#define SNMPCLIENT_H

#include "snmpobject.h"
#include "netsnmpsession.h"

#include <QObject>

namespace KharmonView {

class SnmpClient : public QObject
{
    Q_OBJECT
public:
    explicit SnmpClient(QObject *parent = nullptr);

public slots:
    void snmpRun(SnmpObject *snmpObject);

private:
    void snmpStatic(SDPO::NetSnmpSession &ss, SnmpObject *snmpObject);
    void snmpModules(SDPO::NetSnmpSession &ss, SnmpObject *snmpObject);
    void snmpParams(SDPO::NetSnmpSession &ss, SnmpObject *snmpObject);

private:
    SDPO::MibOid objid_SysName;
    SDPO::MibOid objid_SysDesc;
    SDPO::MibOid objid_SysLocation;
    SDPO::MibOid objid_SysContact;
    SDPO::MibOid objid_SysType;
    SDPO::MibOid objid_SysParentObjectURI;
    SDPO::MibOid objid_StatStatus;
    SDPO::MibOid objid_StatStatusDesc;
    SDPO::MibOid objid_StatLastChangeDate;
    SDPO::MibOid objid_ModCount;
    SDPO::MibOid objid_ParamCount;

    QList<SDPO::MibOid> oids;
    QList<SDPO::MibOid> objid_ModTableColumns;
    QList<SDPO::MibOid> objid_ParamTableColumns;
};

} // namespace KharmonView

#endif // SNMPCLIENT_H
