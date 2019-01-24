#include "tExecuteExternalProgramAction.h"
#include "global/gMacroTranslator.h"
#include <QProcess>

namespace SDPO {

/******************************************************************/

ExecuteExternalProgramAction::ExecuteExternalProgramAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::ProgramExec);
}

/******************************************************************/

void ExecuteExternalProgramAction::run(TTest *test)
{
    Q_UNUSED(test)
    GMacroTranslator translator(a_CommandLine, test);
    QString command = translator.translate();
    QProcess::startDetached(command);
}

/******************************************************************/

QStringList ExecuteExternalProgramAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Command: %1").arg(a_CommandLine));
    result.append(QString("Window mode: %1").arg(a_WindowMode));
    return result;
}

/******************************************************************/

TestAction *ExecuteExternalProgramAction::clone()
{
    ExecuteExternalProgramAction *result = new ExecuteExternalProgramAction();
    copyProperties(result);
    result->setCommandLine(a_CommandLine);
    result->setWindowMode(a_WindowMode);
    return result;
}

/******************************************************************/

} // nmaespace SDPO
