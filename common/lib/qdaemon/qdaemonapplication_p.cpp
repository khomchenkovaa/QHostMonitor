#include "qdaemonapplication_p.h"
#include "qdaemonapplication.h"
#include "qdaemonlog_p.h"

#include <csignal>

#include "daemonbackend_linux.h"
#include "controllerbackend_linux.h"

QT_BEGIN_NAMESPACE

using namespace QtDaemon;

typedef DaemonBackendLinux DaemonBackend;
typedef ControllerBackendLinux ControllerBackend;

QString QDaemonApplicationPrivate::description;

QDaemonApplicationPrivate::QDaemonApplicationPrivate(QDaemonApplication * q)
    : q_ptr(q), log(*new QDaemonLogPrivate), autoQuit(true)
{
    std::signal(SIGTERM, QDaemonApplicationPrivate::processSignalHandler);
    std::signal(SIGINT, QDaemonApplicationPrivate::processSignalHandler);
    std::signal(SIGSEGV, QDaemonApplicationPrivate::processSignalHandler);
}

QDaemonApplicationPrivate::~QDaemonApplicationPrivate()
{
}

void QDaemonApplicationPrivate::processSignalHandler(int signalNumber)
{
    switch (signalNumber)
    {
    case SIGSEGV:
       ::exit(-1);
    case SIGTERM:
    case SIGINT:
        {
            QDaemonApplication * app = QDaemonApplication::instance();
            if (app)
                app->quit();
            else
                ::exit(-1);
        }
        break;
    default:
        return;
    }
}

QAbstractDaemonBackend * QDaemonApplicationPrivate::createBackend(bool isDaemon)
{
    if (isDaemon)  {
        log.setLogType(QDaemonLog::LogToFile);
        return new DaemonBackend(parser);
    }
    else
        return new ControllerBackend(parser, autoQuit);
}

QT_END_NAMESPACE
