#include "tShellScript.h"
#include <QProcess>

namespace SDPO {

/******************************************************************/

TShellScript::TShellScript(QObject *parent) :
    TestMethod(TMethodID::ShellScript, parent)
{
    a_Name = QString();
    a_Platform = "Linux";
    a_StartCmd = "%Script% %Params%";
    a_Script = QString("#!/bin/sh\necho ScriptRes:Ok:0\n");
    a_FileName = "/bin/echo";
}

/******************************************************************/

void TShellScript::run()
{
    m_Result.clear();

    QString command = getCommand();
    if (command.isEmpty()) {
        m_Result.error = "Command is empty";
        emit testFailed();
        return;
    }

//    qDebug() << getTestMethod() << ":" << command;

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(command);
    if (!process.waitForStarted()) {
        m_Result.reply = getTestedObjectInfo() + " can not start";
        process.close();
        emit testFailed();
        return;
    }
    if(!process.waitForFinished(a_Timeout * 1000)) {
        m_Result.reply = getTestedObjectInfo() + " terminated";
        process.close();
        emit testFailed();
        return;
    }
    if( process.exitStatus() == QProcess::NormalExit ) {
        parseResult(process.readAll().trimmed());
        emit testSuccess();
    } else {
        m_Result.error = process.errorString();
        emit testFailed();
    }
}

/******************************************************************/

QString TShellScript::getCommand() const
{
    QString command = a_StartCmd;
    command.replace("%Script%",a_FileName,Qt::CaseInsensitive).replace("%Params%", a_Params, Qt::CaseInsensitive);
    return command;
}

/******************************************************************/

void TShellScript::parseResult(QString data)
{
    TTestResult tResult;
    tResult.reply = "No answer";

    // Result format: scriptres:<status>:<Reply>
    QStringList result = data.split(":");
    if (result.count() > 0) {
        if (result.at(0).compare("scriptres",Qt::CaseInsensitive)) {
            // not equals - bad contents
            tResult.reply = result.at(0);
            tResult.status = TestStatus::BadContents;
        } else {
            // equals - processing
            if (result.count() > 1) {
                // getting status: Host is alive, No answer, Unknown, Unknown host, Ok, Bad, Bad contents
                tResult.status = TEnums::testStatusFromString(result.at(1));
            }
            if (result.count() > 2) {
                //! TODO parsing reply:
                // • decimal_number (like “123”, “0”, “6456.45”
                // • decimal_number + space + “Kb” (like “512 Kb”, “64 Kb”)
                // • decimal_number + space + “Mb” (like “1024 Mb”, “5 Mb”)
                // • decimal_number + space + “Gb” (like “12 Gb”, “4 Gb”)
                // • decimal_number + space + “%”   (like “50 %”, “99 %”)
                // • decimal_number + space + “ms” (like “100 ms”, “5400 ms”
                tResult.reply = result.at(2);
                tResult.replyInt = tResult.reply.mid(0,tResult.reply.indexOf(' ')).toInt();
                tResult.replyDouble = tResult.reply.mid(0,tResult.reply.indexOf(' ')).toDouble();
            }
        }
    }

    m_Result = tResult;
}

/******************************************************************/

TestMethod *TShellScript::clone()
{
    TShellScript *result = new TShellScript(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Name = a_Name;
    result->a_Platform = a_Platform;
    result->a_StartCmd = a_StartCmd;
    result->a_Script = a_Script;
    result->a_FileName = a_FileName;
    result->a_Params = a_Params;
    result->a_Timeout = a_Timeout;
    result->b_TranslateMacros = b_TranslateMacros;
    return result;
}

/******************************************************************/

QString TShellScript::getTestMethod() const
{
    return "Shell Script";
}

/******************************************************************/

QString TShellScript::getTestedObjectInfo() const
{
    return "Shell Script: " + a_Name + " " + a_Params;
}

/******************************************************************/

QString TShellScript::getParam(const int i) const
{
    QStringList params = a_Params.split(" ");
    if (params.count() > i) {
        return params.at(i);
    }
    return QString();
}

/******************************************************************/

} // namespace SDPO
