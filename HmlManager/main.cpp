#include "startup.h"
#include "gSettings.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Windows"));
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);

    QApplication a(argc, argv);

    SDPO::Startup start_up;
    QObject::connect(&a, &QApplication::lastWindowClosed, &a, &QApplication::quit);
    start_up.show();

    return a.exec();
}
