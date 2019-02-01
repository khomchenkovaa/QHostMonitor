#include "qLogEventWidget.h"
#include "ui_qLogEventWidget.h"
#include "qMacroEditorDlg.h"
#include "action/tLogEventAction.h"

namespace SDPO {

/******************************************************************/

LogEventWidget::LogEventWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::LogEventWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

LogEventWidget::~LogEventWidget()
{
    delete ui;
}

/******************************************************************/

void LogEventWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::LogEvent) {
        return;
    }
    LogEventAction *action = qobject_cast<LogEventAction *>(item);
    ui->cmbComputer->setCurrentText(action->getComputer());
    ui->cmbLog->setCurrentText(action->getLog());
    ui->cmbEventType->setCurrentText(action->getEventType());
    ui->cmbEventSource->setCurrentText(action->getEventSource());
    ui->spinEventId->setValue(action->getEventId());
    ui->lineDescription->setText(action->getDescription());
    ui->chkConnectAs->setChecked(action->isConnectAs());
    ui->cmbConnectAsLogin->setCurrentText(action->getLogin());
    ui->lineConnectAsPassword->setText(action->getPassword());
}

/******************************************************************/

TestAction *LogEventWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::LogEvent) {
        item = new LogEventAction();
    }
    LogEventAction *action = qobject_cast<LogEventAction *>(item);
    action->setComputer(ui->cmbComputer->currentText());
    action->setLog(ui->cmbLog->currentText());
    action->setEventType(ui->cmbEventType->currentText());
    action->setEventSource(ui->cmbEventSource->currentText());
    action->setEventId(ui->spinEventId->value());
    action->setDescription(ui->lineDescription->text());
    action->setConnectAs(ui->chkConnectAs->isChecked());
    action->setLogin(ui->cmbConnectAsLogin->currentText());
    action->setPassword(ui->lineConnectAsPassword->text());
    return action;
}

/******************************************************************/

void LogEventWidget::on_btnDescription_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Condition to perform dependant test"));
    dlg.setScript(ui->lineDescription->text());
    if (dlg.exec() == QDialog::Accepted) {
        ui->lineDescription->setText(dlg.getScript());
    }
}

/******************************************************************/

} // namespace SDPO


