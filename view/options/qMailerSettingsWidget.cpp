#include "qMailerSettingsWidget.h"
#include "ui_qMailerSettingsWidget.h"
#include "QMessageBox"

namespace SDPO {

/******************************************************************/

MailerSettingsWidget::MailerSettingsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::MailerSettingsWidget)
{
    ui->setupUi(this);

}

/******************************************************************/

MailerSettingsWidget::~MailerSettingsWidget()
{
    delete ui;
}

/******************************************************************/

void MailerSettingsWidget::onPrimaryPortChange()
{
   int PrimaryTlsIndx =  ui->cmbPrimarySmtpTls->currentIndex();
   int PrimaryPort = ui->spinPrimarySmtpPort->value();
   if ( PrimaryTlsIndx == 0 && PrimaryPort != 25 ) {
       QMessageBox::StandardButton reply = QMessageBox::warning(this,QObject::tr("Confirm"),  "Would you like to change port to #25", QMessageBox::Ok | QMessageBox::Cancel);
       if (reply == QMessageBox::Ok) {
            ui->spinPrimarySmtpPort->setValue(25);
       }
   }
   else if (PrimaryTlsIndx == 1 && PrimaryPort != 465) {
       QMessageBox::StandardButton reply = QMessageBox::warning(this,QObject::tr("Hello"),  "Would you like to change port to #465", QMessageBox::Ok | QMessageBox::Cancel);
       if (reply == QMessageBox::Ok) {
            ui->spinPrimarySmtpPort->setValue(465);
       }
   }
   else if (PrimaryTlsIndx == 2 && PrimaryPort != 587) {
       QMessageBox::StandardButton reply = QMessageBox::warning(this,QObject::tr("Hello"),  "Would you like to change port to #587", QMessageBox::Ok | QMessageBox::Cancel);
       if (reply == QMessageBox::Ok) {
            ui->spinPrimarySmtpPort->setValue(587);
       }
   }
}

/******************************************************************/

void MailerSettingsWidget::onBackUpPortChange()
{    
   int BackupTlsIndx =  ui->cmbBackupSmtpTls->currentIndex();
   int BackupPort = ui->spinBackupSmtpPort->value();
   if ( BackupTlsIndx == 0 && BackupPort != 25 ) {
       QMessageBox::StandardButton reply = QMessageBox::warning(this,QObject::tr("Confirm"),  "Would you like to change port to #25", QMessageBox::Ok | QMessageBox::Cancel);
       if (reply == QMessageBox::Ok) {
            ui->spinBackupSmtpPort->setValue(25);
       }
   }
   else if (BackupTlsIndx == 1 && BackupPort != 465) {
       QMessageBox::StandardButton reply = QMessageBox::warning(this,QObject::tr("Hello"),  "Would you like to change port to #465", QMessageBox::Ok | QMessageBox::Cancel);
       if (reply == QMessageBox::Ok) {
            ui->spinBackupSmtpPort->setValue(465);
       }
   }
   else if (BackupTlsIndx == 2 && BackupPort != 587) {
       QMessageBox::StandardButton reply = QMessageBox::warning(this,QObject::tr("Hello"),  "Would you like to change port to #587", QMessageBox::Ok | QMessageBox::Cancel);
       if (reply == QMessageBox::Ok) {
            ui->spinBackupSmtpPort->setValue(587);
       }
   }
}

/******************************************************************/

void MailerSettingsWidget::init(QSettings *s)
{
    ui->cmbPrimarySmtpAddress->setCurrentText(s->value(SKEY_SMTP_Server1,"smtp.mail.yahoo.com").toString());
    ui->spinPrimarySmtpPort->setValue(s->value(SKEY_SMTP_Port1,25).toInt());
    ui->cmbPrimarySmtpTls->setCurrentIndex(s->value(SKEY_SMTP_SslType1,0).toInt());
    int idx1 = s->value(SKEY_SMTP_Auth1,0).toInt();
    ui->cmbPrimarySmtpAuth->setCurrentIndex(idx1);
    ui->editPrimarySmtpLogin->setText(s->value(SKEY_SMTP_User1).toString());
    ui->editPrimarySmtpPassword->setText(s->value(SKEY_SMTP_Pswd1).toString());
    on_cmbPrimaryAuthSelect(idx1);
    connect(ui->cmbPrimarySmtpTls, SIGNAL(currentIndexChanged(int)), this, SLOT(onPrimaryPortChange()));
    connect(ui->cmbPrimarySmtpAuth, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cmbPrimaryAuthSelect(int)));

    ui->cmbBackupSmtpAddress->setCurrentText(s->value(SKEY_SMTP_Server2,"smtp.mail.yahoo.com").toString());
    ui->spinBackupSmtpPort->setValue(s->value(SKEY_SMTP_Port2,25).toInt());
    ui->cmbBackupSmtpTls->setCurrentIndex(s->value(SKEY_SMTP_SslType2,0).toInt());
    int idx2 = s->value(SKEY_SMTP_Auth2,0).toInt();
    ui->cmbBackupSmtpAuth->setCurrentIndex(idx2);
    ui->editBackupSmtpLogin->setText(s->value(SKEY_SMTP_User2).toString());
    ui->editBackupSmtpPassword->setText(s->value(SKEY_SMTP_Pswd2).toString());
    on_cmbBackupAuthSelect(idx2);
    connect (ui->cmbBackupSmtpTls, SIGNAL(currentIndexChanged(int)),this,SLOT(onBackUpPortChange()));
    connect(ui->cmbBackupSmtpAuth, SIGNAL(currentIndexChanged(int)), this,SLOT(on_cmbBackupAuthSelect(int)));

    ui->gpShowStatusWindow->setChecked(s->value(SKEY_SMTP_ShowMailWin,1).toInt() == 1);
    ui->chkCloseOnDisconnect->setChecked(s->value(SKEY_SMTP_MailWinAutoClose,1).toInt() == 1);
    ui->spinCloseOnDisconnect->setValue(s->value(SKEY_SMTP_MailWinCloseAfter,6).toInt());
    ui->chkShowInLastPosition->setChecked(s->value(SKEY_SMTP_ShowMailWinInLastPos,1).toInt() == 1);
}

