#include "snmpclient.h"

#include <QDebug>

enum DiagMibStatic {
    IDX_SYS_NAME = 0,
    IDX_SYS_DESC,
    IDX_SYS_LOCATION,
    IDX_SYS_CONTACT,
    IDX_SYS_TYPE,
    IDX_SYS_PARENT_OBJECT_URI,
    IDX_STAT_STATUS,
    IDX_STAT_STATUS_DESC,
    IDX_STAT_LAST_CHANGE_DATE,
    IDX_MOD_COUNT,
    IDX_PARAM_COUNT
};

enum DiagMibModules {
    IDX_MOD_INDEX = 0,
    IDX_MOD_NAME,
    IDX_MOD_DESC,
    IDX_MOD_TYPE,
    IDX_MOD_STATUS,
    IDX_MOD_STATUS_DESC,
    IDX_MOD_LAST_CHANGE_DATE,
    IDX_MOD_URI
};

enum DiagMibParamss {
    IDX_PARAM_NAME = 0,
    IDX_PARAM_DESC,
    IDX_PARAM_CURR_VALUE,
    IDX_PARAM_CURR_VALUE_DESC,
    IDX_PARAM_TYPE,
    IDX_PARAM_DATA_TYPE,
    IDX_PARAM_UNITS,
    IDX_PARAM_STATUS,
    IDX_PARAM_LAST_CHANGE_DATE,
    IDX_PARAM_NORMAL_VALUE,
    IDX_PARAM_LOW_FAIL_LIMIT,
    IDX_PARAM_LOW_WARNING_LIMIT,
    IDX_PARAM_HIGH_FAIL_LIMIT,
    IDX_PARAM_HIGH_WARNING_LIMIT,
    IDX_PARAM_MODULE_INDEX
};

using namespace KharmonView;

/*************************************************************/

SnmpClient::SnmpClient(QObject *parent) : QObject(parent)
{
    SDPO::NetSNMP::appName = "KharmonView";
    SDPO::NetSNMP::saveDescriptions = 0;
    SDPO::NetSNMP::initSnmp();
    initOids();
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

    int numMods = snmpObject->snmpModList()->size();
    int numParams = snmpObject->snmpParamList()->size();

    snmpStatic(ss, snmpObject, numMods, numParams);
    snmpModules(ss, snmpObject, numMods);
    snmpParams(ss, snmpObject, numParams);
}

/*************************************************************/

void SnmpClient::snmpStatic(SDPO::NetSnmpSession &ss, SnmpObject *snmpObject, int &numMods, int &numParams)
{
    SDPO::SnmpValueList valueList = ss.get(oids);
    foreach(const SDPO::SnmpValue &value, valueList) {
        if (oids.at(IDX_SYS_NAME).equals(value.name)) {
            snmpObject->snmpSystem()->sysName = value.val;
            continue;
        }
        if (oids.at(IDX_SYS_DESC).equals(value.name)) {
            snmpObject->snmpSystem()->sysDescr = value.val;
            continue;
        }
        if (oids.at(IDX_SYS_LOCATION).equals(value.name)) {
            snmpObject->snmpSystem()->sysLocation = value.val;
            continue;
        }
        if (oids.at(IDX_SYS_CONTACT).equals(value.name)) {
            snmpObject->snmpSystem()->sysContact = value.val;
            continue;
        }
        if (oids.at(IDX_SYS_TYPE).equals(value.name)) {
            snmpObject->snmpSystem()->sysType = value.val.toInt();
            continue;
        }
        if (oids.at(IDX_SYS_PARENT_OBJECT_URI).equals(value.name)) {
            snmpObject->snmpSystem()->sysParentObjectURI = value.val;
            continue;
        }
        if (oids.at(IDX_STAT_STATUS).equals(value.name)) {
            snmpObject->snmpStatus()->statStatus = value.val.toInt();
            continue;
        }
        if (oids.at(IDX_STAT_STATUS_DESC).equals(value.name)) {
            snmpObject->snmpStatus()->statStatusDesc = value.val;
            continue;
        }
        if (oids.at(IDX_STAT_LAST_CHANGE_DATE).equals(value.name)) {
            snmpObject->snmpStatus()->statLastChangeDate = value.val;
            continue;
        }
        if (oids.at(IDX_MOD_COUNT).equals(value.name)) {
            numMods = value.val.toInt();
            continue;
        }
        if (oids.at(IDX_PARAM_COUNT).equals(value.name)) {
            numParams = value.val.toInt();
            continue;
        }
    }
}

/*************************************************************/

