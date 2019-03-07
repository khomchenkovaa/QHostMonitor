#include "qabstractdaemonbackend.h"
#include "qdaemonapplication.h"
#include "qdaemonlog.h"

#include <QtCore/qcommandlineparser.h>

QT_BEGIN_NAMESPACE

using namespace QtDaemon;

/******************************************************************/

const int QAbstractDaemonBackend::BackendFailed = -1;

/******************************************************************/

QAbstractDaemonBackend::QAbstractDaemonBackend(QCommandLineParser & prsr)
    : parser(prsr)
{
}

/******************************************************************/

QAbstractDaemonBackend::~QAbstractDaemonBackend()
{
}

/******************************************************************/

QAbstractControllerBackend::QAbstractControllerBackend(QCommandLineParser & parser, bool aq)
    : QAbstractDaemonBackend(parser), autoQuit(aq),
      installOption(QStringList() << QStringLiteral("i") << QStringLiteral("install"), QCoreApplication::translate("main", "Install the daemon")),
      uninstallOption(QStringList() << QStringLiteral("u") << QStringLiteral("uninstall"), QCoreApplication::translate("main", "Uninstall the daemon")),
      startOption(QStringList() << QStringLiteral("s") << QStringLiteral("start"), QCoreApplication::translate("main", "Start the daemon")),
      stopOption(QStringList() << QStringLiteral("t") << QStringLiteral("stop"), QCoreApplication::translate("main", "Stop the daemon")),
      statusOption(QStringList() << QStringLiteral("status"), QCoreApplication::translate("main", "Check the daemon status")),
      fakeOption(QStringLiteral("fake"), QCoreApplication::translate("main", "Run the daemon in fake mode (for debugging)."))
{
    parser.addOption(installOption);
    parser.addOption(uninstallOption);
    parser.addOption(startOption);
    parser.addOption(stopOption);
    parser.addOption(statusOption);
    parser.addOption(fakeOption);
    parser.addHelpOption();
}

/******************************************************************/

int QAbstractControllerBackend::exec()
{
    bool result = true;
    if (parser.isSet(startOption))
        result = start();
    else if (parser.isSet(stopOption))
        result = stop();
    else if (parser.isSet(installOption))
        result = install();
    else if (parser.isSet(uninstallOption))
        result = uninstall();
    else if (parser.isSet(statusOption))  {
        qDaemonLog() << (status() == RunningStatus ? QCoreApplication::translate("main", "Daemon is running.") : QCoreApplication::translate("main", "Daemon is not running or it's not responding."));
    }
    else if (parser.isSet(fakeOption))  {
        autoQuit = false;	// Enforce not quitting

        QStringList arguments = parser.positionalArguments();
        arguments.prepend(QDaemonApplication::applicationFilePath());

        QMetaObject::invokeMethod(qApp, "daemonized", Qt::QueuedConnection, Q_ARG(QStringList, arguments));
    }
    else  {		// Everything else + the help option, show help and enforce quit
        qDaemonLog() << parser.helpText();
        return 0;
    }

    if (!result)
        return BackendFailed;

    if (autoQuit)
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);

    return QCoreApplication::exec();
}

/******************************************************************/

QT_END_NAMESPACE
