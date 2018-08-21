#include "qRebootLocalMachineWidget.h"
#include "ui_qRebootLocalMachineWidget.h"
#include "action/tRebootLocalMachineAction.h"

namespace SDPO {

/******************************************************************/

RebootLocalMachineWidget::RebootLocalMachineWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::RebootLocalMachineWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

RebootLocalMachineWidget::~RebootLocalMachineWidget()
{
    delete ui;
}

/******************************************************************/

void RebootLocalMachineWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::RebootLocal) {
        return;
    }
    RebootLocalMachineAction *action = qobject_cast<RebootLocalMachineAction *>(item);
        ui->rdLogout->setChecked(action->isLogout());
        ui->rdReboot->setChecked(action->isReboot());
        ui->rdShutdown->setChecked(action->isShutdown());
        ui->rdPowerOff->setChecked(action->isPowerOff());
        ui->chkForceProcessesToTerminate->setChecked(action->isForceProcesses());
}

/******************************************************************/

TestAction *RebootLocalMachineWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::RebootLocal) {
            item = new RebootLocalMachineAction();
        }
    RebootLocalMachineAction *action = qobject_cast<RebootLocalMachineAction *>(item);
    action->setLogout(ui->rdLogout->isChecked());
    action->setReboot(ui->rdReboot->isChecked());
    action->setShutdown(ui->rdShutdown->isChecked());
    action->setPowerOff(ui->rdPowerOff->isChecked());
    action->setForceProcesses(ui->chkForceProcessesToTerminate->isChecked());
    return action;
}

/******************************************************************/

} //namespace SDPO
