#ifndef TREBOOTLOCALMACHINEACTION_H
#define TREBOOTLOCALMACHINEACTION_H

#include "tTestAction.h"

namespace SDPO {

class RebootLocalMachineAction : public TestAction
{
    Q_OBJECT

public:
    enum SDType { ST_LOGOUT, ST_REBOOT, ST_SHUTDOWN, ST_POWEROFF };

private:
    AUTO_PROPERTY(SDType, ShutdownMethod)
    BOOL_PROPERTY(ForceProcesses) // Force processes to terminate

public:
    explicit RebootLocalMachineAction(QObject *parent = nullptr);
    virtual ~RebootLocalMachineAction() {}

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();
    QString methodAsString() const;
    void setMethodFromString(const QString& method);
};

} // namespace SDPO

#endif // TREBOOTLOCALMACHINEACTION_H
