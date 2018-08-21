#include "qPagersOptionsWidget.h"
#include "ui_qPagersOptionsWidget.h"

namespace SDPO {

/******************************************************************/

PagersOptionsWidget::PagersOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::PagersOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

PagersOptionsWidget::~PagersOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void PagersOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::Pagers, Settings::pgDevice, QVariant("Auto select free TAPI device"));
        ui->cmbUseDevice->setCurrentText(value.toString());

    value = Settings::get(Settings::Pagers, Settings::pgBoudRate, QVariant("2400"));
        ui->cmbBaudRate->setCurrentText(value.toString());

    value = Settings::get(Settings::Pagers, Settings::pgInitStr, QVariant("AUTO"));
        ui->cmbModemInitString->setCurrentText(value.toString());

    value = Settings::get(Settings::Pagers, Settings::pgDialStr, QVariant("ATDT"));
        ui->cmbModemDialString->setCurrentText(value.toString());

    value = Settings::get(Settings::Pagers, Settings::pgShowWindow, QVariant(1));
        if (value.toInt() == 1)
            ui->chkShowStatusWindow->setChecked(true);
        else
            ui->chkShowStatusWindow->setChecked(false);

    value = Settings::get(Settings::Pagers, Settings::pgCloseWindow, QVariant(1));
        if (value.toInt() == 1)
            ui->chkCloseWindowOnDisconnect->setChecked(true);
        else
            ui->chkCloseWindowOnDisconnect->setChecked(false);

    value = Settings::get(Settings::Pagers, Settings::pgCloseDelay, QVariant(5));
        ui->spinCloseWindowOnDisconnect->setValue(value.toInt());

    value = Settings::get(Settings::Pagers, Settings::pgWaitFreeDevice, QVariant(1));
        if (value.toInt() == 1)
            ui->chkIfDeviceBusyWait->setChecked(true);
        else
            ui->chkIfDeviceBusyWait->setChecked(false);

    value = Settings::get(Settings::Pagers, Settings::pgWaitDeviceDelay, QVariant(15));
        ui->spinIfDeviceBusyWait->setValue(value.toInt());

}

/******************************************************************/

void PagersOptionsWidget::prepareToSave()
{
     Settings::set(Settings::Pagers, Settings::pgDevice) = QVariant(ui->cmbUseDevice->currentText());
     Settings::set(Settings::Pagers, Settings::pgBoudRate) = QVariant(ui->cmbBaudRate->currentText());
     Settings::set(Settings::Pagers, Settings::pgInitStr) = QVariant(ui->cmbModemInitString->currentText());
     Settings::set(Settings::Pagers, Settings::pgDialStr) = QVariant(ui->cmbModemDialString->currentText());
     Settings::set(Settings::Pagers, Settings::pgShowWindow) = QVariant(ui->chkShowStatusWindow->isChecked()?1:0);
     Settings::set(Settings::Pagers, Settings::pgCloseWindow) = QVariant(ui->chkCloseWindowOnDisconnect->isChecked()?1:0);
     Settings::set(Settings::Pagers, Settings::pgCloseDelay) = QVariant(ui->spinCloseWindowOnDisconnect->value());
     Settings::set(Settings::Pagers, Settings::pgWaitFreeDevice) = QVariant(ui->chkIfDeviceBusyWait->isChecked()?1:0);
     Settings::set(Settings::Pagers, Settings::pgWaitDeviceDelay) = QVariant(ui->spinIfDeviceBusyWait->value());
}

/******************************************************************/

} // namespace SDPO