void SnmpClient::snmpModules(SDPO::NetSnmpSession &ss, SnmpObject *snmpObject, int numMods)
{
    SDPO::SnmpValueTable modTable = ss.getTableRows(objid_ModTableColumns);
    if (numMods != snmpObject->snmpModList()->size()) {
        snmpObject->snmpModList()->clear();
        foreach(const SDPO::SnmpValueList &row, modTable) {
            SnmpModule module;
            setModuleInfo(module, row);
            snmpObject->snmpModList()->append(module);
        }
    } else {
        for (int i=0; i < modTable.size(); ++i) {
            SnmpModule module;
            setModuleInfo(module, modTable.at(i));
            snmpObject->snmpModList()->replace(i, module);
        }
    }
}

/*************************************************************/

void SnmpClient::snmpParams(SDPO::NetSnmpSession &ss, SnmpObject *snmpObject, int numParams)
{
    SDPO::SnmpValueTable paramTable = ss.getTableRows(objid_ParamTableColumns);
    if (numParams != snmpObject->snmpParamList()->size()) {
        snmpObject->snmpParamList()->clear();
        foreach(const SDPO::SnmpValueList &row, paramTable) {
            SnmpParameter param;
            setParameterInfo(param, row);
            snmpObject->snmpParamList()->append(param);
        }
    } else {
        for (int i=0; i < paramTable.size(); ++i) {
            SnmpParameter param;
            setParameterInfo(param, paramTable.at(i));
            snmpObject->snmpParamList()->replace(i, param);
        }
    }
}

/*************************************************************/

void SnmpClient::setModuleInfo(SnmpModule &module, const SDPO::SnmpValueList &row)
{
    module.modIndex          = row.at(IDX_MOD_INDEX).val.toLong();
    module.modName           = row.at(IDX_MOD_NAME).val;
    module.modDesc           = row.at(IDX_MOD_DESC).val;
    module.modType           = row.at(IDX_MOD_TYPE).val.toInt();
    module.modStatus         = row.at(IDX_MOD_STATUS).val.toInt();
    module.modStatusDesc     = row.at(IDX_MOD_STATUS_DESC).val;
    module.modLastChangeDate = row.at(IDX_MOD_LAST_CHANGE_DATE).val;
    module.modURI            = row.at(IDX_MOD_URI).val;
}

/*************************************************************/

void SnmpClient::setParameterInfo(SnmpParameter &param, const SDPO::SnmpValueList &row)
{
    param.paramName             = row.at(IDX_PARAM_NAME).val;
    param.paramDesc             = row.at(IDX_PARAM_DESC).val;
    param.paramCurrValue        = row.at(IDX_PARAM_CURR_VALUE).val;
    param.paramCurrValueDesc    = row.at(IDX_PARAM_CURR_VALUE_DESC).val;
    param.paramType             = row.at(IDX_PARAM_TYPE).val.toInt();
    param.paramDataType         = row.at(IDX_PARAM_DATA_TYPE).val.toInt();
    param.paramUnits            = row.at(IDX_PARAM_UNITS).val;
    param.paramStatus           = row.at(IDX_PARAM_STATUS).val.toInt();
    param.paramLastChangeDate   = row.at(IDX_PARAM_LAST_CHANGE_DATE).val;
    param.paramNormalValue      = row.at(IDX_PARAM_NORMAL_VALUE).val;
    param.paramLowFailLimit     = row.at(IDX_PARAM_LOW_FAIL_LIMIT).val;
    param.paramLowWarningLimit  = row.at(IDX_PARAM_LOW_WARNING_LIMIT).val;
    param.paramHighFailLimit    = row.at(IDX_PARAM_HIGH_FAIL_LIMIT).val;
    param.paramHighWarningLimit = row.at(IDX_PARAM_HIGH_WARNING_LIMIT).val;
    param.paramModuleIndex      = row.at(IDX_PARAM_MODULE_INDEX).val.toInt();
}

/*************************************************************/

void SnmpClient::initOids()
{
    oids << SDPO::MibOid::parse("DIAG-MIB::sysName.0")
         << SDPO::MibOid::parse("DIAG-MIB::sysDesc.0")
         << SDPO::MibOid::parse("DIAG-MIB::sysLocation.0")
         << SDPO::MibOid::parse("DIAG-MIB::sysContact.0")
         << SDPO::MibOid::parse("DIAG-MIB::sysType.0")
         << SDPO::MibOid::parse("DIAG-MIB::sysParentObjectURI.0")
         << SDPO::MibOid::parse("DIAG-MIB::statStatus.0")
         << SDPO::MibOid::parse("DIAG-MIB::statStatusDesc.0")
         << SDPO::MibOid::parse("DIAG-MIB::statLastChangeDate.0")
         << SDPO::MibOid::parse("DIAG-MIB::modCount.0")
         << SDPO::MibOid::parse("DIAG-MIB::paramCount.0");

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
