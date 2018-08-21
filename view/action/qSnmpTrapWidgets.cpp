#include "qSnmpTrapWidgets.h"
#include "ui_qSnmpTrapWidgets.h"
#include "action/tSnmpTrapAction.h"

namespace SDPO {

/******************************************************************/

SnmpTrapWidgets::SnmpTrapWidgets(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SnmpTrapWidgets)
{
    ui->setupUi(this);
}

/******************************************************************/

SnmpTrapWidgets::~SnmpTrapWidgets()
{
    delete ui;
}

/******************************************************************/

void SnmpTrapWidgets::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::SnmpTrap) {
        return;
    }
    SnmpTrapAction *action = qobject_cast<SnmpTrapAction *>(item);
    ui->cmbDestAddress->setCurrentText(action->getDestAddress());
    ui->cmbCommunity->setCurrentText(action->getCommunity());
    ui->cmbAgentAddress->setCurrentText(action->getAgentAddress());
    ui->cmbEnterprise->setCurrentText(action->getEnterprise());
    ui->cmbTrapType->setCurrentText(action->getTrapType());
    ui->spinSpecific->setValue(action->getSpecific());
    ui->cmbMibOid->setCurrentText(action->getMibOid());
    ui->cmbMibValue->setCurrentText(action->getMibValue());
    ui->cmbMibType->setCurrentText(action->getMibType());
}

/******************************************************************/

TestAction *SnmpTrapWidgets::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::SnmpTrap) {
        item = new SnmpTrapAction();
    }
    SnmpTrapAction *action = qobject_cast<SnmpTrapAction *>(item);
    action->setDestAddress(ui->cmbDestAddress->currentText());
    action->setCommunity(ui->cmbCommunity->currentText());
    action->setAgentAddress(ui->cmbAgentAddress->currentText());
    action->setEnterprise(ui->cmbEnterprise->currentText());
    action->setTrapType(ui->cmbTrapType->currentText());
    action->setSpecific(ui->spinSpecific->value());
    action->setMibOid(ui->cmbMibOid->currentText());
    action->setMibValue(ui->cmbMibValue->currentText());
    action->setMibType(ui->cmbMibType->currentText());
    return action;
}

/******************************************************************/

} // namespace SDPO
