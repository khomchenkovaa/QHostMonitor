#include "startup.h"
#include "settings.h"

#include <QApplication>
#include <QStyleFactory>
#include <QLockFile>
#include <QDir>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Windows"));
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QApplication a(argc, argv);

    QLockFile lockFile(QDir::temp().absoluteFilePath("SDPO.lock"));

    /* Пытаемся закрыть Lock File, если попытка безуспешна в течение 100 милисекунд,
     * значит уже существует Lock File, созданный другим процессом
     * */
    if (!lockFile.tryLock(100)) {
        QMessageBox::warning(nullptr, APPLICATION_NAME, "Приложение SDPO уже запущено.\n"
                             "Разрешено запускать только один экземпляр приложения.");
        return 1;
    }

    SDPO::Startup start_up;
    // we want to stay loaded, even when all windows are closed
    QApplication::setQuitOnLastWindowClosed(false);
    start_up.show();

    return a.exec();
}