/******************************************************************/

void MailerSettingsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_SMTP_Server1,ui->cmbPrimarySmtpAddress->currentText());
    s->setValue(SKEY_SMTP_Port1,ui->spinPrimarySmtpPort->value());
    s->setValue(SKEY_SMTP_SslType1,ui->cmbPrimarySmtpTls->currentIndex());
    s->setValue(SKEY_SMTP_Auth1,ui->cmbPrimarySmtpAuth->currentIndex());
    s->setValue(SKEY_SMTP_User1,ui->editPrimarySmtpLogin->text());
    s->setValue(SKEY_SMTP_Pswd1,ui->editPrimarySmtpPassword->text());

    s->setValue(SKEY_SMTP_Server2,ui->cmbBackupSmtpAddress->currentText());
    s->setValue(SKEY_SMTP_Port2,ui->spinBackupSmtpPort->value());
    s->setValue(SKEY_SMTP_SslType2,ui->cmbBackupSmtpTls->currentIndex());
    s->setValue(SKEY_SMTP_Auth2,ui->cmbBackupSmtpAuth->currentIndex());
    s->setValue(SKEY_SMTP_User2,ui->editBackupSmtpLogin->text());
    s->setValue(SKEY_SMTP_Pswd2,ui->editBackupSmtpPassword->text());

    s->setValue(SKEY_SMTP_ShowMailWin,ui->gpShowStatusWindow->isChecked()?1:0);
    s->setValue(SKEY_SMTP_MailWinAutoClose,ui->chkCloseOnDisconnect->isChecked()?1:0);
    s->setValue(SKEY_SMTP_MailWinCloseAfter,ui->spinCloseOnDisconnect->value());
    s->setValue(SKEY_SMTP_ShowMailWinInLastPos,ui->chkShowInLastPosition->isChecked()?1:0);
}

/******************************************************************/

void MailerSettingsWidget::on_cmbPrimaryAuthSelect(int)
{
    int indexPrimary = ui->cmbPrimarySmtpAuth->currentIndex();
    if (indexPrimary == 0)
    {
        ui->lblPrimarySmtpLogin->setDisabled(true);
        ui->editPrimarySmtpLogin->setDisabled(true);
        ui->lblPrimarySmtpPassword->setDisabled(true);
        ui->editPrimarySmtpPassword->setDisabled(true);
    }
    else
    {
        ui->lblPrimarySmtpLogin->setEnabled(true);
        ui->editPrimarySmtpLogin->setEnabled(true);
        ui->lblPrimarySmtpPassword->setEnabled(true);
        ui->editPrimarySmtpPassword->setEnabled(true);
    }
}

/******************************************************************/

void MailerSettingsWidget::on_cmbBackupAuthSelect(int)
{
    int indexBackUp = ui->cmbBackupSmtpAuth->currentIndex();
    if (indexBackUp == 0)
    {
        ui->lblBackupSmtpLogin->setDisabled(true);
        ui->editBackupSmtpLogin->setDisabled(true);
        ui->lblBackupSmtpPassword->setDisabled(true);
        ui->editBackupSmtpPassword->setDisabled(true);
    }
    else
    {
        ui->lblBackupSmtpLogin->setEnabled(true);
        ui->editBackupSmtpLogin->setEnabled(true);
        ui->lblBackupSmtpPassword->setEnabled(true);
        ui->editBackupSmtpPassword->setEnabled(true);
    }
}

/******************************************************************/

} // namespace SDPO
