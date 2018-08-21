#include "qJabberOptionsWidget.h"
#include "ui_qJabberOptionsWidget.h"

namespace SDPO {

/******************************************************************/

JabberOptionsWidget::JabberOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::JabberOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

JabberOptionsWidget::~JabberOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void JabberOptionsWidget::on_btnSwitchJabberAccount_clicked()
{
    QList<QString> setPrimary;
    QList<QString> setBackup;
    QList<int> spinBox;
    setPrimary << ui->editPrimaryLoginServer->text()<<ui->editPrimaryJabberID->text()<<ui->editPrimaryPassword->text()<<ui->cmbPrimarySslTls->currentText();
    setBackup  << ui->editBackupLoginServer->text()<<ui->editBackupJabberID->text()<<ui->editBackupPassword->text()<<ui->cmbBackupSslTls->currentText();
    spinBox <<ui->spinPrimaryTcpPort->value()<<ui->spinBackupTcpPort->value();
    ui->editPrimaryLoginServer->setText(setBackup.at(0));
    ui->editPrimaryJabberID->setText(setBackup.at(1));
    ui->editPrimaryPassword->setText(setBackup.at(2));
    ui->cmbPrimarySslTls->setCurrentText(setBackup.at(3));
    ui->spinPrimaryTcpPort->setValue(spinBox.at(1));
    ui->editBackupLoginServer->setText(setPrimary.at(0));
    ui->editBackupJabberID->setText(setPrimary.at(1));
    ui->editBackupPassword->setText(setPrimary.at(2));
    ui->cmbBackupSslTls->setCurrentText(setPrimary.at(3));
    ui->spinBackupTcpPort->setValue(spinBox.at(0));
}

/******************************************************************/

void JabberOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::Jabber, Settings::PrimaryLoginServer, QVariant("jabber.org"));
        ui->editPrimaryLoginServer->setText(value.toString());

    value = Settings::get(Settings::Jabber, Settings::PrimaryUserName, QVariant());
        ui->editPrimaryJabberID->setText(value.toString());

    value = Settings::get(Settings::Jabber, Settings::PrimaryPswd, QVariant());
        ui->editPrimaryPassword->setText(value.toString());

    value = Settings::get(Settings::Jabber, Settings::PrimarySSLMode, QVariant(0));
        ui->cmbPrimarySslTls->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Jabber, Settings::PrimaryLoginPort, QVariant(5222));
        ui->spinPrimaryTcpPort->setValue(value.toInt());

    value = Settings::get(Settings::Jabber, Settings::BackupLoginServer, QVariant("jabber.org"));
        ui->editBackupLoginServer->setText(value.toString());

    value = Settings::get(Settings::Jabber, Settings::BackupUserName, QVariant());
        ui->editBackupJabberID->setText(value.toString());

    value = Settings::get(Settings::Jabber, Settings::BackupPswd, QVariant());
        ui->editBackupPassword->setText(value.toString());

    value = Settings::get(Settings::Jabber, Settings::BackupSSLMode, QVariant(0));
        ui->cmbBackupSslTls->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Jabber, Settings::BackupLoginPort, QVariant(5222));
        ui->spinBackupTcpPort->setValue(value.toInt());
}

/******************************************************************/

void JabberOptionsWidget::prepareToSave()
{
    Settings::set(Settings::Jabber, Settings::PrimaryLoginServer) = QVariant(ui->editPrimaryLoginServer->text());
    Settings::set(Settings::Jabber, Settings::PrimaryUserName) = QVariant(ui->editPrimaryJabberID->text());
    Settings::set(Settings::Jabber, Settings::PrimaryPswd) = QVariant(ui->editPrimaryPassword->text());
    Settings::set(Settings::Jabber, Settings::PrimarySSLMode) = QVariant(ui->cmbPrimarySslTls->currentIndex());
    Settings::set(Settings::Jabber, Settings::PrimaryLoginPort) = QVariant(ui->spinPrimaryTcpPort->value());
    Settings::set(Settings::Jabber, Settings::BackupLoginServer) = QVariant(ui->editBackupLoginServer->text());
    Settings::set(Settings::Jabber, Settings::BackupUserName) = QVariant(ui->editBackupJabberID->text());
    Settings::set(Settings::Jabber, Settings::BackupPswd) = QVariant(ui->editBackupPassword->text());
    Settings::set(Settings::Jabber, Settings::BackupSSLMode) = QVariant(ui->cmbBackupSslTls->currentIndex());
    Settings::set(Settings::Jabber, Settings::BackupLoginPort) = QVariant(ui->spinBackupTcpPort->value());
}

/******************************************************************/

} // namespace SDPO


