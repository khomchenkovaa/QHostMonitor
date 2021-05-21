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
    void snmpStatic(SDPO::NetSnmpSession &ss, SnmpObject *snmpObject, int &numMods, int &numParams);
    void snmpModules(SDPO::NetSnmpSession &ss, SnmpObject *snmpObject, int numMods);
    void snmpParams(SDPO::NetSnmpSession &ss, SnmpObject *snmpObject, int numParams);
    void setModuleInfo(SnmpModule &module, const SDPO::SnmpValueList &row);
    void setParameterInfo(SnmpParameter &param, const SDPO::SnmpValueList &row);
    void initOids();

private:
    QList<SDPO::MibOid> oids;
    QList<SDPO::MibOid> objid_ModTableColumns;
    QList<SDPO::MibOid> objid_ParamTableColumns;
};

} // namespace KharmonView

#endif // SNMPCLIENT_H