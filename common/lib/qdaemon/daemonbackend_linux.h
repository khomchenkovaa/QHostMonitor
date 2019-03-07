#ifndef DAEMONBACKEND_LINUX_H
#define DAEMONBACKEND_LINUX_H

#include "qabstractdaemonbackend.h"

#include <QObject>

#define Q_DAEMON_DBUS_CONTROL_INTERFACE "io.qt.QtDaemon.Control"

QT_BEGIN_NAMESPACE

namespace QtDaemon
{
    class DaemonBackendLinux : public QObject, public QAbstractDaemonBackend
    {
        Q_OBJECT
        Q_DISABLE_COPY(DaemonBackendLinux)
        Q_CLASSINFO("D-Bus Interface", Q_DAEMON_DBUS_CONTROL_INTERFACE)

    public:
        DaemonBackendLinux(QCommandLineParser &);
        ~DaemonBackendLinux() Q_DECL_OVERRIDE;

        int exec() Q_DECL_OVERRIDE;

        Q_INVOKABLE bool isRunning();
        Q_INVOKABLE bool stop();

        static QString serviceName();
    };
}

QT_END_NAMESPACE

#endif // DAEMONBACKEND_LINUX_H
