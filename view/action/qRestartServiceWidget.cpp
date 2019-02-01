#include "qRestartServiceWidget.h"
#include "ui_qRestartServiceWidget.h"
#include "action/tRestartServiceAction.h"

namespace SDPO {

/******************************************************************/

RestartServiceWidget::RestartServiceWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::RestartServiceWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

RestartServiceWidget::~RestartServiceWidget()
{
    delete ui;
}

/******************************************************************/

void RestartServiceWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::ServiceRestart) {
        return;
    }
    RestartServiceAction *action = qobject_cast<RestartServiceAction *>(item);
    ui->cmbRestartServiceOn->setCurrentText(action->getRestartServiceOn());
    ui->cmbServiceName->setCurrentText(action->getServiceName());
    ui->chkDoNotStartService->setChecked(action->isDoNotStartService());
    ui->chkConnectAs->setChecked(action->isConnectAs());
        on_chkConnectStatus();
        connect(ui->chkConnectAs, SIGNAL(clicked()),this, SLOT(on_chkConnectStatus()));
    ui->cmbConnectAsLogin->setCurrentText(action->getConnectAsLogin());
    ui->lineConnectAsPassword->setText(action->getConnectAsPassword());
}

/******************************************************************/

TestAction *RestartServiceWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::ServiceRestart) {
        item = new RestartServiceAction();
    }
    RestartServiceAction *action = qobject_cast<RestartServiceAction *>(item);
    action->setRestartServiceOn(ui->cmbRestartServiceOn->currentText());
    action->setServiceName(ui->cmbServiceName->currentText());
    action->setDoNotStartService(ui->chkDoNotStartService->isChecked());
    action->setConnectAs(ui->chkConnectAs->isChecked());
    action->setConnectAsLogin(ui->cmbConnectAsLogin->currentText());
    action->setConnectAsPassword(ui->lineConnectAsPassword->text());
    return action;
}

/******************************************************************/

void RestartServiceWidget::on_chkConnectStatus()
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
