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

void IcqOptionsWidget::init(QSettings *s)
{
    ui->cmbPrimaryIcqUin->setCurrentText(s->value(SKEY_ICQ_PrimaryUIN).toString());
    ui->editPrimaryIcqPassword->setText(s->value(SKEY_ICQ_PrimaryPswd).toString());
    ui->cmbBackupIcqUin->setCurrentText(s->value(SKEY_ICQ_BackupUIN).toString());
    ui->editBackupIcqPassword->setText(s->value(SKEY_ICQ_BackupPswd).toString());
}

/******************************************************************/

void IcqOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_ICQ_PrimaryUIN,ui->cmbPrimaryIcqUin->currentText());
    s->setValue(SKEY_ICQ_PrimaryPswd,ui->editPrimaryIcqPassword->text());
    s->setValue(SKEY_ICQ_BackupUIN,ui->cmbBackupIcqUin->currentText());
    s->setValue(SKEY_ICQ_BackupPswd,ui->editBackupIcqPassword->text());
}

/******************************************************************/

} // namespace SDPO


