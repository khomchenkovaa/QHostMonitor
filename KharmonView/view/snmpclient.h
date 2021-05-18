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

    QList<SDPO::MibOid> objid_ModTableColumns;
    SDPO::MibOid objid_ModIndex;
    SDPO::MibOid objid_ModName;
    SDPO::MibOid objid_ModDesc;
    SDPO::MibOid objid_ModType;
    SDPO::MibOid objid_ModStatus;
    SDPO::MibOid objid_ModStatusDesc;
    SDPO::MibOid objid_ModLastChangeDate;
    SDPO::MibOid objid_ModURI;

    QList<SDPO::MibOid> objid_ParamTableColumns;
    SDPO::MibOid objid_ParamName;
    SDPO::MibOid objid_ParamDesc;
    SDPO::MibOid objid_ParamCurrValue;
    SDPO::MibOid objid_ParamCurrValueDesc;
    SDPO::MibOid objid_ParamType;
    SDPO::MibOid objid_ParamDataType;
    SDPO::MibOid objid_ParamUnits;
    SDPO::MibOid objid_ParamStatus;
    SDPO::MibOid objid_ParamLastChangeDate;
    SDPO::MibOid objid_ParamNormalValue;
    SDPO::MibOid objid_ParamLowFailLimit;
    SDPO::MibOid objid_ParamLowWarningLimit;
    SDPO::MibOid objid_ParamHighFailLimit;
    SDPO::MibOid objid_ParamHighWarningLimit;
    SDPO::MibOid objid_ParamModuleIndex;
};

} // namespace KharmonView

#endif // SNMPCLIENT_H
