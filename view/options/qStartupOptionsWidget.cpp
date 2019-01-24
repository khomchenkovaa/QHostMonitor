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

void StartupOptionsWidget::init(QSettings *s)
{
    switch (s->value(SKEY_STARTUP_StartStopMode,2).toInt()) {
    case 0: ui->rbStartupMonitoringStart->setChecked(true); break;
    case 1: ui->rbStartupMonitoringStop->setChecked(true); break;
    default: // case 2:
        ui->rbStartupMonitoringRestore->setChecked(true);
    }

    switch (s->value(SKEY_STARTUP_WinStatusMode,3).toInt()) {
    case 0: ui->rbStartupWindowMin->setChecked(true); break;
    case 1: ui->rbStartupWindowMax->setChecked(true); break;
    case 2: ui->rbStartupWindowNormal->setChecked(true); break;
    default: // case 3:
        ui->rbStartupWindowRestore->setChecked(true);
    }

    switch (s->value(SKEY_STARTUP_FileLoadMode,2).toInt()) {
    case 0: ui->rbStartupEmptyList->setChecked(true); break;
    case 1: ui->rbnStartupLoadList->setChecked(true); break;
    default: // case 2:
        ui->rbStartupRestoreList->setChecked(true);
    }

    onTestListChanged();
    connect(ui->rbStartupEmptyList, SIGNAL(clicked()), this, SLOT(onTestListChanged()));
    connect(ui->rbnStartupLoadList, SIGNAL(clicked()), this, SLOT(onTestListChanged()));
    connect(ui->rbStartupRestoreList, SIGNAL(clicked()), this, SLOT(onTestListChanged()));

    switch (s->value(SKEY_STARTUP_ErrorHandlerMode,1).toInt()) {
    case 0: ui->rbErrorNormal->setChecked(true); break;
    case 2: ui->rbErrorQuit->setChecked(true); break;
    default: // case 1:
        ui->rbErrorIgnore->setChecked(true);
    }

    ui->StartupChk->setChecked(s->value(SKEY_STARTUP_StartupRun,0) == 1);
    ui->editStartupFileName->setText(s->value(SKEY_STARTUP_LoadFileName).toString());
}

/******************************************************************/

void StartupOptionsWidget::prepareToSave(QSettings *s)
{
    int startStopMode = 2; // default
    if (ui->rbStartupMonitoringStart->isChecked()) {
        startStopMode = 0;
    } else if (ui->rbStartupMonitoringStop->isChecked()) {
        startStopMode = 1;
    }
    s->setValue(SKEY_STARTUP_StartStopMode, startStopMode);

    int winStatusMode = 3; // default
    if (ui->rbStartupWindowMin->isChecked()) {
        winStatusMode = 0;
    } else if (ui->rbStartupWindowMax->isChecked()) {
        winStatusMode = 1;
    } else if (ui->rbStartupWindowNormal->isChecked()) {
        winStatusMode = 2;
    }
    s->setValue(SKEY_STARTUP_WinStatusMode, winStatusMode);

    int fileLoadMode = 2; // default
    if (ui->rbStartupEmptyList->isChecked()) {
        fileLoadMode = 0;
    } else if (ui->rbnStartupLoadList->isChecked()) {
        fileLoadMode = 1;
    }
    s->setValue(SKEY_STARTUP_FileLoadMode, fileLoadMode);

    int errorHandlerMode = 1; // default
    if (ui->rbErrorNormal->isChecked()) {
        errorHandlerMode = 0;
    } else if (ui->rbErrorQuit->isChecked()) {
        errorHandlerMode = 2;
    }
    s->setValue(SKEY_STARTUP_ErrorHandlerMode, errorHandlerMode);

    s->setValue(SKEY_STARTUP_StartupRun, ui->StartupChk->isChecked()?1:0);
    s->setValue(SKEY_STARTUP_LoadFileName, ui->editStartupFileName->text());
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

