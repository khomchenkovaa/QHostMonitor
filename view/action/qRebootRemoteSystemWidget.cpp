#include "qRebootRemoteSystemWidget.h"
#include "ui_qRebootRemoteSystemWidget.h"
#include "action/tRebootRemoteSystemAction.h"

namespace SDPO {

/******************************************************************/

RebootRemoteSystemWidget::RebootRemoteSystemWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::RebootRemoteSystemWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

RebootRemoteSystemWidget::~RebootRemoteSystemWidget()
{
    delete ui;
}

/******************************************************************/

void RebootRemoteSystemWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::RebootRemote) {
        return;
    }
    RebootRemoteSystemAction *action = qobject_cast<RebootRemoteSystemAction *>(item);
    ui->cmbComputerName->setCurrentText(action->getComputerName());
    ui->cmbMessageToDisplay->setCurrentText(action->getMessageToDisplay());
    ui->spinParametrs->setValue(action->getTimeToDisplay());
    ui->cmbMethod->setCurrentText(action->getMethod());
    ui->chkForceProcesses->setChecked(action->isForceProcesses());
}

/******************************************************************/

TestAction *RebootRemoteSystemWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::RebootRemote) {
        item = new RebootRemoteSystemAction();
    }
    RebootRemoteSystemAction *action = qobject_cast<RebootRemoteSystemAction *>(item);
    action->setComputerName(ui->cmbComputerName->currentText());
    action->setMessageToDisplay(ui->cmbMessageToDisplay->currentText());
    action->setTimeToDisplay(ui->spinParametrs->value());
    action->setMethod(ui->cmbMethod->currentText());
    action->setForceProcesses(ui->chkForceProcesses->isChecked());
    return action;
}

/******************************************************************/

} // namespace SDPO
