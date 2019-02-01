#include "qSendMessageToBeeperWidget.h"
#include "ui_qSendMessageToBeeperWidget.h"
#include "action/tSendMessageToBeeperAction.h"
#include "qOptionsForm.h"

namespace SDPO {

/******************************************************************/

SendMessageToBeeperWidget::SendMessageToBeeperWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SendMessageToBeeperWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SendMessageToBeeperWidget::~SendMessageToBeeperWidget()
{
    delete ui;
}

/******************************************************************/

void SendMessageToBeeperWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::MsgBeeper) {
        return;
    }
    SendMessageToBeeperAction *action = qobject_cast<SendMessageToBeeperAction *>(item);
    ui->cmbBeeper->setCurrentText(action->getBeeper());
    ui->spinDelay->setValue(action->getDelay());
    ui->cmbSendMessage->setCurrentText(action->getSendMessage());
    ui->cmbTerminationString->setCurrentText(action->getTerminationString());
}

/******************************************************************/

TestAction *SendMessageToBeeperWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::MsgBeeper) {
        item = new SendMessageToBeeperAction();
    }
    SendMessageToBeeperAction *action = qobject_cast<SendMessageToBeeperAction *>(item);
    action->setBeeper(ui->cmbBeeper->currentText());
    action->setDelay(ui->spinDelay->value());
    action->setSendMessage(ui->cmbSendMessage->currentText());
    action->setTerminationString(ui->cmbTerminationString->currentText());
    return action;
}

/******************************************************************/

} // namespace SDPO
