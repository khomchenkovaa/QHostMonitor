#include "qExpressionTestsEditWidget.h"
#include "ui_qExpressionTestsEditWidget.h"
#include "qMacroEditorDlg.h"
#include "tTest.h"

namespace SDPO {

/******************************************************************/

ExpressionTestsEditWidget::ExpressionTestsEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpressionTestsEditWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

ExpressionTestsEditWidget::~ExpressionTestsEditWidget()
{
    delete ui;
}

/******************************************************************/

void ExpressionTestsEditWidget::init(TTest *item)
{
    ui->cmbCondition->setCurrentText(item->getDependencyCondition());
    ui->cmbOtherwiseStatus->setCurrentText(item->getDependencyOtherwiseStatus());
}

/******************************************************************/

void ExpressionTestsEditWidget::save(TTest *item)
{
    item->setDependencyCondition(ui->cmbCondition->currentText());
    item->setDependencyOtherwiseStatus(ui->cmbOtherwiseStatus->currentText());
}

/******************************************************************/

void ExpressionTestsEditWidget::reset()
{
    ui->cmbCondition->clear();
    ui->cmbOtherwiseStatus->clear();
}

/******************************************************************/

void ExpressionTestsEditWidget::on_btnCondition_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Condition to perform dependant test"));
    dlg.setScript(ui->cmbCondition->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbCondition->setCurrentText(dlg.getScript());
    }

}

/******************************************************************/

} // namespace SDPO


