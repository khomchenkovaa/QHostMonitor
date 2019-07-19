#ifndef TSNMPSETACTION_H
#define TSNMPSETACTION_H

#include "tTestAction.h"

namespace SDPO {

class SnmpSetAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, AgentAddress) // Agent address
    AUTO_PROPERTY(int, Timeout) // Timeout
    AUTO_PROPERTY(QString, SnmpProfile) // Community
    AUTO_PROPERTY(int, Retries) // Retries
    AUTO_PROPERTY(QString, Oid) // OID
    AUTO_PROPERTY(QString, SetValue) // Set value

public:
    explicit SnmpSetAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TSNMPSETACTION_H
