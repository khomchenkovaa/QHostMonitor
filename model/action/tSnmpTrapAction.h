#ifndef TSNMPTRAPACTION_H
#define TSNMPTRAPACTION_H

#include "tTestAction.h"

namespace SDPO {

class SnmpTrapAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, DestAddress) // Dest address
    AUTO_PROPERTY(QString, Community) // Community
    AUTO_PROPERTY(QString, AgentAddress) // Agent address
    AUTO_PROPERTY(QString, Enterprise) // Enterprise
    AUTO_PROPERTY(QString, TrapType) // Trap type
    AUTO_PROPERTY(int, Specific) // Specific
    AUTO_PROPERTY(QString, MibOid) // MIB OID
    AUTO_PROPERTY(QString, MibValue) // MIB value
    AUTO_PROPERTY(QString, MibType) // MIB type

public:
    explicit SnmpTrapAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespacae SDPO

#endif // TSNMPTRAPACTION_H
