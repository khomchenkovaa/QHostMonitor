#include "qSendMessageToPagerSnppWidget.h"
#include "ui_qSendMessageToPagerSnppWidget.h"
#include "action/tSendMessageToPagerSnppAction.h"
#include "qOptionsForm.h"
#include "gData.h"
#include "io/ioMailProfileLoader.h"
#include "qMailProfilesDlg.h"

namespace SDPO {

/******************************************************************/

SendMessageToPagerSnppWidget::SendMessageToPagerSnppWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SendMessageToPagerSnppWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SendMessageToPagerSnppWidget::~SendMessageToPagerSnppWidget()
{
    delete ui;
}

/******************************************************************/

void SendMessageToPagerSnppWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::MsgPagerSnpp) {
        return;
    }
    SendMessageToPagerSnppAction *action = qobject_cast<SendMessageToPagerSnppAction *>(item);
    ui->cmbPagerId->setCurrentText(action->getPagerID());
    ui->cmbMailTemplate->setCurrentText(action->getMailTemplate());
    ui->cmbLevel->setCurrentText(action->getLevel());
    ui->chkAlert->setChecked(action->isAlert());
    ui->cmbServer->setCurrentText(action->getServer());
    ui->spinPort->setValue(action->getPort());
    ui->chkLoginAs->setChecked(action->isLoginAs());
    ui->lineLoginAs->setText(action->getLoginAsLogin());
    ui->linePassword->setText(action->getLoginAsPassword());
}

/******************************************************************/

void SendMessageToPagerSnppWidget::reset()
{
    ui->cmbMailTemplate->clear();
    foreach (const GMailProfile &profile, GData::mailProfiles) {
        ui->cmbMailTemplate->addItem(profile.name);
    }
}

/******************************************************************/

TestAction *SendMessageToPagerSnppWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::MsgPagerSnpp) {
        item = new SendMessageToPagerSnppAction();
    }
    SendMessageToPagerSnppAction *action = qobject_cast<SendMessageToPagerSnppAction *>(item);
    action->setPagerID(ui->cmbPagerId->currentText());
    action->setMailTemplate(ui->cmbMailTemplate->currentText());
    action->setLevel(ui->cmbLevel->currentText());
    action->setAlert(ui->chkAlert->isChecked());
    action->setServer(ui->cmbServer->currentText());
    action->setPort(ui->spinPort->value());
    action->setLoginAs(ui->chkLoginAs->isChecked());
    action->setLoginAsLogin(ui->lineLoginAs->text());
    action->setLoginAsPassword(ui->linePassword->text());
    return action;
}

/******************************************************************/

void SendMessageToPagerSnppWidget::on_btnMailTemplate_clicked()
{
    IOMailProfileLoader loader;
    MailProfilesDlg dlg;
    dlg.init(ui->cmbMailTemplate->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset();
        ui->cmbMailTemplate->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

} // namespace SDPO


