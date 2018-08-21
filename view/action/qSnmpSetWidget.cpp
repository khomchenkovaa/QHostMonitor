#include "qSnmpSetWidget.h"
#include "ui_qSnmpSetWidget.h"
#include "action/tSnmpSetAction.h"

namespace SDPO {

/******************************************************************/

SnmpSetWidget::SnmpSetWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SnmpSetWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SnmpSetWidget::~SnmpSetWidget()
{
    delete ui;
}

/******************************************************************/

void SnmpSetWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::SnmpSet) {
        return;
    }
    SnmpSetAction *action = qobject_cast<SnmpSetAction *>(item);
    ui->cmbAgentAddress->setCurrentText(action->getAgentAddress());
    ui->spinTimeout->setValue(action->getTimeout());
    ui->cmbCommunity->setCurrentText(action->getCommunity());
    ui->spinRetries->setValue(action->getRetries());
    ui->cmbOid->setCurrentText(action->getOid());
    ui->cmbSetValue->setCurrentText(action->getSetValue());
}

/******************************************************************/

TestAction *SnmpSetWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::SnmpSet) {
        item = new SnmpSetAction();
    }
    SnmpSetAction *action = qobject_cast<SnmpSetAction *>(item);
    action->setAgentAddress(ui->cmbAgentAddress->currentText());
    action->setTimeout(ui->spinTimeout->value());
    action->setCommunity(ui->cmbCommunity->currentText());
    action->setRetries(ui->spinRetries->value());
    action->setOid(ui->cmbOid->currentText());
    action->setSetValue(ui->cmbSetValue->currentText());
    return action;
}

/******************************************************************/

} // namespace SDPO
