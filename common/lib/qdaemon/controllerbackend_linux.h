#ifndef CONTROLLERBACKEND_LINUX_H
#define CONTROLLERBACKEND_LINUX_H

#include "qabstractdaemonbackend.h"

QT_BEGIN_NAMESPACE

class QDBusAbstractInterface;

namespace QtDaemon
{
    class ControllerBackendLinux : public QAbstractControllerBackend
    {
        Q_DISABLE_COPY(ControllerBackendLinux)

    public:
        ControllerBackendLinux(QCommandLineParser &, bool);

        bool start() Q_DECL_OVERRIDE;
        bool stop() Q_DECL_OVERRIDE;
        bool install() Q_DECL_OVERRIDE;
        bool uninstall() Q_DECL_OVERRIDE;
        DaemonStatus status() Q_DECL_OVERRIDE;

    private:
        QDBusAbstractInterface * getDBusInterface();

        const QCommandLineOption dbusPrefixOption;
        const QCommandLineOption initdPrefixOption;

        static const QString initdPrefix;
        static const QString dbusPrefix;
        static const QString defaultInitPath;
        static const QString defaultDBusPath;
    };
}

QT_END_NAMESPACE

#endif // CONTROLLERBACKEND_LINUX_H
