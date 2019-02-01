#include "qSendMessageToIcqWidget.h"
#include "ui_qSendMessageToIcqWidget.h"
#include "action/tSendMessageToIcqAction.h"
#include "qOptionsForm.h"
#include "gData.h"
#include "io/ioMailProfileLoader.h"
#include "qMailProfilesDlg.h"

namespace SDPO {

/******************************************************************/

SendMessageToIcqWidget::SendMessageToIcqWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SendMessageToIcqWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SendMessageToIcqWidget::~SendMessageToIcqWidget()
{
    delete ui;
}

/******************************************************************/

void SendMessageToIcqWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::MsgIcq) {
        return;
    }
    SendMessageToIcqAction *action = qobject_cast<SendMessageToIcqAction *>(item);
    ui->cmbSendMessageToIcq->setCurrentText(action->getSendMessage());
    ui->cmbMessageTemplate->setCurrentText(action->getMsgTemplate());
}

/******************************************************************/

void SendMessageToIcqWidget::reset()
{
    ui->cmbMessageTemplate->clear();
    foreach (const GMailProfile &profile, GData::mailProfiles) {
        ui->cmbMessageTemplate->addItem(profile.name);
    }
}

/******************************************************************/

TestAction *SendMessageToIcqWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::MsgIcq) {
        item = new SendMessageToIcqAction();
    }
    SendMessageToIcqAction *action = qobject_cast<SendMessageToIcqAction *>(item);
    action->setSendMessage(ui->cmbSendMessageToIcq->currentText());
    action->setMsgTemplate(ui->cmbMessageTemplate->currentText());
    return action;
}

/******************************************************************/

void SendMessageToIcqWidget::on_btnMessageTemplate_clicked()
{
    IOMailProfileLoader loader;
    MailProfilesDlg dlg;
    dlg.init(ui->cmbMessageTemplate->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset();
        ui->cmbMessageTemplate->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

void SendMessageToIcqWidget::on_btnSetupIcqAccounts_clicked()
{
    OptionsForm dlg;
    dlg.setCurrentPage(16); // ICQ
    dlg.exec();

}

/******************************************************************/

} // namespace SDPO


