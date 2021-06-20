#include "qSmsSmppOptionsWidget.h"
#include "ui_qSmsSmppOptionsWidget.h"

using namespace SDPO;

/******************************************************************/

SmsSmppOptionsWidget::SmsSmppOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::SmsSmppOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SmsSmppOptionsWidget::~SmsSmppOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void SmsSmppOptionsWidget::init(QSettings *s)
{
    ui->editPrimaryHost->setText      (s->value(SKEY_SMSSMPP1_Host).toString());
    ui->spinPrimaryPort->setValue     (s->value(SKEY_SMSSMPP1_Port, SVAL_SMSSMPP1_Port).toInt());
    ui->editPrimarySystemId->setText  (s->value(SKEY_SMSSMPP1_ID).toString());
    ui->editPrimaryPassword->setText  (s->value(SKEY_SMSSMPP1_Pswd).toString());
    ui->editPrimaryAddress->setText   (s->value(SKEY_SMSSMPP1_SrcAddr).toString());
    ui->cmbPrimaryTon->setCurrentIndex(s->value(SKEY_SMSSMPP1_TON, SVAL_SMSSMPP1_TON).toInt());
    ui->cmbPrimaryNpi->setCurrentIndex(s->value(SKEY_SMSSMPP1_NPI, SVAL_SMSSMPP1_NPI).toInt());

    ui->editBackupHost->setText      (s->value(SKEY_SMSSMPP2_Host).toString());
    ui->spinBackupPort->setValue     (s->value(SKEY_SMSSMPP2_Port, SVAL_SMSSMPP2_Port).toInt());
    ui->editBackupSystemId->setText  (s->value(SKEY_SMSSMPP2_ID).toString());
    ui->editBackupPassword->setText  (s->value(SKEY_SMSSMPP2_Pswd).toString());
    ui->editBackupAddress->setText   (s->value(SKEY_SMSSMPP2_SrcAddr).toString());
    ui->cmbBackupTon->setCurrentIndex(s->value(SKEY_SMSSMPP2_TON, SVAL_SMSSMPP2_TON).toInt());
    ui->cmbBackupNpi->setCurrentIndex(s->value(SKEY_SMSSMPP2_NPI, SVAL_SMSSMPP2_NPI).toInt());
}

/******************************************************************/

void SmsSmppOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_SMSSMPP1_Host, ui->editPrimaryHost->text());
    s->setValue(SKEY_SMSSMPP1_Port, ui->spinPrimaryPort->value());
    s->setValue(SKEY_SMSSMPP1_ID, ui->editPrimarySystemId->text());
    s->setValue(SKEY_SMSSMPP1_Pswd, ui->editPrimaryPassword->text());
    s->setValue(SKEY_SMSSMPP1_SrcAddr, ui->editPrimaryAddress->text());
    s->setValue(SKEY_SMSSMPP1_TON, ui->cmbPrimaryTon->currentIndex());
    s->setValue(SKEY_SMSSMPP1_NPI, ui->cmbPrimaryNpi->currentIndex());

    s->setValue(SKEY_SMSSMPP2_Host, ui->editBackupHost->text());
    s->setValue(SKEY_SMSSMPP2_Port, ui->spinBackupPort->value());
    s->setValue(SKEY_SMSSMPP2_ID, ui->editBackupSystemId->text());
    s->setValue(SKEY_SMSSMPP2_Pswd, ui->editBackupPassword->text());
    s->setValue(SKEY_SMSSMPP2_SrcAddr, ui->editBackupAddress->text());
    s->setValue(SKEY_SMSSMPP2_TON, ui->cmbBackupTon->currentIndex());
    s->setValue(SKEY_SMSSMPP2_NPI, ui->cmbBackupNpi->currentIndex());
}

/******************************************************************/
