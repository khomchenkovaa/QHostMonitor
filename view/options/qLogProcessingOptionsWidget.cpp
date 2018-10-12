#include "qLogProcessingOptionsWidget.h"
#include "ui_qLogProcessingOptionsWidget.h"

namespace SDPO {

/******************************************************************/

LogProcessingOptionsWidget::LogProcessingOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::LogProcessingOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

LogProcessingOptionsWidget::~LogProcessingOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void LogProcessingOptionsWidget::init(QSettings *s)
{
    QVariant value = Settings::get(Settings::Logging, Settings::UseBothLogs, QVariant(0));
        if (value.toInt() == 0)
            ui->rbLogProcessingBackup->setChecked(true);
        else if (value.toInt() == 1)
            ui->rbLogProcessingBoth->setChecked(true);

    value = Settings::get(Settings::Logging_CommonProcessing, Settings::CheckEnabled, QVariant(0));
        if (value.toInt() == 0)
        {
            ui->chkLogProcessingCommon->setChecked(false);
        }
        else
        {
            ui->chkLogProcessingCommon->setChecked(true);
        }
        on_chkLogsStatus();
        connect(ui->chkLogProcessingCommon, SIGNAL(clicked()), this, SLOT(on_chkLogsStatus()));

    value = Settings::get(Settings::Logging_CommonProcessing, Settings::CheckMode, QVariant(0));
        ui->cmbLogProcessingCommonCriteria->setCurrentIndex(value.toInt());
        on_SelectLogs();
        connect(ui->cmbLogProcessingCommonCriteria, SIGNAL(currentIndexChanged(int)), this, SLOT(on_SelectLogs()));

    value = Settings::get(Settings::Logging_CommonProcessing, Settings::TimeUnit, QVariant(2));
        ui->cmbLogProcessingCommonTime->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Logging_CommonProcessing, Settings::TimeLimit, QVariant(3));
        ui->spinLogProcessingCommonTime->setValue(value.toInt());

    value = Settings::get(Settings::Logging_CommonProcessing, Settings::SizeLimit, QVariant(600000));
        ui->spinLogProcessingCommonSize->setValue(value.toInt());

    value = Settings::get(Settings::Logging_CommonProcessing, Settings::ExtCommand, QVariant("cmd  /c  del  ""%log%"" +"));
        ui->editLogProcessingCommonCmd->setText(value.toString());

    value = Settings::get(Settings::Logging_PrivProcessing, Settings::CheckEnabled, QVariant(0));
        if (value.toInt() == 0)
            ui->chkLogProcessingPrivate->setChecked(false);
        else
            ui->chkLogProcessingPrivate->setChecked(true);
        on_chkLogsStatus();
        connect(ui->chkLogProcessingPrivate, SIGNAL(clicked()), this, SLOT(on_chkLogsStatus()));

    value = Settings::get(Settings::Logging_PrivProcessing, Settings::CheckMode, QVariant(1));
        ui->cmbLogProcessingPrivateCriteria->setCurrentIndex(value.toInt());
        on_SelectLogs();
        connect(ui->cmbLogProcessingPrivateCriteria, SIGNAL(currentIndexChanged(int)), this, SLOT(on_SelectLogs()));

    value = Settings::get(Settings::Logging_PrivProcessing, Settings::TimeUnit, QVariant(2));
        ui->cmbLogProcessingTime->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Logging_PrivProcessing, Settings::TimeLimit, QVariant(3));
        ui->spinLogProcessingTime->setValue(value.toInt());

    value = Settings::get(Settings::Logging_PrivProcessing, Settings::SizeLimit, QVariant(200000));
        ui->spinLogProcessingSize->setValue(value.toInt());

    value = Settings::get(Settings::Logging_PrivProcessing, Settings::ExtCommand, QVariant("cmd  /c  move /y  ""%log%"  "%logpath%old\%logname%"""));
        ui->editLogProcessingPrivateCmd->setText(value.toString());

}

/******************************************************************/


void LogProcessingOptionsWidget::prepareToSave(QSettings *s)
{
    int BothsLogs;
    if (ui->rbLogProcessingBackup->isChecked())
        BothsLogs = 0;
    else if (ui->rbLogProcessingBoth->isChecked())
        BothsLogs = 1;

    Settings::set(Settings::Logging, Settings::UseBothLogs) = QVariant(BothsLogs);
    Settings::set(Settings::Logging_CommonProcessing, Settings::CheckEnabled) = QVariant(ui->chkLogProcessingCommon->isChecked()?1:0);
    Settings::set(Settings::Logging_CommonProcessing, Settings::CheckMode) = QVariant(ui->cmbLogProcessingCommonCriteria->currentIndex());
    Settings::set(Settings::Logging_CommonProcessing, Settings::TimeUnit) = QVariant(ui->cmbLogProcessingCommonTime->currentIndex());
    Settings::set(Settings::Logging_CommonProcessing, Settings::TimeLimit) = QVariant(ui->spinLogProcessingCommonTime->value());
    Settings::set(Settings::Logging_CommonProcessing, Settings::SizeLimit) = QVariant(ui->spinLogProcessingCommonSize->value());
    Settings::set(Settings::Logging_CommonProcessing, Settings::ExtCommand) =QVariant(ui->editLogProcessingCommonCmd->text());
    Settings::set(Settings::Logging_PrivProcessing, Settings::CheckEnabled) = QVariant(ui->chkLogProcessingPrivate->isChecked()?1:0);
    Settings::set(Settings::Logging_PrivProcessing, Settings::CheckMode) = QVariant(ui->cmbLogProcessingPrivateCriteria->currentIndex());
    Settings::set(Settings::Logging_PrivProcessing, Settings::TimeUnit) = QVariant(ui->cmbLogProcessingTime->currentIndex());
    Settings::set(Settings::Logging_PrivProcessing, Settings::TimeLimit) = QVariant(ui->spinLogProcessingTime->value());
    Settings::set(Settings::Logging_PrivProcessing, Settings::SizeLimit) = QVariant(ui->spinLogProcessingSize->value());
    Settings::set(Settings::Logging_PrivProcessing, Settings::ExtCommand) =QVariant(ui->editLogProcessingPrivateCmd->text());
}

