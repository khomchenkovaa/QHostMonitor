#include "qRunHmsScriptWidget.h"
#include "ui_qRunHmsScriptWidget.h"
#include "action/tRunHmsScriptAction.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

RunHmsScriptWidget::RunHmsScriptWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::RunHmsScriptWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

RunHmsScriptWidget::~RunHmsScriptWidget()
{
    delete ui;
}

/******************************************************************/

void RunHmsScriptWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::RunScript) {
        return;
    }
    RunHmsScriptAction *action = qobject_cast<RunHmsScriptAction *>(item);
    ui->cmbScriptFile->setCurrentText(action->getScriptFile());
}

/******************************************************************/

TestAction *RunHmsScriptWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::RunScript) {
        item = new RunHmsScriptAction();
    }
    RunHmsScriptAction *action = qobject_cast<RunHmsScriptAction *>(item);
    action->setScriptFile(ui->cmbScriptFile->currentText());
    return action;
}

/******************************************************************/

void RunHmsScriptWidget::on_toolButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->cmbScriptFile->currentText());
    if (!fileName.isEmpty()) {
        ui->cmbScriptFile->setCurrentText(fileName);
    }
}

/******************************************************************/

} // namespace SDPO

