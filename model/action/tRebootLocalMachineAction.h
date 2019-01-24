#ifndef TREBOOTLOCALMACHINEACTION_H
#define TREBOOTLOCALMACHINEACTION_H

#include "tTestAction.h"

namespace SDPO {

class RebootLocalMachineAction : public TestAction
{
    Q_OBJECT

    BOOL_PROPERTY(Logout) // Logout
    BOOL_PROPERTY(Reboot) // Reboot
    BOOL_PROPERTY(Shutdown) // Shutdown
    BOOL_PROPERTY(PowerOff) // PowerOff
    BOOL_PROPERTY(ForceProcesses) // Force processes to terminate

public:
    explicit RebootLocalMachineAction(QObject *parent = 0);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TREBOOTLOCALMACHINEACTION_H
