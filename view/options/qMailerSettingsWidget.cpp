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

void MailerSettingsWidget::ShowMessagePrimaryPortChange()
{
   int PrimaryTlsIndx =  ui->cmbPrimarySmtpTls->currentIndex();
   int PrimaryPort = ui->spinPrimarySmtpPort->value();
       if ( PrimaryTlsIndx == 0 && PrimaryPort != 25 )
       {   QMessageBox :: StandardButton reply;
           reply = QMessageBox::warning(this,QObject::tr("Confirm"),  "Would you like to change port to #25", QMessageBox::Ok | QMessageBox::Cancel);
           if (reply == QMessageBox::Ok) {
                ui->spinPrimarySmtpPort->setValue(25);
           }
       }
       else if (PrimaryTlsIndx == 1 && PrimaryPort != 465)
       {   QMessageBox :: StandardButton reply;
           reply = QMessageBox::warning(this,QObject::tr("Hello"),  "Would you like to change port to #465", QMessageBox::Ok | QMessageBox::Cancel);
           if (reply == QMessageBox::Ok) {
                ui->spinPrimarySmtpPort->setValue(465);
           }
       }
       else if (PrimaryTlsIndx == 2 && PrimaryPort != 587)
       {
           QMessageBox :: StandardButton reply;
           reply =QMessageBox::warning(this,QObject::tr("Hello"),  "Would you like to change port to #587", QMessageBox::Ok | QMessageBox::Cancel);
           if (reply == QMessageBox::Ok) {
                ui->spinPrimarySmtpPort->setValue(587);
           }
       }
}

/******************************************************************/

void MailerSettingsWidget::ShowMessageBackUpPortChange()
{
    {
       int BackupTlsIndx =  ui->cmbBackupSmtpTls->currentIndex();
       int BackupPort = ui->spinBackupSmtpPort->value();
           if ( BackupTlsIndx == 0 && BackupPort != 25 )
           {   QMessageBox :: StandardButton reply;
               reply = QMessageBox::warning(this,QObject::tr("Confirm"),  "Would you like to change port to #25", QMessageBox::Ok | QMessageBox::Cancel);
               if (reply == QMessageBox::Ok) {
                    ui->spinBackupSmtpPort->setValue(25);
               }
           }
           else if (BackupTlsIndx == 1 && BackupPort != 465)
           {   QMessageBox :: StandardButton reply;
               reply = QMessageBox::warning(this,QObject::tr("Hello"),  "Would you like to change port to #465", QMessageBox::Ok | QMessageBox::Cancel);
               if (reply == QMessageBox::Ok) {
                    ui->spinBackupSmtpPort->setValue(465);
               }
           }
           else if (BackupTlsIndx == 2 && BackupPort != 587)
           {
               QMessageBox :: StandardButton reply;
               reply =QMessageBox::warning(this,QObject::tr("Hello"),  "Would you like to change port to #587", QMessageBox::Ok | QMessageBox::Cancel);
               if (reply == QMessageBox::Ok) {
                    ui->spinBackupSmtpPort->setValue(587);
               }
           }
    }
}

/******************************************************************/

