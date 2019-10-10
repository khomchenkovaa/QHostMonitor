#include "tRebootLocalMachineAction.h"

#include <QProcess>

namespace SDPO {

/******************************************************************/

RebootLocalMachineAction::RebootLocalMachineAction(QObject *parent) :
    TestAction(parent),
    a_ShutdownMethod(ST_LOGOUT)
{
    setAction(TActionID::RebootLocal);

}

/******************************************************************/

void RebootLocalMachineAction::run(TTest *test)
{
    Q_UNUSED(test)
    // NOTE RebootLocalMachineAction::run implementation
    QString cmd;
    switch(a_ShutdownMethod) {
    case ST_LOGOUT:
        cmd="[ '$(whoami)' != 'root' ] && killall -u $(whoami)";
        // cmd="logout";
        break;
    case ST_REBOOT:
        cmd="shutdown --reboot";
        break;
    case ST_SHUTDOWN:
        cmd="shutdown --halt";
        break;
    case ST_POWEROFF:
        cmd="shutdown --pweroff";
        break;
    }

    if (b_ForceProcesses && a_ShutdownMethod != ST_LOGOUT) {
        cmd.append(" now");
    }

    QProcess::startDetached(cmd);
}

/******************************************************************/

QStringList RebootLocalMachineAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Method: %1").arg(methodAsString()));
    result.append(QString("Force: %1").arg(b_ForceProcesses?"Yes":"No"));
    return result;
}

/******************************************************************/

TestAction *RebootLocalMachineAction::clone()
{
    RebootLocalMachineAction *result = new RebootLocalMachineAction();
    copyProperties(result);
    result->setShutdownMethod(a_ShutdownMethod);
    result->setForceProcesses(b_ForceProcesses);
    return result;
}

/******************************************************************/

QString RebootLocalMachineAction::methodAsString() const
{
    switch(a_ShutdownMethod) {
    case ST_LOGOUT:
        return "Logout";
    case ST_REBOOT:
        return "Reboot";
    case ST_SHUTDOWN:
        return "Shutdown";
    case ST_POWEROFF:
        return "PowerOff";
    }
    return QString();
}

/******************************************************************/

void RebootLocalMachineAction::setMethodFromString(const QString &method)
{
    if (method == "Logout") {
        a_ShutdownMethod = ST_LOGOUT;
    } else if (method == "Reboot") {
        a_ShutdownMethod = ST_REBOOT;
    } else if (method == "Shutdown") {
        a_ShutdownMethod = ST_SHUTDOWN;
    } else if (method == "PowerOff") {
        a_ShutdownMethod = ST_POWEROFF;
    }
}

/******************************************************************/

} // namespace SDPO
