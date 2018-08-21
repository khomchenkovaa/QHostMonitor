#include <QtWidgets/QApplication>
#include <QStyleFactory>
#include "startup.h"
#include "mSettings.h"

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Windows"));
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QApplication a(argc, argv);
    SDPO::Startup start_up;

    // we want to stay loaded, even when all windows are closed
    QApplication::setQuitOnLastWindowClosed(false);

    start_up.show();

    return a.exec();
}
