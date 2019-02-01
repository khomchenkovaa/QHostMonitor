#include "mShellScript.h"
#include <QDate>

namespace SDPO {

/******************************************************************/

ShellScript::ShellScript(QObject *parent) :
    QObject(parent)
{
    loadDefaults();
}

/******************************************************************/

void ShellScript::loadDefaults()
{
    a_Name = QString();
    a_Hint = QString();
    a_Developer = QString();
    a_Platform = "Linux";
    a_Version = 1.0;
    a_Date = QDate::currentDate();
    a_StartCmd = "%Script% %Params%";
    a_Script = QString("#!/bin/sh\necho ScriptRes:Ok:0\n");
    a_Comment = QString();
    a_History = QString();
    a_FileName = QString();
}

/******************************************************************/

} // namespace SDPO
