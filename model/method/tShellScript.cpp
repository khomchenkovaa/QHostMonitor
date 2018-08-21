#include "tShellScript.h"
#include <QProcess>

namespace SDPO {

/******************************************************************/

TShellScript::TShellScript(QObject *parent) :
    TTestMethod(TMethodID::ShellScript, parent)
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
    clearResult();

    QString command = getCommand();
    if (command.isEmpty()) {
        m_ErrorString = "Command is empty";
        emit testFailed();
        return;
    }

//    qDebug() << getTestMethod() << ":" << command;

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(command);
    if (!process.waitForStarted()) {
        m_Reply = getTestedObjectInfo() + " can not start";
        process.close();
        emit testFailed();
        return;
    }
    if(!process.waitForFinished(a_Timeout * 1000)) {
        m_Reply = getTestedObjectInfo() + " terminated";
        process.close();
        emit testFailed();
        return;
    }
    if( process.exitStatus() == QProcess::NormalExit ) {
        parseResult(process.readAll().trimmed());
        emit testSuccess();
    } else {
        m_ErrorString = process.errorString();
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
    QString newReply = "No answer";
    float newReplyFloat = 0.0;
    int newReplyInt = 0;
    TestStatus newStatus = TestStatus::Unknown;
    // Result format: scriptres:<status>:<Reply>
    QStringList result = data.split(":");
    if (result.count() > 0) {
        if (result.at(0).compare("scriptres",Qt::CaseInsensitive)) {
            // not equals - bad contents
            newReply = result.at(0);
            newStatus = TestStatus::BadContents;
        } else {
            // equals - processing
            if (result.count() > 1) {
                // getting status: Host is alive, No answer, Unknown, Unknown host, Ok, Bad, Bad contents
                newStatus = TEnums::testStatusFromString(result.at(1));
            }
            if (result.count() > 2) {
                //! TODO parsing reply:
                // • decimal_number (like “123”, “0”, “6456.45”
                // • decimal_number + space + “Kb” (like “512 Kb”, “64 Kb”)
                // • decimal_number + space + “Mb” (like “1024 Mb”, “5 Mb”)
                // • decimal_number + space + “Gb” (like “12 Gb”, “4 Gb”)
                // • decimal_number + space + “%”   (like “50 %”, “99 %”)
                // • decimal_number + space + “ms” (like “100 ms”, “5400 ms”
                newReply = result.at(2);
                newReplyInt = newReply.mid(0,newReply.indexOf(' ')).toInt();
                newReplyFloat = newReply.mid(0,newReply.indexOf(' ')).toFloat();
            }
        }
    }

    m_Status = newStatus;
    m_Reply = newReply;
    m_ReplyDouble = newReplyFloat;
    m_ReplyInt = newReplyInt;
}

/******************************************************************/

TTestMethod *TShellScript::clone()
{
    TShellScript *result = new TShellScript(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
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
