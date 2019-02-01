#include "tSnmpTrapAction.h"

namespace SDPO {

/******************************************************************/

SnmpTrapAction::SnmpTrapAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::SnmpTrap);
}

/******************************************************************/

void SnmpTrapAction::run(TTest *test)
{
    Q_UNUSED(test)
}

/******************************************************************/

QStringList SnmpTrapAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Target: %1").arg(a_DestAddress));
    result.append(QString("Community: %1").arg(a_Community));
    result.append(QString("Enterprise: %1").arg(a_Enterprise));
    result.append(QString("TrapType: %1").arg(a_TrapType));
    result.append(QString("Specific: %1").arg(a_Specific));
    result.append(QString("MibOID: %1").arg(a_MibOid));
    result.append(QString("MibValue: %1").arg(a_MibValue));
    result.append(QString("MibType: %1").arg(a_MibType));
    return result;
}

/******************************************************************/

TestAction *SnmpTrapAction::clone()
{
    SnmpTrapAction *result = new SnmpTrapAction();
    copyProperties(result);
    result->setDestAddress(a_DestAddress);
    result->setCommunity(a_Community);
    result->setAgentAddress(a_AgentAddress);
    result->setEnterprise(a_Enterprise);
    result->setTrapType(a_TrapType);
    result->setSpecific(a_Specific);
    result->setMibOid(a_MibOid);
    result->setMibValue(a_MibValue);
    result->setMibType(a_MibType);
    return result;
}

/******************************************************************/

} // namespace SDPO
