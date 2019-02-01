#include "qExecuteExternalProgramWidget.h"
#include "ui_qExecuteExternalProgramWidget.h"
#include "action/tExecuteExternalProgramAction.h"

namespace SDPO {

ExecuteExternalProgramWidget::ExecuteExternalProgramWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::ExecuteExternalProgramWidget)
{
    ui->setupUi(this);
}

ExecuteExternalProgramWidget::~ExecuteExternalProgramWidget()
{
    delete ui;
}

void ExecuteExternalProgramWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::ProgramExec) {
        return;
    }
    ExecuteExternalProgramAction *action = qobject_cast<ExecuteExternalProgramAction *>(item);
        ui->cmbCommandLine->setCurrentText(action->getCommandLine());
        ui->cmbWindowMode->setCurrentText(action->getWindowMode());
}

TestAction *ExecuteExternalProgramWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::ProgramExec) {
               item = new ExecuteExternalProgramAction();
           }
       ExecuteExternalProgramAction *action = qobject_cast<ExecuteExternalProgramAction *>(item);
       action->setCommandLine(ui->cmbCommandLine->currentText());
       action->setWindowMode(ui->cmbWindowMode->currentText());
       return action;
}

} // namespace SDPO
