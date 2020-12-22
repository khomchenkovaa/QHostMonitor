#include "qSnmpSetWidget.h"
#include "ui_qSnmpSetWidget.h"
#include "action/tSnmpSetAction.h"
#include "gData.h"
#include "netsnmpsession.h"

using namespace SDPO;

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
    ui->cmbSnmpProfile->setCurrentText(action->getSnmpProfile());
    ui->spinRetries->setValue(action->getRetries());
    ui->cmbOid->setCurrentText(action->getOid());
    ui->cmbSetValue->setCurrentText(action->getSetValue());
}

/******************************************************************/

void SnmpSetWidget::reset()
{
    ui->cmbSnmpProfile->clear();
    ui->cmbSnmpProfile->addItems(SnmpProfile::names());
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
    action->setSnmpProfile(ui->cmbSnmpProfile->currentText());
    action->setRetries(ui->spinRetries->value());
    action->setOid(ui->cmbOid->currentText());
    action->setSetValue(ui->cmbSetValue->currentText());
    return action;
}

/******************************************************************/

void SnmpSetWidget::on_btnGetCurrentValue_clicked()
{
    ui->btnGetCurrentValue->setDisabled(true);

    // get values
    QString snmpProfile = ui->cmbSnmpProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    int timeout = ui->spinTimeout->value(); // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbAgentAddress->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();

    Q_UNUSED(timeout)


    NetSnmpSession ss;
    ss.setProfile(profile);
    ss.setRetries(retries);
    ss.setDestHost(host);
    SnmpValue value = ss.get(oid);
    ui->cmbSetValue->setCurrentText(value.val);

    ui->btnGetCurrentValue->setEnabled(true);
    ui->btnGetCurrentValue->setFocus();
}

/******************************************************************/



