#include "qOptionsForm.h"
#include "ui_qOptionsForm.h"

#include <QTreeWidgetItem>
#include <QStandardPaths>
#include <QDir>

#include <QDebug>


namespace SDPO {

/******************************************************************/

OptionsForm::OptionsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsForm)
{
    ui->setupUi(this);
    ui->optionsTree->setColumnHidden(1,true);
    connect(ui->wAccessMethod, SIGNAL(goToPage(int)), this, SLOT(setCurrentPage(int)));
    connect(ui->FinishCancelHelpBtn, SIGNAL(accepted()), this, SLOT(prepareToSave()));
    connect(ui->PageControl, SIGNAL(currentChanged(int)), this, SLOT(selectOptionsTreeItem(int)));
    init();
}

/******************************************************************/

OptionsForm::~OptionsForm()
{
    delete ui;
}

/******************************************************************/

void OptionsForm::setCurrentPage(const int idx)
{
    ui->PageControl->setCurrentIndex(idx);
    selectOptionsTreeItem(idx);
}

/******************************************************************/

void OptionsForm::on_optionsTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    // activate panel
    Q_UNUSED(previous);
    ui->PageControl->setCurrentIndex(current->text(1).toInt());
}

/******************************************************************/

void OptionsForm::on_backButton_clicked()
{
    // previous panel
    int curIdx = ui->PageControl->currentIndex();
    if(curIdx > 0) {
        ui->PageControl->setCurrentIndex(curIdx-1);
        selectOptionsTreeItem(curIdx-1);
    }
}

/******************************************************************/

void OptionsForm::on_nextButton_clicked()
{
    // next panel
    int curIdx = ui->PageControl->currentIndex();
    if(curIdx < (ui->PageControl->count()-1)) {
        ui->PageControl->setCurrentIndex(curIdx+1);
        selectOptionsTreeItem(curIdx+1);
    }
}

/******************************************************************/

void OptionsForm::selectOptionsTreeItem(const int idx)
{
    QList<QTreeWidgetItem*> items = ui->optionsTree->findItems(QString().setNum(idx),Qt::MatchExactly,1);
    if(items.count() > 0) {
        ui->optionsTree->setCurrentItem(items.at(0));
        return;
    }
    if (idx==3) {
        items = ui->optionsTree->findItems(QString().setNum(2),Qt::MatchExactly,1);
        ui->optionsTree->setCurrentItem(items.at(0)->child(0));
    } else if (idx==5) {
        items = ui->optionsTree->findItems(QString().setNum(4),Qt::MatchExactly,1);
        ui->optionsTree->setCurrentItem(items.at(0)->child(0));
    } else if ((idx>6) & (idx<12)) {
        items = ui->optionsTree->findItems(QString().setNum(6),Qt::MatchExactly,1);
        ui->optionsTree->setCurrentItem(items.at(0)->child(idx-7));
    }

}

/******************************************************************/

void OptionsForm::setAutostart(bool autostart)
{
    // Путь к папке автозапуска
        QString autostartPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).at(0) + QLatin1String("/autostart");
        // Проверяем, существует ли директория, в которой будет храниться файл автозапуска.
        QDir autorunDir(autostartPath);
        if(!autorunDir.exists()){
            // Если не существует, то создаём
            autorunDir.mkpath(autostartPath);
        }
        QFile autorunFile(autostartPath + QString("/%1.desktop").arg(APPLICATION_NAME));
        // Если autostart == true, то добавляем приложения в автозапуск. В противном случае удаляем
        if(autostart) {
            // Проверяем наличие самого файла автозапуска
            if(!autorunFile.exists()){
                // Открываем файл и записываем в него необходимые данные с указанием пути к исполняемому файлу, с помощью QCoreApplication::applicationFilePath()
                if(autorunFile.open(QFile::WriteOnly)){
                    QString autorunContent("[Desktop Entry]\n"
                                           "Type=Application\n"
                                           "Exec=" + QCoreApplication::applicationFilePath() + "\n"
                                           "Hidden=false\n"
                                           "NoDisplay=false\n"
                                           "X-GNOME-Autostart-enabled=true\n"
                                           "Name[en_GB]=SDPO\n"
                                           "Name=SDPO\n"
                                           "Comment[en_GB]=SDPO\n"
                                           "Comment=SDPO\n");
                    QTextStream outStream(&autorunFile);
                    outStream << autorunContent;
                    // Устанавливаем права доступа, в том числе и на исполнение файла, иначе автозапуск не сработает
                    autorunFile.setPermissions(QFileDevice::ExeUser|QFileDevice::ExeOwner|QFileDevice::ExeOther|QFileDevice::ExeGroup|
                                           QFileDevice::WriteUser|QFileDevice::ReadUser);
                    autorunFile.close();
                }
            }
        } else {
            // Удаляем файл автозапуска
            if(autorunFile.exists()) {
                autorunFile.remove();
            }
        }
}

/******************************************************************/

void OptionsForm::init()
{
    QSettings s;
    ui->wPreferences->init(&s);
    ui->wBehavior->init(&s);
    ui->wStartupOptions->init(&s);
    ui->wService->init(&s);
    ui->wAccessMethod->init(&s);
    ui->wProxy->init(&s);
    ui->wPrimaryLog->init(&s);
    ui->wBackupLog->init(&s);
    ui->wSystemLog->init(&s);
    ui->wLogProcessing->init(&s);
    ui->wHtmlColors->init(&s);
    ui->wViewers->init(&s);
    ui->wReports->init(&s);
    ui->wMsgWindow->init(&s);
    ui->wMailerSettings->init(&s);
    ui->wPagers->init(&s);
    ui->wIcq->init(&s);
    ui->wJabber->init(&s);
    ui->wSmsGsm->init(&s);
    ui->wSmsSmpp->init(&s);
    ui->wPingTrace->init(&s);
    ui->wRci->init(&s);
    ui->wActiveRma->init(&s);
    ui->wScheduler->init(&s);
    ui->wMisc->init(&s);
}

/******************************************************************/

void OptionsForm::prepareToSave()
{
    QSettings s;
    ui->wPreferences->prepareToSave(&s);
    ui->wBehavior->prepareToSave(&s);
    ui->wStartupOptions->prepareToSave(&s);
    ui->wService->prepareToSave(&s);
    ui->wAccessMethod->prepareToSave(&s);
    ui->wProxy->prepareToSave(&s);
    ui->wPrimaryLog->prepareToSave(&s);
    ui->wBackupLog->prepareToSave(&s);
    ui->wSystemLog->prepareToSave(&s);
    ui->wLogProcessing->prepareToSave(&s);
    ui->wHtmlColors->prepareToSave(&s);
    ui->wViewers->prepareToSave(&s);
    ui->wReports->prepareToSave(&s);
    ui->wMsgWindow->prepareToSave(&s);
    ui->wMailerSettings->prepareToSave(&s);
    ui->wPagers->prepareToSave(&s);
    ui->wIcq->prepareToSave(&s);
    ui->wJabber->prepareToSave(&s);
    ui->wSmsGsm->prepareToSave(&s);
    ui->wSmsSmpp->prepareToSave(&s);
    ui->wPingTrace->prepareToSave(&s);
    ui->wRci->prepareToSave(&s);
    ui->wActiveRma->prepareToSave(&s);
    ui->wScheduler->prepareToSave(&s);
    ui->wMisc->prepareToSave(&s);
    setAutostart(s.value(SKEY_STARTUP_StartupRun,0).toInt() == 1);
}

/******************************************************************/

} // namespace SDPO


