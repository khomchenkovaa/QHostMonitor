#include "qDialupToTheNetworkWidget.h"
#include "ui_qDialupToTheNetworkWidget.h"
#include "action/tDialupToTheNetworkAction.h"

namespace SDPO {

/******************************************************************/

DialupToTheNetworkWidget::DialupToTheNetworkWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::DialupToTheNetworkWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

DialupToTheNetworkWidget::~DialupToTheNetworkWidget()
{
    delete ui;
}

/******************************************************************/

void DialupToTheNetworkWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::DialUpConnect) {
        return;
    }
    DialupToTheNetworkAction *action = qobject_cast<DialupToTheNetworkAction *>(item);
    ui->cmbDialupConnection->setCurrentText(action->getDialUpConnection());
    ui->cmbUserName->setCurrentText(action->getUserName());
    ui->linePassword->setText(action->getPassword());
    ui->chkSavePassword->setChecked(action->isSavePassword());
    ui->chkShowDialUpWindows->setChecked(action->isShowDialUpWindow());
    ui->spinRetries->setValue(action->getRetries());
}

/******************************************************************/

TestAction *DialupToTheNetworkWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::DialUpConnect) {
            item = new DialupToTheNetworkAction();
        }
    DialupToTheNetworkAction *action = qobject_cast<DialupToTheNetworkAction *>(item);
    action->setDialUpConnection(ui->cmbDialupConnection->currentText());
    action->setUserName(ui->cmbUserName->currentText());
    action->setPassword(ui->linePassword->text());
    action->setSavePassword(ui->chkSavePassword->isChecked());
    action->setShowDialUpWindow(ui->chkShowDialUpWindows->isChecked());
    action->setRetries(ui->spinRetries->value());
    return action;
}

/******************************************************************/

} // namespace SDPO
