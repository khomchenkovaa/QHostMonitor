#include "qStopServiceWidget.h"
#include "ui_qStopServiceWidget.h"
#include "action/tStopServiceAction.h"

namespace SDPO {

/******************************************************************/

StopServiceWidget::StopServiceWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::StopServiceWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

StopServiceWidget::~StopServiceWidget()
{
    delete ui;
}

/******************************************************************/


void StopServiceWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::ServiceStop) {
        return;
    }
    StopServiceAction *action = qobject_cast<StopServiceAction *>(item);
    ui->cmbStopServiceOn->setCurrentText(action->getStopServiceOn());
    ui->cmbServiceName->setCurrentText(action->getServiceName());
    ui->cmbParameters->setCurrentText(action->getParameters());
    ui->chkConnectAs->setChecked(action->isConnectAs());
        on_chkConnectStatus();
        connect(ui->chkConnectAs, SIGNAL(clicked()),this, SLOT(on_chkConnectStatus()));
    ui->cmbConnectAsLogin->setCurrentText(action->getConnectAsLogin());
    ui->lineConnectAsPassword->setText(action->getConnectAsPassword());
}

/******************************************************************/

TestAction *StopServiceWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::ServiceStop) {
        item = new StopServiceAction();
    }
    StopServiceAction *action = qobject_cast<StopServiceAction *>(item);
    action->setStopServiceOn(ui->cmbStopServiceOn->currentText());
    action->setServiceName(ui->cmbServiceName->currentText());
    action->setParameters(ui->cmbParameters->currentText());
    action->setConnectAs(ui->chkConnectAs->isChecked());
    action->setConnectAsLogin(ui->cmbConnectAsLogin->currentText());
    action->setConnectAsPassword(ui->lineConnectAsPassword->text());
    return action;
}

/******************************************************************/

void StopServiceWidget::on_chkConnectStatus()
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