void MailerSettingsWidget::init()
{
    QVariant value = Settings::get(Settings::SMTP, Settings::SMTPServer, QVariant("smtp.mail.yahoo.com"));
        ui->cmbPrimarySmtpAddress->setCurrentText(value.toString());

    value = Settings::get(Settings::SMTP, Settings::SMTPPort, QVariant(25));
        ui->spinPrimarySmtpPort->setValue(value.toInt());

    value = Settings::get(Settings::SMTP, Settings::SSLType1, QVariant(0));
        ui->cmbPrimarySmtpTls->setCurrentIndex(value.toInt());
        connect (ui->cmbPrimarySmtpTls, SIGNAL(currentIndexChanged(int)),this,SLOT(ShowMessagePrimaryPortChange()));

    value = Settings::get(Settings::SMTP, Settings::Authentication1, QVariant(0));
        ui->cmbPrimarySmtpAuth->setCurrentIndex(value.toInt());
        on_cmbPrimaryAuthSelect(value.toInt());
        connect(ui->cmbPrimarySmtpAuth, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cmbPrimaryAuthSelect(int)));

    value = Settings::get(Settings::SMTP, Settings::Username1, QVariant());
        ui->editPrimarySmtpLogin->setText(value.toString());

    value = Settings::get(Settings::SMTP, Settings::Password1, QVariant());
        ui->editPrimarySmtpPassword->setText(value.toString());

    value = Settings::get(Settings::SMTP, Settings::SMTPServer2, QVariant("smtp.mail.yahoo.com"));
        ui->cmbBackupSmtpAddress->setCurrentText(value.toString());

    value = Settings::get(Settings::SMTP, Settings::SMTPPort2, QVariant(25));
        ui->spinBackupSmtpPort->setValue(value.toInt());

    value = Settings::get(Settings::SMTP, Settings::SSLType2, QVariant(0));
        ui->cmbBackupSmtpTls->setCurrentIndex(value.toInt());
        connect (ui->cmbBackupSmtpTls, SIGNAL(currentIndexChanged(int)),this,SLOT(ShowMessageBackUpPortChange()));

    value = Settings::get(Settings::SMTP, Settings::Authentication2, QVariant(0));
        ui->cmbBackupSmtpAuth->setCurrentIndex(value.toInt());
        on_cmbBackupAuthSelect(value.toInt());
        connect(ui->cmbBackupSmtpAuth, SIGNAL(currentIndexChanged(int)), this,SLOT(on_cmbBackupAuthSelect(int)));

    value = Settings::get(Settings::SMTP, Settings::Username2, QVariant());
        ui->editBackupSmtpLogin->setText(value.toString());

    value = Settings::get(Settings::SMTP, Settings::Password2, QVariant());
        ui->editBackupSmtpPassword->setText(value.toString());

    value = Settings::get(Settings::SMTP, Settings::ShowMailWin, QVariant(1));
        if (value.toInt() == 1)
            ui->gpShowStatusWindow->setChecked(true);
        else
            ui->gpShowStatusWindow->setChecked(false);

    value = Settings::get(Settings::SMTP, Settings::MailWinAutoClose, QVariant(1));
        if (value.toInt() == 1)
            ui->chkCloseOnDisconnect->setChecked(true);
        else
            ui->chkCloseOnDisconnect->setChecked(false);

    value = Settings::get(Settings::SMTP, Settings::MailWinCloseAfter, QVariant(6));
        ui->spinCloseOnDisconnect->setValue(value.toInt());

    value = Settings::get(Settings::SMTP, Settings::ShowMailWinInLastPos, QVariant(1));
        if (value.toInt() == 1)
            ui->chkShowInLastPosition->setChecked(true);
        else
            ui->chkShowInLastPosition->setChecked(false);

}

/******************************************************************/

void MailerSettingsWidget::prepareToSave()
{
      Settings::set(Settings::SMTP, Settings::SMTPServer) = QVariant(ui->cmbPrimarySmtpAddress->currentText());
      Settings::set(Settings::SMTP, Settings::SMTPPort) = QVariant(ui->spinPrimarySmtpPort->value());
      Settings::set(Settings::SMTP, Settings::SSLType1) = QVariant(ui->cmbPrimarySmtpTls->currentIndex());
      Settings::set(Settings::SMTP, Settings::Authentication1) = QVariant(ui->cmbPrimarySmtpAuth->currentIndex());
      Settings::set(Settings::SMTP, Settings::Username1) = QVariant(ui->editPrimarySmtpLogin->text());
      Settings::set(Settings::SMTP, Settings::Password1) = QVariant(ui->editPrimarySmtpPassword->text());
      Settings::set(Settings::SMTP, Settings::SMTPServer2) = QVariant(ui->cmbBackupSmtpAddress->currentText());
      Settings::set(Settings::SMTP, Settings::SMTPPort2) = QVariant(ui->spinBackupSmtpPort->value());
      Settings::set(Settings::SMTP, Settings::SSLType2) = QVariant(ui->cmbBackupSmtpTls->currentIndex());
      Settings::set(Settings::SMTP, Settings::Authentication2) = QVariant(ui->cmbBackupSmtpAuth->currentIndex());
      Settings::set(Settings::SMTP, Settings::Username2) = QVariant(ui->editBackupSmtpLogin->text());
      Settings::set(Settings::SMTP, Settings::Password2) = QVariant(ui->editBackupSmtpPassword->text());
      Settings::set(Settings::SMTP, Settings::ShowMailWin) = QVariant(ui->gpShowStatusWindow->isChecked()?1:0);
      Settings::set(Settings::SMTP, Settings::MailWinAutoClose) = QVariant(ui->chkCloseOnDisconnect->isChecked()?1:0);
      Settings::set(Settings::SMTP, Settings::MailWinCloseAfter) = QVariant(ui->spinCloseOnDisconnect->value());
      Settings::set(Settings::SMTP, Settings::ShowMailWinInLastPos) = QVariant(ui->chkShowInLastPosition->isChecked()?1:0);

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
