#include "qSystemLogOptionsWidget.h"
#include "ui_qSystemLogOptionsWidget.h"

namespace SDPO {

/******************************************************************/

SystemLogOptionsWidget::SystemLogOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::SystemLogOptionsWidget)
{
    ui->setupUi(this);
    ui->boxUserOperationsLog->setDisabled(true);
}

/******************************************************************/

SystemLogOptionsWidget::~SystemLogOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void SystemLogOptionsWidget::on_btnSystemLogFileName_clicked()
{

}

/******************************************************************/

void SystemLogOptionsWidget::init(QSettings *s)
{
    ui->editSystemLogFileName->setText    (s->value(SKEY_LOGGING_SysLogFileName).toString());
    ui->chkSystemLogSuccessful->setChecked(s->value(SKEY_LOGGING_LogSuccessActions, SVAL_LOGGING_LogSuccessActions).toInt());
    ui->chkSystemLogFailed->setChecked    (s->value(SKEY_LOGGING_LogFailedActions, SVAL_LOGGING_LogFailedActions).toInt());
}

/******************************************************************/

void SystemLogOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_LOGGING_SysLogFileName, ui->editSystemLogFileName->text());
    s->setValue(SKEY_LOGGING_LogSuccessActions, ui->chkSystemLogSuccessful->isChecked()?1:0);
    s->setValue(SKEY_LOGGING_LogFailedActions, ui->chkSystemLogFailed->isChecked()?1:0);
}

/******************************************************************/

} // namespace SDPO

