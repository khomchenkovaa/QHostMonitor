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

void PagersOptionsWidget::init(QSettings *s)
{
    ui->cmbUseDevice->setCurrentText          (s->value(SKEY_PAGERS_Device, SVAL_PAGERS_Device).toString());
    ui->cmbBaudRate->setCurrentText           (s->value(SKEY_PAGERS_BoudRate, SVAL_PAGERS_BoudRate).toString());
    ui->cmbModemInitString->setCurrentText    (s->value(SKEY_PAGERS_InitStr, SVAL_PAGERS_InitStr).toString());
    ui->cmbModemDialString->setCurrentText    (s->value(SKEY_PAGERS_DialStr, SVAL_PAGERS_DialStr).toString());
    ui->chkShowStatusWindow->setChecked       (s->value(SKEY_PAGERS_ShowWindow, SVAL_PAGERS_ShowWindow).toInt());
    ui->chkCloseWindowOnDisconnect->setChecked(s->value(SKEY_PAGERS_CloseWindow, SVAL_PAGERS_CloseWindow).toInt());
    ui->spinCloseWindowOnDisconnect->setValue (s->value(SKEY_PAGERS_CloseDelay, SVAL_PAGERS_CloseDelay).toInt());
    ui->chkIfDeviceBusyWait->setChecked       (s->value(SKEY_PAGERS_WaitFreeDevice, SVAL_PAGERS_WaitFreeDevice).toInt());
    ui->spinIfDeviceBusyWait->setValue        (s->value(SKEY_PAGERS_WaitDeviceDelay, SVAL_PAGERS_WaitDeviceDelay).toInt());
}

/******************************************************************/

void PagersOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_PAGERS_Device,ui->cmbUseDevice->currentText());
    s->setValue(SKEY_PAGERS_BoudRate,ui->cmbBaudRate->currentText());
    s->setValue(SKEY_PAGERS_InitStr,ui->cmbModemInitString->currentText());
    s->setValue(SKEY_PAGERS_DialStr,ui->cmbModemDialString->currentText());
    s->setValue(SKEY_PAGERS_ShowWindow,ui->chkShowStatusWindow->isChecked()?1:0);
    s->setValue(SKEY_PAGERS_CloseWindow,ui->chkCloseWindowOnDisconnect->isChecked()?1:0);
    s->setValue(SKEY_PAGERS_CloseDelay,ui->spinCloseWindowOnDisconnect->value());
    s->setValue(SKEY_PAGERS_WaitFreeDevice,ui->chkIfDeviceBusyWait->isChecked()?1:0);
    s->setValue(SKEY_PAGERS_WaitDeviceDelay,ui->spinIfDeviceBusyWait->value());
}

/******************************************************************/

} // namespace SDPO
