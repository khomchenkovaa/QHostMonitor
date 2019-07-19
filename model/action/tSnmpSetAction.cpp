#include "tSnmpSetAction.h"
#include "netsnmpset.h"
#include "gData.h"

namespace SDPO {

/******************************************************************/

SnmpSetAction::SnmpSetAction(QObject *parent) :
    TestAction(parent)
{
     setAction(TActionID::SnmpSet);
}

/******************************************************************/

void SnmpSetAction::run(TTest *test)
{
    Q_UNUSED(test)
    SnmpProfile profile = GData::getSnmpProfile(a_SnmpProfile);
    NetSnmpSet snmpSet;
    snmpSet.setProfile(profile);
    snmpSet.setRetries(a_Retries);
    snmpSet.setHost(a_AgentAddress);
    SnmpValue value = snmpSet.set(a_Oid, a_SetValue);
}

/******************************************************************/

QStringList SnmpSetAction::description(bool isBad)
{
    SnmpProfile profile = GData::getSnmpProfile(a_SnmpProfile);
    QStringList result = TestAction::description(isBad);
    result.append(QString("Agent: %1").arg(a_AgentAddress));
    result.append(QString("Community: %1").arg(profile.community));
    result.append(QString("OID: %1").arg(a_Oid));
    result.append(QString("Value: %1").arg(a_SetValue));
    result.append(QString("Timeout: %1").arg(a_Timeout));
    result.append(QString("Retries: %1").arg(a_Retries));
    return result;
}

/******************************************************************/

TestAction *SnmpSetAction::clone()
{
    SnmpSetAction *result = new SnmpSetAction();
    copyProperties(result);
    result->setAgentAddress(a_AgentAddress);
    result->setTimeout(a_Timeout);
    result->setSnmpProfile(a_SnmpProfile);
    result->setRetries(a_Retries);
    result->setOid(a_Oid);
    result->setSetValue(a_SetValue);
    return result;
}

/******************************************************************/

} // namespace SDPO
