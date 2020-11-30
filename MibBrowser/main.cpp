#include "startup.h"

#include <QApplication>
#include <QStyleFactory>

#define ORGANIZATION_NAME "SNIIP"
#define ORGANIZATION_DOMAIN "sniip.ru"
#define APPLICATION_NAME "MibBrowser"

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Windows"));
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QApplication a(argc, argv);

    MibBrowser::Startup start_up;
    start_up.show();

    return a.exec();
}
