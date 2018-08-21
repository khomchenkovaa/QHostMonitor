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

void SystemLogOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::Logging, Settings::SysLogFileName, QVariant());
        ui->editSystemLogFileName->setText(value.toString());

    value = Settings::get(Settings::Logging, Settings::LogSuccessActions, QVariant(0));
        if (value.toInt() == 1) {
            ui->chkSystemLogSuccessful->setChecked(true);
        } else {
            ui->chkSystemLogSuccessful->setChecked(false);
        }

    value = Settings::get(Settings::Logging, Settings::LogSuccessActions, QVariant(1));
        if (value.toInt() == 1) {
            ui->chkSystemLogFailed->setChecked(true);
        } else {
            ui->chkSystemLogFailed->setChecked(false);
        }
}

/******************************************************************/

void SystemLogOptionsWidget::prepareToSave()
{
   Settings::set(Settings::Logging, Settings::SysLogFileName) = QVariant(ui->editSystemLogFileName->text());
   Settings::set(Settings::Logging, Settings::LogSuccessActions) = QVariant(ui->chkSystemLogSuccessful->isChecked()?1:0);
   Settings::set(Settings::Logging, Settings::LogFailedActions) = QVariant(ui->chkSystemLogFailed->isChecked()?1:0);
}

/******************************************************************/

} // namespace SDPO

