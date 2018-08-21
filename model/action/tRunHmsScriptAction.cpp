#include "tRunHmsScriptAction.h"

namespace SDPO {

/******************************************************************/

RunHmsScriptAction::RunHmsScriptAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::RunScript);
}

/******************************************************************/

void RunHmsScriptAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Action runs from ActionService
}

/******************************************************************/

QStringList RunHmsScriptAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("Script file: %1").arg(a_ScriptFile));
    return result;
}

/******************************************************************/

TestAction *RunHmsScriptAction::clone()
{
    RunHmsScriptAction *result = new RunHmsScriptAction();
    copyProperties(result);
    result->setScriptFile(a_ScriptFile);
    return result;
}

/******************************************************************/

} // namespace SDPO
