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
void ServiceOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::Service, Settings::Logon, QVariant(1));
    if (value.toInt() == 1) {
        ui->rbServiceLocalAccount->setChecked(true);
    } else {
        ui->rbServiceUseAccount->setChecked(true);
    }
    onLogOnAsChanged();
    connect(ui->rbServiceLocalAccount, SIGNAL(clicked()), this, SLOT(onLogOnAsChanged()));
    connect(ui->rbServiceUseAccount, SIGNAL(clicked()), this, SLOT(onLogOnAsChanged()));

    value = Settings::get(Settings::Service, Settings::User, QVariant());
        ui->editServiceUser->setText(value.toString());

    value = Settings::get(Settings::Service, Settings::Pswd, QVariant());
        ui->editServicePassword->setText(value.toString());

    value = Settings::get(Settings::Service, Settings::Delay, QVariant(0));
        ui->spinServiceStartupDelay->setValue(value.toInt());

    value = Settings::get(Settings::Service, Settings::SaveMode, QVariant(1));
    if (value.toInt() == 1) {
        ui->rbServiceSaveInHML->setChecked(true);
    } else {
        ui->rbServiceDiscardChanges->setChecked(true);
    }

}

/******************************************************************/

void ServiceOptionsWidget::prepareToSave()
{
    Settings::set(Settings::Service, Settings::Logon) = QVariant(ui->rbServiceLocalAccount->isChecked()?1:0);
    Settings::set(Settings::Service, Settings::User) = QVariant(ui->editServiceUser->text());
    Settings::set(Settings::Service, Settings::Pswd) = QVariant(ui->editServicePassword->text());
    Settings::set(Settings::Service, Settings::Delay) = QVariant(ui->spinServiceStartupDelay->value());
    Settings::set(Settings::Service, Settings::SaveMode) = QVariant(ui->rbServiceSaveInHML->isChecked()?1:0);
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


