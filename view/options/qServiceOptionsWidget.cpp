#include "qServiceOptionsWidget.h"
#include "ui_qServiceOptionsWidget.h"

namespace SDPO {

/******************************************************************/

ServiceOptionsWidget::ServiceOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::ServiceOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

ServiceOptionsWidget::~ServiceOptionsWidget()
{
    delete ui;
}

/******************************************************************/
void ServiceOptionsWidget::init(QSettings *s)
{
    if (s->value(SKEY_SERVICE_Logon,1).toInt() == 1) {
        ui->rbServiceLocalAccount->setChecked(true);
    } else {
        ui->rbServiceUseAccount->setChecked(true);
    }
    onLogOnAsChanged();
    connect(ui->rbServiceLocalAccount, SIGNAL(clicked()), this, SLOT(onLogOnAsChanged()));
    connect(ui->rbServiceUseAccount, SIGNAL(clicked()), this, SLOT(onLogOnAsChanged()));

    ui->editServiceUser->setText(s->value(SKEY_SERVICE_User).toString());
    ui->editServicePassword->setText(s->value(SKEY_SERVICE_Pswd).toString());
    ui->spinServiceStartupDelay->setValue(s->value(SKEY_SERVICE_Delay,0).toInt());

    if (s->value(SKEY_SERVICE_SaveMode,1).toInt() == 1) {
        ui->rbServiceSaveInHML->setChecked(true);
    } else {
        ui->rbServiceDiscardChanges->setChecked(true);
    }
}

/******************************************************************/

void ServiceOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_SERVICE_Logon,ui->rbServiceLocalAccount->isChecked()?1:0);
    s->setValue(SKEY_SERVICE_User,ui->editServiceUser->text());
    s->setValue(SKEY_SERVICE_Pswd,ui->editServicePassword->text());
    s->setValue(SKEY_SERVICE_Delay,ui->spinServiceStartupDelay->value());
    s->setValue(SKEY_SERVICE_SaveMode,ui->rbServiceSaveInHML->isChecked()?1:0);
}

/******************************************************************/

void ServiceOptionsWidget::onLogOnAsChanged()
{
    if(ui->rbServiceLocalAccount->isChecked()) {
         // disable
        ui->editServiceUser->setDisabled(true);
        ui->editServicePassword->setDisabled(true);
    } else {
        // enable
        ui->editServiceUser->setEnabled(true);
        ui->editServicePassword->setEnabled(true);
    }
}

/******************************************************************/

} // namespace SDPO


