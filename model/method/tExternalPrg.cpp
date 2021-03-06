#include "tExternalPrg.h"
#include <QProcess>

using namespace SDPO;

/******************************************************************/

TExternalPrg::TExternalPrg(QObject *parent) :
    TestMethod(TMethodID::Externalprg, parent)
{
    a_AlertMode = 3; // "is <> from"
    a_ExitCode = 0;
    b_KillPrg = false;
    a_KillTimeout = 60; // 60 sec.
}

/******************************************************************/

void TExternalPrg::run()
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
    QString res = process.readAll();
    m_Log.append(res);
    m_Result.status = testStatusByExitCode(process.exitCode());
    parseResult(res.trimmed());

    emit testSuccess();
}

/******************************************************************/

TestMethod *TExternalPrg::clone()
{
    TExternalPrg *result = new TExternalPrg(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_ExternalPrg = a_ExternalPrg;
    result->a_AlertMode = a_AlertMode;
    result->a_ExitCode = a_ExitCode;
    result->b_KillPrg = b_KillPrg;
    result->a_KillTimeout = a_KillTimeout;
    return result;
}

/******************************************************************/

QString TExternalPrg::getTestMethod() const
{
    return "External Prg";
}

/******************************************************************/

QString TExternalPrg::getTestedObjectInfo() const
{
    return "External: " + a_ExternalPrg;
}

/******************************************************************/

QString TExternalPrg::getObjectProperty() const
{
    return a_ExternalPrg.mid(a_ExternalPrg.lastIndexOf("/"));
}

/******************************************************************/

TestStatus TExternalPrg::testStatusByExitCode(const int exitCode)
{
    TestStatus result = TestStatus::Ok;
    switch (a_AlertMode) {
    case 0: // is < then
        if (a_ExitCode < exitCode) {
            result = TestStatus::Bad;
        }
        break;
    case 1: // is > then
        if (a_ExitCode > exitCode) {
            result = TestStatus::Bad;
        }
        break;
    case 2: // is = to
        if (a_ExitCode == exitCode) {
            result = TestStatus::Bad;
        }
        break;
    case 3: // is <> to
        if (a_ExitCode != exitCode) {
            result = TestStatus::Bad;
        }
        break;
    }
    return result;
}

/******************************************************************/

