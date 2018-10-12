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

void JabberOptionsWidget::init(QSettings *s)
{
    ui->editPrimaryLoginServer->setText(s->value(SKEY_JABBER_PrimaryLoginServer, "jabber.org").toString());
    ui->editPrimaryJabberID->setText(s->value(SKEY_JABBER_PrimaryUserName).toString());
    ui->editPrimaryPassword->setText(s->value(SKEY_JABBER_PrimaryPswd).toString());
    ui->cmbPrimarySslTls->setCurrentIndex(s->value(SKEY_JABBER_PrimarySSLMode,0).toInt());
    ui->spinPrimaryTcpPort->setValue(s->value(SKEY_JABBER_PrimaryLoginPort,5222).toInt());

    ui->editBackupLoginServer->setText(s->value(SKEY_JABBER_BackupLoginServer, "jabber.org").toString());
    ui->editBackupJabberID->setText(s->value(SKEY_JABBER_BackupUserName).toString());
    ui->editBackupPassword->setText(s->value(SKEY_JABBER_BackupPswd).toString());
    ui->cmbBackupSslTls->setCurrentIndex(s->value(SKEY_JABBER_BackupSSLMode,0).toInt());
    ui->spinBackupTcpPort->setValue(s->value(SKEY_JABBER_BackupLoginPort,5222).toInt());
}

/******************************************************************/

void JabberOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_JABBER_PrimaryLoginServer, ui->editPrimaryLoginServer->text());
    s->setValue(SKEY_JABBER_PrimaryUserName, ui->editPrimaryJabberID->text());
    s->setValue(SKEY_JABBER_PrimaryPswd, ui->editPrimaryPassword->text());
    s->setValue(SKEY_JABBER_PrimarySSLMode, ui->cmbPrimarySslTls->currentIndex());
    s->setValue(SKEY_JABBER_PrimaryLoginPort, ui->spinPrimaryTcpPort->value());

    s->setValue(SKEY_JABBER_BackupLoginServer, ui->editBackupLoginServer->text());
    s->setValue(SKEY_JABBER_BackupUserName, ui->editBackupJabberID->text());
    s->setValue(SKEY_JABBER_BackupPswd, ui->editBackupPassword->text());
    s->setValue(SKEY_JABBER_BackupSSLMode, ui->cmbBackupSslTls->currentIndex());
    s->setValue(SKEY_JABBER_BackupLoginPort, ui->spinBackupTcpPort->value());
}

/******************************************************************/

} // namespace SDPO


