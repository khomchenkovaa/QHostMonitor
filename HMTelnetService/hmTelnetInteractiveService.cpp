#include "hmTelnetInteractiveService.h"
#include <QApplication>
#include <QDesktopWidget>

using namespace SDPO;

/******************************************************************/

HMTelnetInteractiveService::HMTelnetInteractiveService(int argc, char **argv)
    : QtService<QApplication>(argc, argv, "HM Telnet Service"), gui(nullptr)
{
    setServiceDescription("This application works like Telnet server and allows to control HostMonitor remotely using any telnet client.");
    setServiceFlags(QtServiceBase::CanBeSuspended);
}

/******************************************************************/

HMTelnetInteractiveService::~HMTelnetInteractiveService()
{

}

/******************************************************************/

void HMTelnetInteractiveService::start()
{
#if defined(Q_OS_WIN)
    if ((QSysInfo::WindowsVersion & QSysInfo::WV_NT_based) &&
        (QSysInfo::WindowsVersion >= QSysInfo::WV_VISTA)) {
        logMessage( "Service GUI not allowed on Windows Vista. See the documentation for this example for more information.", QtServiceBase::Error );
        return;
    }
#endif

    qApp->setQuitOnLastWindowClosed(false);

    gui = new HMTelnetServiceDialog();
    gui->move(QApplication::desktop()->availableGeometry().center());
    gui->show();
}

/******************************************************************/

void HMTelnetInteractiveService::stop()
{
    gui->deleteLater();
}

/******************************************************************/

void HMTelnetInteractiveService::pause()
{
    if (gui) {
        gui->hide();
    }
}

/******************************************************************/

void HMTelnetInteractiveService::resume()
{
    if (gui) {
        gui->show();
    }
}

/******************************************************************/

void HMTelnetInteractiveService::processCommand(int code)
{
    logMessage( "Comand code " + QString::number(code), QtServiceBase::Information );
}

/******************************************************************/
