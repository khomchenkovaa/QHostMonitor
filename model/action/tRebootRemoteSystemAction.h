#ifndef TREBOOTREMOTESYSTEMACTION_H
#define TREBOOTREMOTESYSTEMACTION_H

#include "tTestAction.h"

namespace SDPO {

class RebootRemoteSystemAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, ComputerName) // Computer Name
    AUTO_PROPERTY(QString, MessageToDisplay) // Message To Display
    AUTO_PROPERTY(int, TimeToDisplay) // Time to display
    AUTO_PROPERTY(QString, Method) // Method
    BOOL_PROPERTY(ForceProcesses) // Force processes to terminate

public:
    explicit RebootRemoteSystemAction(QObject *parent = 0);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TREBOOTREMOTESYSTEMACTION_H
