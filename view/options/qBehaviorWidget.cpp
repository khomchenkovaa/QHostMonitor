#include "qBehaviorWidget.h"
#include "ui_qBehaviorWidget.h"

namespace SDPO {

/******************************************************************/

BehaviorWidget::BehaviorWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::BehaviorWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

BehaviorWidget::~BehaviorWidget()
{
    delete ui;
}

/******************************************************************/

void BehaviorWidget::init()
{
    QVariant value = Settings::get(Settings::HostMon, Settings::RefreshMode, QVariant(2));
        ui->cmbBResetOnEditing->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::HostMon, Settings::MaxThreads, QVariant(32));
        ui->spinBMaxThreads->setValue(value.toInt());

    value = Settings::get(Settings::HostMon, Settings::MastersLifetime, QVariant(60));
        ui->spinBMastersLifetime->setValue(value.toInt());

    value = Settings::get(Settings::HostMon, Settings::RecheckDependants, QVariant(0));
        if (value.toInt() == 1) {
            ui->chkBRecheckDependants->setChecked(true);
        } else {
            ui->chkBRecheckDependants->setChecked(false);
        }

    value = Settings::get(Settings::HostMon, Settings::CommentForDisabling, QVariant(0));
        if (value.toInt() == 1) {
            ui->chkBRequestForComment->setChecked(true);
        } else {
            ui->chkBRequestForComment->setChecked(false);
    }

    value = Settings::get(Settings::Misc, Settings::DisableResetIterations, QVariant(0));
        if (value.toInt() == 1) {
            ui->chkBResetOnDisabled->setChecked(true);
        } else {
            ui->chkBResetOnDisabled->setChecked(false);
        }

    value = Settings::get(Settings::Misc, Settings::PauseResetIterations, QVariant(0));
        if (value.toInt() == 1) {
            ui->chkBResetOnPause->setChecked(true);
        } else {
            ui->chkBResetOnPause->setChecked(false);
        }

}

/******************************************************************/

void BehaviorWidget::prepareToSave()
{
    Settings::set(Settings::HostMon, Settings::RefreshMode) = QVariant(ui->cmbBResetOnEditing->currentIndex());
    Settings::set(Settings::HostMon, Settings::MaxThreads) = QVariant(ui->spinBMaxThreads->value());
    Settings::set(Settings::HostMon, Settings::MastersLifetime) = QVariant(ui->spinBMastersLifetime->value());
    Settings::set(Settings::HostMon, Settings::RecheckDependants) = QVariant(ui->chkBRecheckDependants->isChecked()?1:0);
    Settings::set(Settings::HostMon, Settings::CommentForDisabling) = QVariant(ui->chkBRequestForComment->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::DisableResetIterations) = QVariant(ui->chkBResetOnDisabled->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::PauseResetIterations) = QVariant(ui->chkBResetOnPause->isChecked()?1:0);

}

/******************************************************************/

} // namespace SDPO
