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

void BehaviorWidget::init(QSettings *s)
{
    ui->cmbBResetOnEditing->setCurrentIndex(s->value(SKEY_HOSTMON_RefreshMode,2).toInt());
    ui->spinBMaxThreads->setValue(s->value(SKEY_HOSTMON_MaxThreads,32).toInt());
    ui->spinBMastersLifetime->setValue(s->value(SKEY_HOSTMON_MastersLifetime,60).toInt());
    ui->chkBRecheckDependants->setChecked(s->value(SKEY_HOSTMON_RecheckDependants,0).toInt() == 1);
    ui->chkBRequestForComment->setChecked(s->value(SKEY_HOSTMON_CommentForDisabling,0).toInt() == 1);
    ui->chkBResetOnDisabled->setChecked(s->value(SKEY_HOSTMON_DisableResetIterations,0).toInt() == 1);
    ui->chkBResetOnPause->setChecked(s->value(SKEY_HOSTMON_PauseResetIterations,0).toInt() == 1);
}

/******************************************************************/

void BehaviorWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_HOSTMON_RefreshMode, ui->cmbBResetOnEditing->currentIndex());
    s->setValue(SKEY_HOSTMON_MaxThreads, ui->spinBMaxThreads->value());
    s->setValue(SKEY_HOSTMON_MastersLifetime, ui->spinBMastersLifetime->value());
    s->setValue(SKEY_HOSTMON_RecheckDependants, ui->chkBRecheckDependants->isChecked()?1:0);
    s->setValue(SKEY_HOSTMON_CommentForDisabling, ui->chkBRequestForComment->isChecked()?1:0);
    s->setValue(SKEY_HOSTMON_DisableResetIterations, ui->chkBResetOnDisabled->isChecked()?1:0);
    s->setValue(SKEY_HOSTMON_PauseResetIterations, ui->chkBResetOnPause->isChecked()?1:0);
}

/******************************************************************/

} // namespace SDPO