/******************************************************************/

void LogProcessingOptionsWidget::on_chkLogsStatus()
{
        if (ui->chkLogProcessingCommon->isChecked())
        {
            ui->cmbLogProcessingCommonCriteria->setEnabled(true);
            ui->spinLogProcessingCommonTime->setEnabled(true);
            ui->cmbLogProcessingCommonTime->setEnabled(true);
            ui->spinLogProcessingCommonSize->setEnabled(true);
            ui->lblLogProcessingKb_2->setEnabled(true);
            ui->editLogProcessingCommonCmd->setEnabled(true);
            ui->lblLogProcessingCommon->setEnabled(true);
        }
        else
        {
            ui->cmbLogProcessingCommonCriteria->setDisabled(true);
            ui->spinLogProcessingCommonTime->setDisabled(true);
            ui->cmbLogProcessingCommonTime->setDisabled(true);
            ui->spinLogProcessingCommonSize->setDisabled(true);
            ui->lblLogProcessingKb_2->setDisabled(true);
            ui->editLogProcessingCommonCmd->setDisabled(true);
            ui->lblLogProcessingCommon->setDisabled(true);
        }

        if(ui->chkLogProcessingPrivate->isChecked())
        {
            ui->cmbLogProcessingPrivateCriteria->setEnabled(true);
            ui->spinLogProcessingTime->setEnabled(true);
            ui->cmbLogProcessingTime->setEnabled(true);
            ui->spinLogProcessingSize->setEnabled(true);
            ui->lblLogProcessingKb->setEnabled(true);
            ui->editLogProcessingPrivateCmd->setEnabled(true);
            ui->lblLogProcessingPrivate->setEnabled(true);
        }
        else
        {
            ui->cmbLogProcessingPrivateCriteria->setDisabled(true);
            ui->spinLogProcessingTime->setDisabled(true);
            ui->cmbLogProcessingTime->setDisabled(true);
            ui->spinLogProcessingSize->setDisabled(true);
            ui->lblLogProcessingKb->setDisabled(true);
            ui->editLogProcessingPrivateCmd->setDisabled(true);
            ui->lblLogProcessingPrivate->setDisabled(true);
        }
}
/******************************************************************/

void LogProcessingOptionsWidget::on_SelectLogs()
{   int CommonSelect = ui->cmbLogProcessingCommonCriteria->currentIndex();
        switch (CommonSelect )
        {
        case 0:
             ui->lblLogProcessingKb_2->setHidden(true);
             ui->spinLogProcessingCommonSize->setHidden(true);
             ui->cmbLogProcessingCommonTime->setHidden(false);
             ui->spinLogProcessingCommonTime->setHidden(false);
             break;
        case 1:
             ui->lblLogProcessingKb_2->setHidden(false);
             ui->spinLogProcessingCommonSize->setHidden(false);
             ui->cmbLogProcessingCommonTime->setHidden(true);
             ui->spinLogProcessingCommonTime->setHidden(true);
             break;
        case 2:

             ui->lblLogProcessingKb_2->setHidden(true);
             ui->spinLogProcessingCommonSize->setHidden(true);
             ui->cmbLogProcessingCommonTime->setHidden(true);
             ui->spinLogProcessingCommonTime->setHidden(true);
             break;
        }

    int PrivateSelect = ui->cmbLogProcessingPrivateCriteria->currentIndex();
        switch (PrivateSelect)
        {
        case 0:
             ui->lblLogProcessingKb->setHidden(true);
             ui->spinLogProcessingSize->setHidden(true);
             ui->cmbLogProcessingTime->setHidden(false);
             ui->spinLogProcessingTime->setHidden(false);
             break;
        case 1:
             ui->lblLogProcessingKb->setHidden(false);
             ui->spinLogProcessingSize->setHidden(false);
             ui->cmbLogProcessingTime->setHidden(true);
             ui->spinLogProcessingTime->setHidden(true);
             break;
        case 2:
             ui->lblLogProcessingKb->setHidden(true);
             ui->spinLogProcessingSize->setHidden(true);
             ui->cmbLogProcessingTime->setHidden(true);
             ui->spinLogProcessingTime->setHidden(true);
             break;
        }

}

/******************************************************************/

} // namespace SDPO
