#include "qSendMessageToPagerTapWidget.h"
#include "ui_qSendMessageToPagerTapWidget.h"
#include "action/tSendMessageToPagerTapAction.h"
#include "gData.h"
#include "global/ioMailProfileLoader.h"
#include "qMailProfilesDlg.h"
#include "qOptionsForm.h"

namespace SDPO {

/******************************************************************/

SendMessageToPagerTapWidget::SendMessageToPagerTapWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SendMessageToPagerTapWidget)
{
    ui->setupUi(this);
    reset();
}

/******************************************************************/

SendMessageToPagerTapWidget::~SendMessageToPagerTapWidget()
{
    delete ui;
}

/******************************************************************/

void SendMessageToPagerTapWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::MsgPagerTap) {
        return;
    }
    SendMessageToPagerTapAction *action = qobject_cast<SendMessageToPagerTapAction *>(item);
    ui->cmbAccessNumber->setCurrentText(action->getAccessNumber());
    ui->linePassword->setText(action->getPassword());
    ui->spinMaxCharacters->setValue(action->getMaxCharacter());
    ui->cmbParity->setCurrentText(action->getParity());
    ui->cmbPagerId->setCurrentText(action->getPagerId());
    ui->cmbMsgTemplate->setCurrentText(action->getMsgTemplate());
}

/******************************************************************/

void SendMessageToPagerTapWidget::reset()
{
    ui->cmbMsgTemplate->clear();
    foreach (const GMailProfile &profile, GData::mailProfiles) {
        ui->cmbMsgTemplate->addItem(profile.name);
    }
}

/******************************************************************/

TestAction *SendMessageToPagerTapWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::MsgPagerTap) {
        item = new SendMessageToPagerTapAction();
    }
    SendMessageToPagerTapAction *action = qobject_cast<SendMessageToPagerTapAction *>(item);
    action->setAccessNumber(ui->cmbAccessNumber->currentText());
    action->setPassword(ui->linePassword->text());
    action->setMaxCharacter(ui->spinMaxCharacters->value());
    action->setParity(ui->cmbParity->currentText());
    action->setPagerId(ui->cmbPagerId->currentText());
    action->setMsgTemplate(ui->cmbMsgTemplate->currentText());
    return action;
}

/******************************************************************/

void SendMessageToPagerTapWidget::on_btnPagingSettings_clicked()
{
    OptionsForm dlg;
    dlg.setCurrentPage(15); // Pagers
    dlg.exec();
}

/******************************************************************/

void SendMessageToPagerTapWidget::on_btnMsgTemplate_clicked()
{
    IOMailProfileLoader loader;
    MailProfilesDlg dlg;
    dlg.init(ui->cmbMsgTemplate->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset();
        ui->cmbMsgTemplate->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

} // namespace SDPO



