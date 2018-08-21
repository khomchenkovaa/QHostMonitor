#include "tSnmpSetAction.h"

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
}

/******************************************************************/

QStringList SnmpSetAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Agent: %1").arg(a_AgentAddress));
    result.append(QString("Community: %1").arg(a_Community));
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
    result->setCommunity(a_Community);
    result->setRetries(a_Retries);
    result->setOid(a_Oid);
    result->setSetValue(a_SetValue);
    return result;
}

/******************************************************************/

} // namespace SDPO
