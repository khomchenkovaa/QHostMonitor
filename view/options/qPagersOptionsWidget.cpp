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
    ui->cmbUseDevice->setCurrentText(s->value(SKEY_PAGERS_Device,"Auto select free TAPI device").toString());
    ui->cmbBaudRate->setCurrentText(s->value(SKEY_PAGERS_BoudRate,"2400").toString());
    ui->cmbModemInitString->setCurrentText(s->value(SKEY_PAGERS_InitStr,"AUTO").toString());
    ui->cmbModemDialString->setCurrentText(s->value(SKEY_PAGERS_DialStr,"ATDT").toString());
    ui->chkShowStatusWindow->setChecked(s->value(SKEY_PAGERS_ShowWindow,1).toInt() == 1);
    ui->chkCloseWindowOnDisconnect->setChecked(s->value(SKEY_PAGERS_ClodeWindow,1).toInt() == 1);
    ui->spinCloseWindowOnDisconnect->setValue(s->value(SKEY_PAGERS_CloseDelay,5).toInt());
    ui->chkIfDeviceBusyWait->setChecked(s->value(SKEY_PAGERS_WaitFreeDevice,1).toInt() == 1);
    ui->spinIfDeviceBusyWait->setValue(s->value(SKEY_PAGERS_WaitDeviceDelay,15).toInt());
}

/******************************************************************/

void PagersOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_PAGERS_Device,ui->cmbUseDevice->currentText());
    s->setValue(SKEY_PAGERS_BoudRate,ui->cmbBaudRate->currentText());
    s->setValue(SKEY_PAGERS_InitStr,ui->cmbModemInitString->currentText());
    s->setValue(SKEY_PAGERS_DialStr,ui->cmbModemDialString->currentText());
    s->setValue(SKEY_PAGERS_ShowWindow,ui->chkShowStatusWindow->isChecked()?1:0);
    s->setValue(SKEY_PAGERS_ClodeWindow,ui->chkCloseWindowOnDisconnect->isChecked()?1:0);
    s->setValue(SKEY_PAGERS_CloseDelay,ui->spinCloseWindowOnDisconnect->value());
    s->setValue(SKEY_PAGERS_WaitFreeDevice,ui->chkIfDeviceBusyWait->isChecked()?1:0);
    s->setValue(SKEY_PAGERS_WaitDeviceDelay,ui->spinIfDeviceBusyWait->value());
}

/******************************************************************/

} // namespace SDPO
