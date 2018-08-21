#include "qSendSmsSmppWidget.h"
#include "ui_qSendSmsSmppWidget.h"
#include "action/tSendSmsSmppAction.h"
#include "qOptionsForm.h"
#include "gData.h"
#include "global/ioMailProfileLoader.h"
#include "qMailProfilesDlg.h"


namespace SDPO {

/******************************************************************/

SendSmsSmppWidget::SendSmsSmppWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SendSmsSmppWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SendSmsSmppWidget::~SendSmsSmppWidget()
{
    delete ui;
}

/******************************************************************/

void SendSmsSmppWidget::reset()
{
    ui->cmbMessageTemplate->clear();
    foreach (const GMailProfile &profile, GData::mailProfiles) {
        ui->cmbMessageTemplate->addItem(profile.name);
    }
}

/******************************************************************/

void SendSmsSmppWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::MsgSmsSmpp) {
        return;
    }
    SendSmsSmppAction *action = qobject_cast<SendSmsSmppAction *>(item);
    ui->cmbDestinationPhone->setCurrentText(action->getDestPhone());
    ui->cmbDestinationTon->setCurrentText(action->getDestTon());
    ui->cmbDestinationNpi->setCurrentText(action->getDestNpi());
    ui->cmbMessageTemplate->setCurrentText(action->getMsgTemplate());
}

/******************************************************************/

TestAction *SendSmsSmppWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::MsgSmsSmpp) {
        item = new SendSmsSmppAction();
    }
    SendSmsSmppAction *action = qobject_cast<SendSmsSmppAction *>(item);
    action->setDestPhone(ui->cmbDestinationPhone->currentText());
    action->setDestTon(ui->cmbDestinationTon->currentText());
    action->setDestNpi(ui->cmbDestinationNpi->currentText());
    action->setMsgTemplate(ui->cmbMessageTemplate->currentText());
    return action;
}

/******************************************************************/

void SendSmsSmppWidget::on_btnMessageTemplateSelect_clicked()
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

void SendSmsSmppWidget::on_btnSetupSmpp_clicked()
{
    OptionsForm dlg;
    dlg.setCurrentPage(19); // SMS SMPP
    dlg.exec();
}

/******************************************************************/

} // namespace SDPO





