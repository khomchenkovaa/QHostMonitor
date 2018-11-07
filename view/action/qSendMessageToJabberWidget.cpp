#include "qSendMessageToJabberWidget.h"
#include "ui_qSendMessageToJabberWidget.h"
#include "qOptionsForm.h"
#include "action/tSendMessageToJabberAction.h"
#include "gData.h"
#include "io/ioMailProfileLoader.h"
#include "qMailProfilesDlg.h"

namespace SDPO {

/******************************************************************/

SendMessageToJabberWidget::SendMessageToJabberWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SendMessageToJabberWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SendMessageToJabberWidget::~SendMessageToJabberWidget()
{
    delete ui;
}

/******************************************************************/

void SendMessageToJabberWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::MsgJabber) {
        return;
    }
    SendMessageToJabberAction *action = qobject_cast<SendMessageToJabberAction *>(item);
    ui->cmbSendMessageToJabber->setCurrentText(action->getSendMessage());
    ui->cmbMessageTemplate->setCurrentText(action->getMsgTemplate());
}

/******************************************************************/

void SendMessageToJabberWidget::reset()
{
    ui->cmbMessageTemplate->clear();
    foreach (const GMailProfile &profile, GData::mailProfiles) {
        ui->cmbMessageTemplate->addItem(profile.name);
    }
}

/******************************************************************/

TestAction *SendMessageToJabberWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::MsgJabber) {
        item = new SendMessageToJabberAction();
    }
    SendMessageToJabberAction *action = qobject_cast<SendMessageToJabberAction *>(item);
    action->setSendMessage(ui->cmbSendMessageToJabber->currentText());
    action->setMsgTemplate(ui->cmbMessageTemplate->currentText());
    return action;
}

/******************************************************************/

void SendMessageToJabberWidget::on_btnSetupJabberAccounts_clicked()
{
    OptionsForm dlg;
    dlg.setCurrentPage(17); // Jabber
    dlg.exec();

}

/******************************************************************/

void SendMessageToJabberWidget::on_btnMessageTemplate_clicked()
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

} // namespace SDPO


