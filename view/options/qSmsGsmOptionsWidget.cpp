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

void SmsGsmOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::GSM, Settings::Primary_ComPort, QVariant("COM1"));
        ui->cmbPrimaryComPort->setCurrentText(value.toString());

    value = Settings::get(Settings::GSM, Settings::Primary_BaudRate, QVariant("19200"));
        ui->cmbPrimaryBaudRate->setCurrentText(value.toString());

    value = Settings::get(Settings::GSM, Settings::Primary_Modem, QVariant("Siemens A1"));
        ui->cmbPrimaryModemType->setCurrentText(value.toString());

    value = Settings::get(Settings::GSM, Settings::Primary_SMSFormat, QVariant("PDU"));
        ui->cmbPrimaryMode->setCurrentText(value.toString());

    value = Settings::get(Settings::GSM, Settings::Primary_PIN, QVariant("1111"));
        ui->editPrimaryPin->setText(value.toString());

    value = Settings::get(Settings::GSM, Settings::Primary_SCA, QVariant());
        ui->editPrimaryServiceCenter->setText(value.toString());

    value = Settings::get(Settings::GSM, Settings::Backup_ComPort, QVariant("COM2"));
        ui->cmbBackupComPort->setCurrentText(value.toString());

    value = Settings::get(Settings::GSM, Settings::Backup_BaudRate, QVariant("19200"));
        ui->cmbBackupBaudRate->setCurrentText(value.toString());

    value = Settings::get(Settings::GSM, Settings::Backup_Modem, QVariant("Nokia 6650"));
        ui->cmbBackupModemType->setCurrentText(value.toString());

    value = Settings::get(Settings::GSM, Settings::Backup_SMSFormat, QVariant("PDU"));
        ui->cmbBackupMode->setCurrentText(value.toString());

    value = Settings::get(Settings::GSM, Settings::Backup_PIN, QVariant("1111"));
        ui->editBackupPin->setText(value.toString());

    value = Settings::get(Settings::GSM, Settings::Backup_SCA, QVariant());
        ui->editBackupServiceCenter->setText(value.toString());

    value = Settings::get(Settings::GSM, Settings::LogMode, QVariant(2));
        ui->cmbSmsLog->setCurrentIndex(value.toInt());

    QString curFolder = QCoreApplication::applicationDirPath() + "/logs/";
    value = Settings::get(Settings::GSM, Settings::LogFile, QVariant(curFolder + "smslog.txt"));
        ui->editLogFile->setText(value.toString());
}

/******************************************************************/

void SmsGsmOptionsWidget::prepareToSave()
{
    Settings::set(Settings::GSM, Settings::Primary_ComPort) = QVariant(ui->cmbPrimaryComPort->currentText());
    Settings::set(Settings::GSM, Settings::Primary_BaudRate) = QVariant(ui->cmbPrimaryBaudRate->currentText());
    Settings::set(Settings::GSM, Settings::Primary_Modem) = QVariant(ui->cmbPrimaryModemType->currentText());
    Settings::set(Settings::GSM, Settings::Primary_SMSFormat) = QVariant(ui->cmbPrimaryMode->currentText());
    Settings::set(Settings::GSM, Settings::Primary_PIN) = QVariant(ui->editPrimaryPin->text());
    Settings::set(Settings::GSM, Settings::Primary_SCA) = QVariant(ui->editPrimaryServiceCenter->text());
    Settings::set(Settings::GSM, Settings::Backup_ComPort) = QVariant(ui->cmbBackupComPort->currentText());
    Settings::set(Settings::GSM, Settings::Backup_BaudRate) = QVariant(ui->cmbBackupBaudRate->currentText());
    Settings::set(Settings::GSM, Settings::Backup_Modem) = QVariant(ui->cmbBackupModemType->currentText());
    Settings::set(Settings::GSM, Settings::Backup_SMSFormat) = QVariant(ui->cmbBackupMode->currentText());
    Settings::set(Settings::GSM, Settings::Backup_PIN) = QVariant(ui->editBackupPin->text());
    Settings::set(Settings::GSM, Settings::Backup_SCA) = QVariant(ui->editBackupServiceCenter->text());
    Settings::set(Settings::GSM, Settings::LogMode) = QVariant(ui->cmbSmsLog->currentIndex());
    Settings::set(Settings::GSM, Settings::LogFile) = QVariant(ui->editLogFile->text());
}

/******************************************************************/

} // namespace SDPO

