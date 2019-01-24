#include "qSyslogWidget.h"
#include "ui_qSyslogWidget.h"
#include "action/tSyslogAction.h"
#include "qMacroEditorDlg.h"

namespace SDPO {

/******************************************************************/

SyslogWidget::SyslogWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SyslogWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SyslogWidget::~SyslogWidget()
{
    delete ui;
}

/******************************************************************/

void SyslogWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::Syslog) {
        return;
    }
    SyslogAction *action = qobject_cast<SyslogAction *>(item);
    ui->cmbServer->setCurrentText(action->getServer());
    ui->spinPort->setValue(action->getPort());
    ui->cmbMessage->setCurrentText(action->getMessage());
    ui->cmbSeverity->setCurrentText(action->getSeverity());
    ui->spinFacility->setValue(action->getFacility());
}

/******************************************************************/

TestAction *SyslogWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::Syslog) {
        item = new SyslogAction();
    }
    SyslogAction *action = qobject_cast<SyslogAction *>(item);
    action->setServer(ui->cmbServer->currentText());
    action->setPort(ui->spinPort->value());
    action->setMessage(ui->cmbMessage->currentText());
    action->setSeverity(ui->cmbSeverity->currentText());
    action->setFacility(ui->spinFacility->value());
    return action;
}

/******************************************************************/

void SyslogWidget::on_btnMessage_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Init packet to send"));
    dlg.setScript(ui->cmbMessage->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbMessage->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

} // namespace SDPO

