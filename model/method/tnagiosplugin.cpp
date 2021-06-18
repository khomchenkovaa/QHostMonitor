#include "tnagiosplugin.h"
#include <QProcess>

using namespace SDPO;

/******************************************************************/

TNagiosPlugin::TNagiosPlugin(QObject *parent)
    : TestMethod(TMethodID::Nagios, parent)
{

}

/******************************************************************/

QString TNagiosPlugin::getTestMethod() const
{
    return "Nagios Plugin";
}

/******************************************************************/

QString TNagiosPlugin::getTestedObjectInfo() const
{
    return "Nagios: " + a_NagiosPlugin;
}

/******************************************************************/

QString TNagiosPlugin::getObjectProperty() const
{
    return a_NagiosPlugin.mid(a_NagiosPlugin.lastIndexOf("/"));
}

/******************************************************************/

void TNagiosPlugin::run()
{
    m_Result.clear();
    writeLogTitle();

    QString command = getCommand();
    m_Log.append(QString("[Command]$ %1\n\n").arg(command));
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
    if(!process.waitForFinished(a_KillTimeout * 1000)) {
        m_Result.reply = getTestedObjectInfo() + " terminated";
        process.close();
        emit testFailed();
        return;
    }
    QString output = process.readAll();
    m_Log.append(output);
    m_Result.status = testStatusByExitCode(process.exitCode());
    parseResult(output.trimmed());

    emit testSuccess();
}

/******************************************************************/

QString TNagiosPlugin::getCommand() const
{
    return getNagiosPlugin() + " " + getArguments();
}

/******************************************************************/

TestMethod *TNagiosPlugin::clone()
{
    TNagiosPlugin *result = new TNagiosPlugin(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_NagiosPlugin = a_NagiosPlugin;
    result->b_KillPrg = b_KillPrg;
    result->a_KillTimeout = a_KillTimeout;
    return result;
}

/******************************************************************/

TestStatus TNagiosPlugin::testStatusByExitCode(const int exitCode)
{
    switch (exitCode) {
    case 0: // The plugin was able to check the service and it appeared to be functioning properly
        return TestStatus::Ok;
    case 1: // The plugin was able to check the service, but it appeared to be above some "warning" threshold or did not appear to be working properly
        return TestStatus::Warning;
    case 2: // The plugin detected that either the service was not running or it was above some "critical" threshold
        return TestStatus::Bad;
    case 3: // Invalid command line arguments were supplied to the plugin or low-level failures internal to the plugin that prevent it from performing the specified operation.
        return TestStatus::Unknown;
    }
    return TestStatus::Unknown;
}

/******************************************************************/
