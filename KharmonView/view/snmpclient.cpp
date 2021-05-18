#include "snmpclient.h"

#include <QDebug>

using namespace KharmonView;

/*************************************************************/

SnmpClient::SnmpClient(QObject *parent) : QObject(parent)
{
    SDPO::NetSNMP::appName = "KharmonView";
    SDPO::NetSNMP::saveDescriptions = 0;
    SDPO::NetSNMP::initSnmp();

    objid_SysName = SDPO::MibOid::parse("DIAG-MIB::sysName.0");
    objid_SysDesc = SDPO::MibOid::parse("DIAG-MIB::sysDesc.0");
    objid_SysLocation = SDPO::MibOid::parse("DIAG-MIB::sysLocation.0");
    objid_SysContact = SDPO::MibOid::parse("DIAG-MIB::sysContact.0");
    objid_SysType = SDPO::MibOid::parse("DIAG-MIB::sysType.0");
    objid_SysParentObjectURI = SDPO::MibOid::parse("DIAG-MIB::sysParentObjectURI.0");
    objid_StatStatus = SDPO::MibOid::parse("DIAG-MIB::statStatus.0");
    objid_StatStatusDesc = SDPO::MibOid::parse("DIAG-MIB::statStatusDesc.0");
    objid_StatLastChangeDate = SDPO::MibOid::parse("DIAG-MIB::statLastChangeDate.0");
    objid_ModCount = SDPO::MibOid::parse("DIAG-MIB::modCount.0");
    objid_ParamCount = SDPO::MibOid::parse("DIAG-MIB::paramCount.0");

    objid_ModTableColumns
        << SDPO::MibOid::parse("DIAG-MIB::modIndex")
        << SDPO::MibOid::parse("DIAG-MIB::modName")
        << SDPO::MibOid::parse("DIAG-MIB::modDesc")
        << SDPO::MibOid::parse("DIAG-MIB::modType")
        << SDPO::MibOid::parse("DIAG-MIB::modStatus")
        << SDPO::MibOid::parse("DIAG-MIB::modStatusDesc")
        << SDPO::MibOid::parse("DIAG-MIB::modLastChangeDate")
        << SDPO::MibOid::parse("DIAG-MIB::modURI");

    objid_ParamTableColumns
        << SDPO::MibOid::parse("DIAG-MIB::paramName")
        << SDPO::MibOid::parse("DIAG-MIB::paramDesc")
        << SDPO::MibOid::parse("DIAG-MIB::paramCurrValue")
        << SDPO::MibOid::parse("DIAG-MIB::paramCurrValueDesc")
        << SDPO::MibOid::parse("DIAG-MIB::paramType")
        << SDPO::MibOid::parse("DIAG-MIB::paramDataType")
        << SDPO::MibOid::parse("DIAG-MIB::paramUnits")
        << SDPO::MibOid::parse("DIAG-MIB::paramStatus")
        << SDPO::MibOid::parse("DIAG-MIB::paramLastChangeDate")
        << SDPO::MibOid::parse("DIAG-MIB::paramNormalValue")
        << SDPO::MibOid::parse("DIAG-MIB::paramLowFailLimit")
        << SDPO::MibOid::parse("DIAG-MIB::paramLowWarningLimit")
        << SDPO::MibOid::parse("DIAG-MIB::paramHighFailLimit")
        << SDPO::MibOid::parse("DIAG-MIB::paramHighWarningLimit")
        << SDPO::MibOid::parse("DIAG-MIB::paramModuleIndex");
}

/*************************************************************/

void SnmpClient::snmpRun(SnmpObject *snmpObject)
{
    QString cmd = QString("snmpwalk -v %1 -c %2 %3 -t %4 -r %5 DIAG-MIB::diagMIB")
                      .arg(snmpObject->getVersionStr(),
                           snmpObject->getCommunity(),
                           snmpObject->getDestHost(),
                           QString::number(snmpObject->getTimeout()),
                           QString::number(snmpObject->getRetries()));

    qDebug() << "Object:" << snmpObject->getName() << "$" << cmd;

    SDPO::NetSnmpSession ss;
    ss.setVersion(snmpObject->getVersion());
    ss.setCommunity(snmpObject->getCommunity());
    ss.setDestHost(snmpObject->getDestHost());
    ss.setTimeoutSec(snmpObject->getTimeout());
    ss.setRetries(snmpObject->getRetries());

    QList<SDPO::MibOid> oids;
    oids.append(objid_SysName);
    oids.append(objid_SysDesc);
    oids.append(objid_SysLocation);
    oids.append(objid_SysContact);
    oids.append(objid_SysType);
    oids.append(objid_SysParentObjectURI);
    oids.append(objid_StatStatus);
    oids.append(objid_StatStatusDesc);
    oids.append(objid_StatLastChangeDate);
    oids.append(objid_ModCount);
    oids.append(objid_ParamCount);

    SDPO::SnmpValueList valueList = ss.get(oids);
    SDPO::SnmpValueTable modTable = ss.getTableRows(objid_ModTableColumns);
    SDPO::SnmpValueTable paramTable = ss.getTableRows(objid_ParamTableColumns);

    qDebug() << "Object:" << snmpObject->getName()
             << "Received values:" << valueList.count()
             << "modules:" << modTable.count()
             << "params:" << paramTable.count();
}

/*************************************************************/
