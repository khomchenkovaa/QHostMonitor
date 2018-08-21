#include "qSendEmailSmtpWidget.h"
#include "ui_qSendEmailSmtpWidget.h"
#include "qMacroEditorDlg.h"
#include "qOptionsForm.h"
#include "action/tSendEmailSmtpAction.h"
#include "gData.h"
#include "global/ioMailProfileLoader.h"
#include "qMailProfilesDlg.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

SendEmailSmtpWidget::SendEmailSmtpWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SendEmailSmtpWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SendEmailSmtpWidget::~SendEmailSmtpWidget()
{
    delete ui;
}

/******************************************************************/

void SendEmailSmtpWidget::reset()
{
    ui->cmbBodyTemplate->clear();
    foreach (const GMailProfile &profile, GData::mailProfiles) {
        ui->cmbBodyTemplate->addItem(profile.name);
    }
}

/******************************************************************/

void SendEmailSmtpWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::MsgEmail) {
        return;
    }
    SendEmailSmtpAction *action = qobject_cast<SendEmailSmtpAction *>(item);
    ui->cmbFromSender->setCurrentText(action->getFromSender());
    ui->cmbToRecipients->setCurrentText(action->getToRecipients());
    ui->cmbPriority->setCurrentText(action->getPriority());
    ui->cmbSubject->setCurrentText(action->getSubject());
    ui->cmbBodyTemplate->setCurrentText(action->getBodyTemplate());
    ui->chkAttachFile->setChecked(action->isAttachFile());
    ui->lineAttachFile->setText(action->getAttachFileSelect());
}

/******************************************************************/

TestAction *SendEmailSmtpWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::MsgEmail) {
        item = new SendEmailSmtpAction();
    }
    SendEmailSmtpAction *action = qobject_cast<SendEmailSmtpAction *>(item);
    action->setFromSender(ui->cmbFromSender->currentText());
    action->setToRecipients(ui->cmbToRecipients->currentText());
    action->setPriority(ui->cmbPriority->currentText());
    action->setSubject(ui->cmbSubject->currentText());
    action->setBodyTemplate(ui->cmbBodyTemplate->currentText());
    action->setAttachFile(ui->chkAttachFile->isChecked());
    action->setAttachFileSelect(ui->lineAttachFile->text());
    return action;
}

/******************************************************************/

void SendEmailSmtpWidget::on_btnToRecipients_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Condition to perform dependant test"));
    dlg.setScript(ui->cmbToRecipients->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbToRecipients->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

void SendEmailSmtpWidget::on_btnSubject_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Condition to perform dependant test"));
    dlg.setScript(ui->cmbSubject->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbSubject->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

void SendEmailSmtpWidget::on_btnBodyTemplate_clicked()
{
    IOMailProfileLoader loader;
    MailProfilesDlg dlg;
    dlg.init(ui->cmbBodyTemplate->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset();
        ui->cmbBodyTemplate->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }

}

/******************************************************************/

void SendEmailSmtpWidget::on_btnAttachFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->lineAttachFile->text());
    if (!fileName.isEmpty()) {
        ui->lineAttachFile->setText(fileName);
    }
}

/******************************************************************/

} // namespace SDPO





