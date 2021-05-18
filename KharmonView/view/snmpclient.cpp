#include "snmpclient.h"

#include <QDebug>

using namespace KharmonView;

/*************************************************************/

SnmpClient::SnmpClient(QObject *parent) : QObject(parent)
{
    SDPO::NetSNMP::appName = "KharmonView";
    SDPO::NetSNMP::saveDescriptions = 0;
    SDPO::NetSNMP::initSnmp();

    objid_SysName            = SDPO::MibOid::parse("DIAG-MIB::sysName.0");
    objid_SysDesc            = SDPO::MibOid::parse("DIAG-MIB::sysDesc.0");
    objid_SysLocation        = SDPO::MibOid::parse("DIAG-MIB::sysLocation.0");
    objid_SysContact         = SDPO::MibOid::parse("DIAG-MIB::sysContact.0");
    objid_SysType            = SDPO::MibOid::parse("DIAG-MIB::sysType.0");
    objid_SysParentObjectURI = SDPO::MibOid::parse("DIAG-MIB::sysParentObjectURI.0");
    objid_StatStatus         = SDPO::MibOid::parse("DIAG-MIB::statStatus.0");
    objid_StatStatusDesc     = SDPO::MibOid::parse("DIAG-MIB::statStatusDesc.0");
    objid_StatLastChangeDate = SDPO::MibOid::parse("DIAG-MIB::statLastChangeDate.0");
    objid_ModCount           = SDPO::MibOid::parse("DIAG-MIB::modCount.0");
    objid_ParamCount         = SDPO::MibOid::parse("DIAG-MIB::paramCount.0");

    oids << objid_SysName
         << objid_SysDesc
         << objid_SysLocation
         << objid_SysContact
         << objid_SysType
         << objid_SysParentObjectURI
         << objid_StatStatus
         << objid_StatStatusDesc
         << objid_StatLastChangeDate
         << objid_ModCount
         << objid_ParamCount;

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

    snmpStatic(ss, snmpObject);
    snmpModules(ss, snmpObject);
    snmpParams(ss, snmpObject);

    qDebug() << "Object:" << snmpObject->getName()
             << "Received system:" << snmpObject->snmpSystem()->toString()
             << "status:" << snmpObject->snmpStatus()->toString()
             << "modules:" << snmpObject->snmpModList()->count()
             << "params:" << snmpObject->snmpParamList()->count();
}

/*************************************************************/

void SnmpClient::snmpStatic(SDPO::NetSnmpSession &ss, SnmpObject *snmpObject)
{
    SDPO::SnmpValueList valueList = ss.get(oids);
    foreach(const SDPO::SnmpValue &value, valueList) {
        if (objid_SysName.equals(value.name)) {
            snmpObject->snmpSystem()->sysName = value.val;
        }
        if (objid_SysDesc.equals(value.name)) {
            snmpObject->snmpSystem()->sysDescr = value.val;
            continue;
        }
        if (objid_SysLocation.equals(value.name)) {
            snmpObject->snmpSystem()->sysLocation = value.val;
            continue;
        }
        if (objid_SysContact.equals(value.name)) {
            snmpObject->snmpSystem()->sysContact = value.val;
            continue;
        }
        if (objid_SysType.equals(value.name)) {
            snmpObject->snmpSystem()->sysType = value.val.toInt();
            continue;
        }
        if (objid_SysParentObjectURI.equals(value.name)) {
            snmpObject->snmpSystem()->sysParentObjectURI = value.val;
            continue;
        }
        if (objid_StatStatus.equals(value.name)) {
            snmpObject->snmpStatus()->statStatus = value.val.toInt();
            continue;
        }
        if (objid_StatStatusDesc.equals(value.name)) {
            snmpObject->snmpStatus()->statStatusDesc = value.val;
            continue;
        }
        if (objid_StatLastChangeDate.equals(value.name)) {
            snmpObject->snmpStatus()->statLastChangeDate = value.val;
            continue;
        }
    }
}

/*************************************************************/

void SnmpClient::snmpModules(SDPO::NetSnmpSession &ss, SnmpObject *snmpObject)
{
    SDPO::SnmpValueTable modTable = ss.getTableRows(objid_ModTableColumns);
    snmpObject->snmpModList()->clear();
    foreach(const SDPO::SnmpValueList &row, modTable) {
        SnmpModule module;
        module.modIndex          = row.at(0).val.toLong();
        module.modName           = row.at(1).val;
        module.modDesc           = row.at(2).val;
        module.modType           = row.at(3).val.toInt();
        module.modStatus         = row.at(4).val.toInt();
        module.modStatusDesc     = row.at(5).val;
        module.modLastChangeDate = row.at(6).val;
        module.modURI            = row.at(7).val;
        snmpObject->snmpModList()->append(module);
    }
}

/*************************************************************/

void SnmpClient::snmpParams(SDPO::NetSnmpSession &ss, SnmpObject *snmpObject)
{
    SDPO::SnmpValueTable paramTable = ss.getTableRows(objid_ParamTableColumns);
    snmpObject->snmpParamList()->clear();
    foreach(const SDPO::SnmpValueList &row, paramTable) {
        SnmpParameter param;
        param.paramName             = row.at(0).val;
        param.paramDesc             = row.at(1).val;
        param.paramCurrValue        = row.at(2).val;
        param.paramCurrValueDesc    = row.at(3).val;
        param.paramType             = row.at(4).val.toInt();
        param.paramDataType         = row.at(5).val.toInt();
        param.paramUnits            = row.at(6).val;
        param.paramStatus           = row.at(7).val.toInt();
        param.paramLastChangeDate   = row.at(8).val;
        param.paramNormalValue      = row.at(9).val;
        param.paramLowFailLimit     = row.at(10).val;
        param.paramLowWarningLimit  = row.at(11).val;
        param.paramHighFailLimit    = row.at(12).val;
        param.paramHighWarningLimit = row.at(13).val;
        param.paramModuleIndex      = row.at(14).val.toInt();
        snmpObject->snmpParamList()->append(param);
    }
}

/*************************************************************/
