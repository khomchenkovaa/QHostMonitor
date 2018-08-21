#include "qSmsSmppOptionsWidget.h"
#include "ui_qSmsSmppOptionsWidget.h"

namespace SDPO {

SmsSmppOptionsWidget::SmsSmppOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::SmsSmppOptionsWidget)
{
    ui->setupUi(this);
}

SmsSmppOptionsWidget::~SmsSmppOptionsWidget()
{
    delete ui;
}

void SmsSmppOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::SMS_SMPP1, Settings::Host, QVariant());
        ui->editPrimaryHost->setText(value.toString());

    value = Settings::get(Settings::SMS_SMPP1, Settings::Port, QVariant(2775));
        ui->spinPrimaryPort->setValue(value.toInt());

    value = Settings::get(Settings::SMS_SMPP1, Settings::ID, QVariant());
        ui->editPrimarySystemId->setText(value.toString());

    value = Settings::get(Settings::SMS_SMPP1, Settings::Pswd, QVariant());
        ui->editPrimaryPassword->setText(value.toString());

    value = Settings::get(Settings::SMS_SMPP1, Settings::SrcAddr, QVariant());
        ui->editPrimaryAddress->setText(value.toString());

    value = Settings::get(Settings::SMS_SMPP1, Settings::TON, QVariant(0));
        ui->cmbPrimaryTon->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::SMS_SMPP1, Settings::NPI, QVariant(0));
        ui->cmbPrimaryNpi->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::SMS_SMPP2, Settings::Host, QVariant());
        ui->editBackupHost->setText(value.toString());

    value = Settings::get(Settings::SMS_SMPP2, Settings::Port, QVariant(2775));
        ui->spinBackupPort->setValue(value.toInt());

    value = Settings::get(Settings::SMS_SMPP2, Settings::ID, QVariant());
        ui->editBackupSystemId->setText(value.toString());

    value = Settings::get(Settings::SMS_SMPP2, Settings::Pswd, QVariant());
        ui->editBackupPassword->setText(value.toString());

    value = Settings::get(Settings::SMS_SMPP2, Settings::SrcAddr, QVariant());
        ui->editBackupAddress->setText(value.toString());

    value = Settings::get(Settings::SMS_SMPP2, Settings::TON, QVariant(0));
        ui->cmbBackupTon->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::SMS_SMPP2, Settings::NPI, QVariant(0));
        ui->cmbBackupNpi->setCurrentIndex(value.toInt());
}

void SmsSmppOptionsWidget::prepareToSave()
{
    Settings::set(Settings::SMS_SMPP1, Settings::Host) = QVariant(ui->editPrimaryHost->text());
    Settings::set(Settings::SMS_SMPP1, Settings::Port) = QVariant(ui->spinPrimaryPort->value());
    Settings::set(Settings::SMS_SMPP1, Settings::ID) = QVariant(ui->editPrimarySystemId->text());
    Settings::set(Settings::SMS_SMPP1, Settings::Pswd) = QVariant(ui->editPrimaryPassword->text());
    Settings::set(Settings::SMS_SMPP1, Settings::SrcAddr) = QVariant(ui->editPrimaryAddress->text());
    Settings::set(Settings::SMS_SMPP1, Settings::TON) = QVariant(ui->cmbBackupTon->currentIndex());
    Settings::set(Settings::SMS_SMPP1, Settings::NPI) = QVariant(ui->cmbPrimaryNpi->currentIndex());
    Settings::set(Settings::SMS_SMPP2, Settings::Host) = QVariant(ui->editBackupHost->text());
    Settings::set(Settings::SMS_SMPP2, Settings::Port) = QVariant(ui->spinBackupPort->value());
    Settings::set(Settings::SMS_SMPP2, Settings::ID) = QVariant(ui->editBackupSystemId->text());
    Settings::set(Settings::SMS_SMPP2, Settings::Pswd) = QVariant(ui->editBackupPassword->text());
    Settings::set(Settings::SMS_SMPP2, Settings::SrcAddr) = QVariant(ui->editBackupAddress->text());
    Settings::set(Settings::SMS_SMPP2, Settings::TON) = QVariant(ui->cmbBackupTon->currentIndex());
    Settings::set(Settings::SMS_SMPP2, Settings::NPI) = QVariant(ui->cmbBackupNpi->currentIndex());

}

} // namespace SDPO
