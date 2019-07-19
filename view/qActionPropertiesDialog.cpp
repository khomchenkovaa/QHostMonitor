#include "qActionPropertiesDialog.h"
#include "ui_qActionPropertiesDialog.h"
#include "qMacroEditorDlg.h"
#include "action/qActionWidget.h"

namespace SDPO {

/******************************************************************/

ActionPropertiesDialog::ActionPropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActionPropertiesDialog),
    m_item(nullptr)
{
    ui->setupUi(this);
    ui->cmbSelectMode->setCurrentIndex(0);
    ui->stcWidgetMode->setCurrentIndex(0);
}

/******************************************************************/

ActionPropertiesDialog::~ActionPropertiesDialog()
{
    delete ui;
}

/******************************************************************/

void ActionPropertiesDialog::setAddFlag(const bool isBad)
{
    ui->chkActionDependsOn->setHidden(isBad);
    ui->cmbActionDependsOn->setHidden(isBad);
    ui->lineActionDependsOn->setHidden(isBad);
}

/******************************************************************/

void ActionPropertiesDialog::setIndex(int index)
{
    ui->cmbActionType->setCurrentIndex(index);
    actionTypeChanged(index);
    connect(ui->cmbActionType, SIGNAL(currentIndexChanged(int)), this, SLOT(actionTypeChanged(int)));
}

/******************************************************************/

void ActionPropertiesDialog::init(TestAction *item)
{
    m_item = item;
    setIndex(static_cast<int>(m_item->getAction()));
    ActionWidget *widget = qobject_cast<ActionWidget*>(ui->stcWidgetActionParametrs->currentWidget());
    widget->init(m_item);
    ui->cmbActionType->setEnabled(false);
    ui->lnActionName->setText(m_item->getName());
    ui->cmbExecuteBy->setCurrentText(m_item->getAgent());
    ui->chkStoreActionResult->setChecked(m_item->isStoreResult());
    ui->cmbSelectMode->setCurrentIndex(static_cast<int>(m_item->getMode()));
    ui->spinStartWhen->setValue(m_item->getStartAfter());
    if (m_item->getRetries() == -1) {
        ui->rbUntilStatusChanges->setChecked(true);
        ui->spinRepeat->setValue(1);
    } else {
        ui->rbRepeat->setChecked(true);
        ui->spinRepeat->setValue(m_item->getRetries());
    }
    ui->cmbAdvancedMode->setCurrentText(m_item->getCondition());
}

/******************************************************************/

TestAction *ActionPropertiesDialog::getResult()
{
    ActionWidget *widget = qobject_cast<ActionWidget*>(ui->stcWidgetActionParametrs->currentWidget());
    m_item = widget->save(m_item);
    if (m_item) {
        m_item->setName(ui->lnActionName->text());
        m_item->setAgent(ui->cmbExecuteBy->currentText());
        m_item->setStoreResult(ui->chkStoreActionResult->isChecked());
        m_item->setMode(static_cast<TActionMode>(ui->cmbSelectMode->currentIndex()));
        m_item->setStartAfter(ui->spinStartWhen->value());
        m_item->setRetries(ui->spinRepeat->value());
        if (ui->rbUntilStatusChanges->isChecked()) {
            m_item->setRetries(-1);
        }
        m_item->setCondition(ui->cmbAdvancedMode->currentText());
    }
    return m_item;
}

/******************************************************************/

void ActionPropertiesDialog::on_cmbSelectMode_currentIndexChanged(int index)
{
    switch (index) {
    case 0: // standard mode
        ui->stcWidgetMode->setCurrentIndex(0);
        ui->stcWidgetMode->setEnabled(true);
        ui->chkActionDependsOn->setEnabled(true);
        ui->cmbActionDependsOn->setEnabled(true);
        break;
    case 1: // advanced mode
        ui->stcWidgetMode->setCurrentIndex(1);
        ui->stcWidgetMode->setEnabled(true);
        ui->chkActionDependsOn->setDisabled(true);
        ui->cmbActionDependsOn->setDisabled(true);
        break;
    case 2: // on the schedule
        ui->stcWidgetMode->setCurrentIndex(0);
        ui->stcWidgetMode->setDisabled(true);
        ui->chkActionDependsOn->setDisabled(true);
        ui->cmbActionDependsOn->setDisabled(true);
        break;
    }
}

/******************************************************************/

void ActionPropertiesDialog::on_btnAdvancedMode_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Condition to start action"));
    dlg.setScript(ui->cmbAdvancedMode->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbAdvancedMode->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

void ActionPropertiesDialog::actionTypeChanged(int index)
{
    ui->stcWidgetActionParametrs->setCurrentIndex(index);
    ui->lnActionName->setText(ui->cmbActionType->currentText());
    if (m_item == nullptr) {
        ActionWidget *widget = qobject_cast<ActionWidget*>(ui->stcWidgetActionParametrs->currentWidget());
        widget->reset();
    }
}

/******************************************************************/

} // namespace SDPO
