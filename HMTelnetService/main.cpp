/*
#include "hmTelnetInteractiveService.h"
#include <QDir>
#include <QSettings>

int main(int argc, char *argv[])
{
#if !defined(Q_OS_WIN)
    // QtService stores service settings in SystemScope, which normally require root privileges.
    // To allow testing this example as non-root, we change the directory of the SystemScope settings file.
    QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, QDir::tempPath());
    qWarning("(Example uses dummy settings file: %s/QtSoftware.conf)", QDir::tempPath().toLatin1().constData());
#endif
    SDPO::HMTelnetInteractiveService service(argc, argv);
    return service.exec();
}
*/

#include <QtWidgets/QApplication>
#include <QStyleFactory>
#include "tcpserver/tcpserver.h"

#include "qdaemonapplication.h"
#include "hmTelnetServiceDialog.h"

#define ORGANIZATION_NAME   "SNIIP"
#define ORGANIZATION_DOMAIN "sniip.ru"
#define APPLICATION_NAME    "HMTelnetService"
#define APPLICATION_DESCR   "This application works like Telnet server and allows to control HostMonitor remotely using any telnet client."

int main(int argc, char ** argv)
{
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);

    bool startAsDaemon = true;
    for(int i=0; i<argc; i++) {
        QString arg = argv[i];
        if (!arg.compare("--gui")) {
            startAsDaemon = false;
        }
    }

    if (startAsDaemon) {
        QDaemonApplication app(argc, argv);
        QDaemonApplication::setApplicationDescription(APPLICATION_DESCR);

        TcpServer tcpServer(&app);

        QObject::connect(&app, &QDaemonApplication::daemonized, &tcpServer, &TcpServer::start);
        QObject::connect(&app, &QDaemonApplication::aboutToQuit, &tcpServer, &TcpServer::stop);

        return QDaemonApplication::exec();
    } else {
        QApplication::setStyle(QStyleFactory::create("Windows"));
        QApplication a(argc, argv);
        SDPO::HMTelnetServiceDialog dlg;
        dlg.show();
        return a.exec();
    }
}
