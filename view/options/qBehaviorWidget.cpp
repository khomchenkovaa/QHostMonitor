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
    ui->chkBRecheckDependants->setChecked  (s->value(SKEY_HOSTMON_RecheckDependants, SVAL_HOSTMON_RecheckDependants).toInt());
    ui->spinBMastersLifetime->setValue     (s->value(SKEY_HOSTMON_MastersLifetime, SVAL_HOSTMON_MastersLifetime).toInt());
    ui->spinBMaxThreads->setValue          (s->value(SKEY_HOSTMON_MaxThreads, SVAL_HOSTMON_MaxThreads).toInt());

    ui->cmbBResetOnEditing->setCurrentIndex(s->value(SKEY_HOSTMON_RefreshMode, SVAL_HOSTMON_RefreshMode).toInt());
    ui->chkBResetOnPause->setChecked       (s->value(SKEY_HOSTMON_PauseResetIterations, SVAL_HOSTMON_PauseResetIterations).toInt());
    ui->chkBRequestForComment->setChecked  (s->value(SKEY_HOSTMON_CommentForDisabling, SVAL_HOSTMON_CommentForDisabling).toInt());
    ui->chkBResetOnDisabled->setChecked    (s->value(SKEY_HOSTMON_DisableResetIterations, SVAL_HOSTMON_DisableResetIterations).toInt());
}

/******************************************************************/

void BehaviorWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_HOSTMON_RecheckDependants, ui->chkBRecheckDependants->isChecked()?1:0);
    s->setValue(SKEY_HOSTMON_MastersLifetime, ui->spinBMastersLifetime->value());
    s->setValue(SKEY_HOSTMON_MaxThreads, ui->spinBMaxThreads->value());

    s->setValue(SKEY_HOSTMON_RefreshMode, ui->cmbBResetOnEditing->currentIndex());
    s->setValue(SKEY_HOSTMON_DisableResetIterations, ui->chkBResetOnDisabled->isChecked()?1:0);
    s->setValue(SKEY_HOSTMON_CommentForDisabling, ui->chkBRequestForComment->isChecked()?1:0);
    s->setValue(SKEY_HOSTMON_PauseResetIterations, ui->chkBResetOnPause->isChecked()?1:0);
}

/******************************************************************/

} // namespace SDPO
