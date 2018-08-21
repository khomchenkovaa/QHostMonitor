#include "qIcqOptionsWidget.h"
#include "ui_qIcqOptionsWidget.h"

namespace SDPO {

/******************************************************************/

IcqOptionsWidget::IcqOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::IcqOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

IcqOptionsWidget::~IcqOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void IcqOptionsWidget::on_btnIcqAccountsSwitch_clicked()
{
    QList<QString> dataForSwitch;
    dataForSwitch << ui->cmbPrimaryIcqUin->currentText() << ui->editPrimaryIcqPassword->text() << ui->cmbBackupIcqUin->currentText() << ui->editBackupIcqPassword->text();
    ui->cmbPrimaryIcqUin->setCurrentText(dataForSwitch.at(2));
    ui->editPrimaryIcqPassword->setText(dataForSwitch.at(3));
    ui->cmbBackupIcqUin->setCurrentText(dataForSwitch.at(0));
    ui->editBackupIcqPassword->setText(dataForSwitch.at(1));
}

/******************************************************************/

void IcqOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::ICQ, Settings::PrimaryUIN, QVariant(0));
        ui->cmbPrimaryIcqUin->setCurrentText(value.toString());

    value = Settings::get(Settings::ICQ, Settings::PrimaryPswd, QVariant(0));
        ui->editPrimaryIcqPassword->setText(value.toString());

    value = Settings::get(Settings::ICQ, Settings::BackupUIN, QVariant(0));
        ui->cmbBackupIcqUin->setCurrentText(value.toString());

    value = Settings::get(Settings::ICQ, Settings::BackupPswd, QVariant(0));
        ui->editBackupIcqPassword->setText(value.toString());
}

/******************************************************************/

void IcqOptionsWidget::prepareToSave()
{
    Settings::set(Settings::ICQ, Settings::PrimaryUIN) = QVariant(ui->cmbPrimaryIcqUin->currentText());
    Settings::set(Settings::ICQ, Settings::PrimaryPswd) = QVariant(ui->editPrimaryIcqPassword->text());
    Settings::set(Settings::ICQ, Settings::BackupUIN) = QVariant(ui->cmbBackupIcqUin->currentText());
    Settings::set(Settings::ICQ, Settings::BackupPswd) = QVariant(ui->editBackupIcqPassword->text());

}

/******************************************************************/

} // namespace SDPO


