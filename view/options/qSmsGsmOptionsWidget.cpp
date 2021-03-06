#include "qSmsGsmOptionsWidget.h"
#include "ui_qSmsGsmOptionsWidget.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

SmsGsmOptionsWidget::SmsGsmOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::SmsGsmOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SmsGsmOptionsWidget::~SmsGsmOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void SmsGsmOptionsWidget::on_btnSelectLogFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editLogFile->text());
    if (!fileName.isEmpty()) {
        ui->editLogFile->setText(fileName);
    }
}

/******************************************************************/

void SmsGsmOptionsWidget::init(QSettings *s)
{
    ui->cmbPrimaryComPort->setCurrentText  (s->value(SKEY_GSM_PrimaryComPort, SVAL_GSM_PrimaryComPort).toString());
    ui->cmbPrimaryBaudRate->setCurrentText (s->value(SKEY_GSM_PrimaryBaudRate, SVAL_GSM_PrimaryBaudRate).toString());
    ui->cmbPrimaryModemType->setCurrentText(s->value(SKEY_GSM_PrimaryModem, SVAL_GSM_PrimaryModem).toString());
    ui->cmbPrimaryMode->setCurrentText     (s->value(SKEY_GSM_PrimarySmsFormat, SVAL_GSM_PrimarySmsFormat).toString());
    ui->editPrimaryPin->setText            (s->value(SKEY_GSM_PrimaryPIN, SVAL_GSM_PrimaryPIN).toString());
    ui->editPrimaryServiceCenter->setText  (s->value(SKEY_GSM_PrimarySCA).toString());

    ui->cmbBackupComPort->setCurrentText  (s->value(SKEY_GSM_BackupComPort, SVAL_GSM_BackupComPort).toString());
    ui->cmbBackupBaudRate->setCurrentText (s->value(SKEY_GSM_BackupBaudRate, SVAL_GSM_BackupBaudRate).toString());
    ui->cmbBackupModemType->setCurrentText(s->value(SKEY_GSM_BackupModem, SVAL_GSM_BackupModem).toString());
    ui->cmbBackupMode->setCurrentText     (s->value(SKEY_GSM_BackupSmsFormat, SVAL_GSM_BackupSmsFormat).toString());
    ui->editBackupPin->setText            (s->value(SKEY_GSM_BackupPIN, SVAL_GSM_BackupPIN).toString());
    ui->editBackupServiceCenter->setText  (s->value(SKEY_GSM_BackupSCA).toString());

    ui->cmbSmsLog->setCurrentIndex(s->value(SKEY_GSM_LogMode, SVAL_GSM_LogMode).toInt());
    ui->editLogFile->setText      (s->value(SKEY_GSM_LogFile, QCoreApplication::applicationDirPath() + SVAL_GSM_LogFile).toString());
}

/******************************************************************/

void SmsGsmOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_GSM_PrimaryComPort, ui->cmbPrimaryComPort->currentText());
    s->setValue(SKEY_GSM_PrimaryBaudRate, ui->cmbPrimaryBaudRate->currentText());
    s->setValue(SKEY_GSM_PrimaryModem, ui->cmbPrimaryModemType->currentText());
    s->setValue(SKEY_GSM_PrimarySmsFormat, ui->cmbPrimaryMode->currentText());
    s->setValue(SKEY_GSM_PrimaryPIN, ui->editPrimaryPin->text());
    s->setValue(SKEY_GSM_PrimarySCA, ui->editPrimaryServiceCenter->text());

    s->setValue(SKEY_GSM_BackupComPort, ui->cmbBackupComPort->currentText());
    s->setValue(SKEY_GSM_BackupBaudRate, ui->cmbBackupBaudRate->currentText());
    s->setValue(SKEY_GSM_BackupModem, ui->cmbBackupModemType->currentText());
    s->setValue(SKEY_GSM_BackupSmsFormat, ui->cmbBackupMode->currentText());
    s->setValue(SKEY_GSM_BackupPIN, ui->editBackupPin->text());
    s->setValue(SKEY_GSM_BackupSCA, ui->editBackupServiceCenter->text());

    s->setValue(SKEY_GSM_LogMode, ui->cmbSmsLog->currentIndex());
    s->setValue(SKEY_GSM_LogFile, ui->editLogFile->text());
}

/******************************************************************/

} // namespace SDPO

