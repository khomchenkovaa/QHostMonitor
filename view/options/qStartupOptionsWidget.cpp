#include "qStartupOptionsWidget.h"
#include "ui_qStartupOptionsWidget.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

StartupOptionsWidget::StartupOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::StartupOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

StartupOptionsWidget::~StartupOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void StartupOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::Environ, Settings::StartStopMode, QVariant(2));
    if (value.toInt() == 0) {
        ui->rbStartupMonitoringStart->setChecked(true);
    } else if (value.toInt() == 1){
        ui->rbStartupMonitoringStop->setChecked(true);
    } else
        ui->rbStartupMonitoringRestore->setChecked(true);

    value = Settings::get(Settings::Environ, Settings::WinStatusMode, QVariant(3));
    if (value.toInt() == 0) {
        ui->rbStartupWindowMin->setChecked(true);
    } else if (value.toInt() == 1){
        ui->rbStartupWindowMax->setChecked(true);
    } else if (value.toInt() == 2){
        ui->rbStartupWindowNormal->setChecked(true);
    } else
        ui->rbStartupWindowRestore->setChecked(true);

    value = Settings::get(Settings::Environ, Settings::FileLoadMode, QVariant(2));
    if (value.toInt() == 0) {
        ui->rbStartupEmptyList->setChecked(true);
    } else if (value.toInt() == 1){
        ui->rbnStartupLoadList->setChecked(true);
    } else
        ui->rbStartupRestoreList->setChecked(true);
    onTestListChanged();
    connect(ui->rbStartupEmptyList, SIGNAL(clicked()), this, SLOT(onTestListChanged()));
    connect(ui->rbnStartupLoadList, SIGNAL(clicked()), this, SLOT(onTestListChanged()));
    connect(ui->rbStartupRestoreList, SIGNAL(clicked()), this, SLOT(onTestListChanged()));

    value = Settings::get(Settings::Environ, Settings::ErrorHandlerMode, QVariant(1));
    if (value.toInt() == 0) {
        ui->rbErrorNormal->setChecked(true);
    } else if (value.toInt() == 1){
        ui->rbErrorIgnore->setChecked(true);
    } else
        ui->rbErrorQuit->setChecked(true);

    value = Settings::get(Settings::HostMon, Settings::StartupRun, QVariant(0));
    if (value.toInt() == 0) {
        ui->StartupChk->setChecked(false);
    } else {
        ui->StartupChk->setChecked(true);
    }

    value = Settings::get(Settings::Environ, Settings::LoadFileName, QVariant());
        ui->editStartupFileName->setText(value.toString());
}

/******************************************************************/


void StartupOptionsWidget::prepareToSave()
{
    int startMode = 0;
    if (ui->rbStartupMonitoringStart->isChecked()?1:0)
        startMode = 0;
    else if (ui->rbStartupMonitoringStop->isChecked()?1:0)
        startMode = 1;
    else if (ui->rbStartupMonitoringRestore->isChecked()?1:0)
        startMode = 2;

    Settings::set(Settings::Environ, Settings::StartStopMode) = QVariant(startMode);

    int statusMode = 0;
        if (ui->rbStartupWindowMin->isChecked()?1:0)
            statusMode = 0;
        else if (ui->rbStartupWindowMax->isChecked()?1:0)
            statusMode = 1;
        else if (ui->rbStartupWindowNormal->isChecked()?1:0)
            statusMode = 2;
        else if (ui->rbStartupWindowRestore->isChecked()?1:0)
            statusMode = 3;

    Settings::set(Settings::Environ, Settings::WinStatusMode) = QVariant(statusMode);

    int fileMode = 0;
        if (ui->rbStartupEmptyList->isChecked()?1:0)
            fileMode = 0;
        else if (ui->rbnStartupLoadList->isChecked()?1:0)
            fileMode = 1;
        else if (ui->rbStartupRestoreList->isChecked()?1:0)
            fileMode = 2;

    Settings::set(Settings::Environ, Settings::FileLoadMode) = QVariant(fileMode);

    int handlerMode = 0;
        if (ui->rbErrorNormal->isChecked()?1:0)
            handlerMode = 0;
        else if (ui->rbErrorIgnore->isChecked()?1:0)
            handlerMode = 1;
        else
            handlerMode = 2;

    Settings::set(Settings::Environ, Settings::ErrorHandlerMode) = QVariant(handlerMode);
    Settings::set(Settings::Environ, Settings::LoadFileName) = QVariant(ui->editStartupFileName->text());
    Settings::set(Settings::HostMon, Settings::StartupRun) = QVariant(ui->StartupChk->isChecked()?1:0);
}

/******************************************************************/

void StartupOptionsWidget::onTestListChanged()
{
    if(ui->rbStartupEmptyList->isChecked())
    {
        ui->editStartupFileName->setDisabled(true);
        ui->editStartupFileName->clear();
        ui->btnStartupFileDlg->setDisabled(true);
    }
    else if (ui->rbnStartupLoadList->isChecked())
    {
        ui->editStartupFileName->setEnabled(true);
        ui->btnStartupFileDlg->setEnabled(true);
    }
    else if (ui->rbStartupRestoreList->isChecked())
    {
         ui->editStartupFileName->setDisabled(true);
         ui->editStartupFileName->clear();
         ui->btnStartupFileDlg->setDisabled(true);
    }
}

/******************************************************************/
void StartupOptionsWidget::on_btnStartupFileDlg_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editStartupFileName->text());
    if (!fileName.isEmpty()) {
        ui->editStartupFileName->setText(fileName);
    }
}

/******************************************************************/

} // namespace SDPO

