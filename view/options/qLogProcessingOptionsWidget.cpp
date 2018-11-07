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
    if (s->value(SKEY_LOGGING_UseBothLogs,0).toInt()) {
        ui->rbLogProcessingBoth->setChecked(true);
    } else {
        ui->rbLogProcessingBackup->setChecked(true);
    }
    ui->chkLogProcessingCommon->setChecked(s->value(SKEY_COMMONLOG_CheckEnabled,0).toInt());
    on_chkLogsStatus();
    connect(ui->chkLogProcessingCommon, SIGNAL(clicked()), this, SLOT(on_chkLogsStatus()));

    // Common log
    ui->cmbLogProcessingCommonCriteria->setCurrentIndex(s->value(SKEY_COMMONLOG_CheckMode,0).toInt());
    on_SelectLogs();
    connect(ui->cmbLogProcessingCommonCriteria, SIGNAL(currentIndexChanged(int)), this, SLOT(on_SelectLogs()));

    ui->cmbLogProcessingCommonTime->setCurrentIndex(s->value(SKEY_COMMONLOG_TimeUnit,2).toInt());
    ui->spinLogProcessingCommonTime->setValue(s->value(SKEY_COMMONLOG_TimeLimit,3).toInt());
    ui->spinLogProcessingCommonSize->setValue(s->value(SKEY_COMMONLOG_SizeLimit,600000).toInt());
    ui->editLogProcessingCommonCmd->setText(s->value(SKEY_COMMONLOG_ExtCommand, COMMONLOG_PROCESSING_EXT_CMD).toString());

    // Private log
    ui->chkLogProcessingPrivate->setChecked(s->value(SKEY_PRIVLOG_CheckEnabled,0).toInt());
    on_chkLogsStatus();
    connect(ui->chkLogProcessingPrivate, SIGNAL(clicked()), this, SLOT(on_chkLogsStatus()));

    ui->cmbLogProcessingPrivateCriteria->setCurrentIndex(s->value(SKEY_PRIVLOG_CheckMode,1).toInt());
    on_SelectLogs();
    connect(ui->cmbLogProcessingPrivateCriteria, SIGNAL(currentIndexChanged(int)), this, SLOT(on_SelectLogs()));

    ui->cmbLogProcessingTime->setCurrentIndex(s->value(SKEY_PRIVLOG_TimeUnit,2).toInt());
    ui->spinLogProcessingTime->setValue(s->value(SKEY_PRIVLOG_TimeLimit,3).toInt());
    ui->spinLogProcessingSize->setValue(s->value(SKEY_PRIVLOG_SizeLimit,200000).toInt());
    ui->editLogProcessingPrivateCmd->setText(s->value(SKEY_PRIVLOG_ExtCommand, PRIVLOG_PROCESSING_EXT_CMD).toString());
}

/******************************************************************/


void LogProcessingOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_LOGGING_UseBothLogs,ui->rbLogProcessingBoth->isChecked());

    // Common log
    s->setValue(SKEY_COMMONLOG_CheckEnabled, ui->chkLogProcessingCommon->isChecked()?1:0);
    s->setValue(SKEY_COMMONLOG_CheckMode, ui->cmbLogProcessingCommonCriteria->currentIndex());
    s->setValue(SKEY_COMMONLOG_TimeUnit, ui->cmbLogProcessingCommonTime->currentIndex());
    s->setValue(SKEY_COMMONLOG_TimeLimit, ui->spinLogProcessingCommonTime->value());
    s->setValue(SKEY_COMMONLOG_SizeLimit, ui->spinLogProcessingCommonSize->value());
    s->setValue(SKEY_COMMONLOG_ExtCommand, ui->editLogProcessingCommonCmd->text());

    // Private log
    s->setValue(SKEY_PRIVLOG_CheckEnabled, ui->chkLogProcessingPrivate->isChecked()?1:0);
    s->setValue(SKEY_PRIVLOG_CheckMode, ui->cmbLogProcessingPrivateCriteria->currentIndex());
    s->setValue(SKEY_PRIVLOG_TimeUnit, ui->cmbLogProcessingTime->currentIndex());
    s->setValue(SKEY_PRIVLOG_TimeLimit, ui->spinLogProcessingTime->value());
    s->setValue(SKEY_PRIVLOG_SizeLimit, ui->spinLogProcessingSize->value());
    s->setValue(SKEY_PRIVLOG_ExtCommand, ui->editLogProcessingPrivateCmd->text());
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
