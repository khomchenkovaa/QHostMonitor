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
    switch(action->getShutdownMethod()) {
    case RebootLocalMachineAction::ST_LOGOUT:
        ui->rdLogout->setChecked(true);
        break;
    case RebootLocalMachineAction::ST_REBOOT:
        ui->rdReboot->setChecked(true);
        break;
    case RebootLocalMachineAction::ST_SHUTDOWN:
        ui->rdShutdown->setChecked(true);
        break;
    case RebootLocalMachineAction::ST_POWEROFF:
        ui->rdPowerOff->setChecked(true);
        break;
    }
    ui->chkForceProcessesToTerminate->setChecked(action->isForceProcesses());
}

/******************************************************************/

TestAction *RebootLocalMachineWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::RebootLocal) {
            item = new RebootLocalMachineAction();
        }
    RebootLocalMachineAction *action = qobject_cast<RebootLocalMachineAction *>(item);
    if (ui->rdLogout->isChecked()) {
        action->setShutdownMethod(RebootLocalMachineAction::ST_LOGOUT);
    } else if (ui->rdReboot->isChecked()) {
        action->setShutdownMethod(RebootLocalMachineAction::ST_REBOOT);
    } else if (ui->rdShutdown->isChecked()) {
        action->setShutdownMethod(RebootLocalMachineAction::ST_SHUTDOWN);
    } else if (ui->rdPowerOff->isChecked()) {
        action->setShutdownMethod(RebootLocalMachineAction::ST_POWEROFF);
    }
    action->setForceProcesses(ui->chkForceProcessesToTerminate->isChecked());
    return action;
}

/******************************************************************/

} //namespace SDPO
