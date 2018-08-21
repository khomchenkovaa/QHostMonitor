#include "qSendSmsGsmModemWidget.h"
#include "ui_qSendSmsGsmModemWidget.h"
#include "action/tSendSmsGsmModemAction.h"
#include "qOptionsForm.h"
#include "gData.h"
#include "global/ioMailProfileLoader.h"
#include "qMailProfilesDlg.h"

namespace SDPO {

/******************************************************************/

SendSmsGsmModemWidget::SendSmsGsmModemWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SendSmsGsmModemWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SendSmsGsmModemWidget::~SendSmsGsmModemWidget()
{
    delete ui;
}

/******************************************************************/

void SendSmsGsmModemWidget::init(TestAction *item)
{   reset();
    if (!item || item->getAction() != TActionID::MsgSmsGsm) {
        return;
    }
    SendSmsGsmModemAction *action = qobject_cast<SendSmsGsmModemAction *>(item);
    ui->cmbDestPhone->setCurrentText(action->getDestPhone());
    ui->cmbMsgClass->setCurrentText(action->getMsgClass());
    ui->cmbMsgTemplate->setCurrentText(action->getMsgTemplate());
}

/******************************************************************/

void SendSmsGsmModemWidget::reset()
{
    ui->cmbMsgTemplate->clear();
    foreach (const GMailProfile &profile, GData::mailProfiles) {
        ui->cmbMsgTemplate->addItem(profile.name);
    }
}

/******************************************************************/

TestAction *SendSmsGsmModemWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::MsgSmsGsm) {
        item = new SendSmsGsmModemAction();
    }
    SendSmsGsmModemAction *action = qobject_cast<SendSmsGsmModemAction *>(item);
    action->setDestPhone(ui->cmbDestPhone->currentText());
    action->setMsgClass(ui->cmbMsgClass->currentText());
    action->setMsgTemplate(ui->cmbMsgTemplate->currentText());
    return action;
}

/******************************************************************/

void SendSmsGsmModemWidget::on_btnMsgTemplate_clicked()
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

void SendSmsGsmModemWidget::on_btnGsmSettings_clicked()
{
    OptionsForm dlg;
    dlg.setCurrentPage(18); // SMS GSM
    dlg.exec();
}

/******************************************************************/

} // namespace SDPO



