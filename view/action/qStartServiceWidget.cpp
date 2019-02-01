#include "qStartServiceWidget.h"
#include "ui_qStartServiceWidget.h"
#include "action/tStartServiceAction.h"

namespace SDPO {

/******************************************************************/

StartServiceWidget::StartServiceWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::StartServiceWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

StartServiceWidget::~StartServiceWidget()
{
    delete ui;
}

/******************************************************************/

void StartServiceWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::ServiceStart) {
        return;
    }
    StartServiceAction *action = qobject_cast<StartServiceAction *>(item);
    ui->cmbStartServiceOn->setCurrentText(action->getStartServiceOn());
    ui->cmbServiceName->setCurrentText(action->getServiceName());
    ui->cmbParameters->setCurrentText(action->getParameters());
    ui->chkConnectAs->setChecked(action->isConnectAs());
        on_chkConnectStatus();
        connect(ui->chkConnectAs, SIGNAL(clicked()),this, SLOT(on_chkConnectStatus()));
    ui->cmbConnectAsLogin->setCurrentText(action->getConnectAsLogin());
    ui->lineConnectAsPassword->setText(action->getConnectAsPassword());
}

/******************************************************************/

TestAction *StartServiceWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::ServiceStart) {
        item = new StartServiceAction();
    }
    StartServiceAction *action = qobject_cast<StartServiceAction *>(item);
    action->setStartServiceOn(ui->cmbStartServiceOn->currentText());
    action->setServiceName(ui->cmbServiceName->currentText());
    action->setParameters(ui->cmbParameters->currentText());
    action->setConnectAs(ui->chkConnectAs->isChecked());
    action->setConnectAsLogin(ui->cmbConnectAsLogin->currentText());
    action->setConnectAsPassword(ui->lineConnectAsPassword->text());
    return action;
}

/******************************************************************/

void StartServiceWidget::on_chkConnectStatus()
{
    if (ui->chkConnectAs->isChecked()) {
        ui->cmbConnectAsLogin->setEnabled(true);
        ui->lineConnectAsPassword->setEnabled(true);
    } else {
        ui->cmbConnectAsLogin->setDisabled(true);
        ui->lineConnectAsPassword->setDisabled(true);
    }
}

/******************************************************************/

} // namespace SDPO
