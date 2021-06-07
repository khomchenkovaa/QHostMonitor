#include "qViewCriteriaPropertiesWidget.h"
#include "ui_qViewCriteriaPropertiesWidget.h"
#include "tView.h"
#include "qMacroEditorDlg.h"

namespace SDPO {

/******************************************************************/

ViewCriteriaPropertiesWidget::ViewCriteriaPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewCriteriaPropertiesWidget)
{
    ui->setupUi(this);
    ui->listSelectByMethod->clear();
    foreach(const TestMethodMetaInfo &method, TestMethod::metaInfo) {
        if (method.id == TMethodID::Empty) continue;
        QListWidgetItem *item = new QListWidgetItem(method.text);
        item->setCheckState( Qt::Unchecked );
        ui->listSelectByMethod->addItem(item);
    }
}

/******************************************************************/

ViewCriteriaPropertiesWidget::~ViewCriteriaPropertiesWidget()
{
    delete ui;
}

/******************************************************************/

void ViewCriteriaPropertiesWidget::init(TNode *node)
{
    if (!node) {
        reset();
        return;
    }
    if (node->getType() != TNode::VIEW) {
        reset();
        return;
    }
    TView *view = qobject_cast<TView*>(node);
    // Select items by status
    ui->boxSelectByStatus->setChecked(view->isSelectByStatus());
    foreach(TView::VStatus status, view->getStatusCriteria()) {
        ui->listSelectByStatus->item((int)status)->setCheckState(Qt::Checked);
    }
    // Select items by test method
    ui->boxSelectByMethod->setChecked(view->isSelectByTestMethod());
    foreach(TMethodID methodID, view->getMethodCriteria()) {
        ui->listSelectByMethod->item((int)methodID)->setCheckState(Qt::Checked);
    }
    // Select items by stats
    ui->boxSelectByStats->setChecked(view->isSelectByStats());
    switch(view->getStatsCriteria()) {
    case TView::VC_AliveRatio:
        ui->rbAliveRatio->setChecked(true);
        break;
    case TView::VC_DeadRatio:
        ui->rbDeadRatio->setChecked(true);
        break;
    case TView::VC_UnknownRatio:
        ui->rbUnknownRatio->setChecked(true);
        break;
    case TView::VC_ReplyGT:
        ui->rbReplyGreater->setChecked(true);
        break;
    case TView::VC_ReplyLT:
        ui->rbReplyLess->setChecked(true);
        break;
    case TView::VC_Duration:
        ui->rbStatusDuration->setChecked(true);
        break;
    }
    ui->spinAlive->setValue(view->getAliveRatioValue());
    ui->spinDead->setValue(view->getDeadRatioValue());
    ui->spinUnknown->setValue(view->getUnknownRatioValue());
    ui->spinReplyGreater->setValue(view->getReplyGTValue());
    ui->spinReplyLess->setValue(view->getReplyLTValue());
    ui->cmbDurationCriteria->setCurrentIndex(view->isDurationGreater()?0:1);
    ui->spinDurationValue->setValue(view->getDurationValue());
    // Select items by test properties
    ui->chkTestName->setChecked(view->isSelectByTestName());
    ui->chkComment->setChecked(view->isSelectByComment());
    ui->chkTarget->setChecked(view->isSelectByTarget());
    ui->chkTestBy->setChecked(view->isSelectByAgent());
    ui->cmbTestName->setCurrentText(view->getTestNameValue());
    ui->cmbComment->setCurrentText(view->getCommentValue());
    ui->cmbTarget->setCurrentText(view->getTargetValue());
    ui->cmbTestBy->setCurrentText(view->getAgentValue());
    // Select items using expressions
    ui->boxSelectUsingExpression->setChecked(view->isSelectUsingExpression());
    ui->cmbSelectUsingExpression->setCurrentText(view->getExpressionValue());
}

/******************************************************************/

void ViewCriteriaPropertiesWidget::save(TNode *node)
{
    if (!node) {
        return;
    }
    if (node->getType() != TNode::VIEW) {
        return;
    }
    TView *view = qobject_cast<TView*>(node);
    // Select items by status
    view->setSelectByStatus(ui->boxSelectByStatus->isChecked());
    view->clearStatusCriteria();
    for (int i=0; i < ui->listSelectByStatus->count(); i++) {
        if (ui->listSelectByStatus->item(i)->checkState() == Qt::Checked) {
            view->addStatusCriteria((TView::VStatus)i);
        }
    }
    // Select items by test method
    view->setSelectByTestMethod(ui->boxSelectByMethod->isChecked());
    view->clearMethodCriteria();
    for (int i=0; i < ui->listSelectByMethod->count(); i++) {
        if (ui->listSelectByMethod->item(i)->checkState() == Qt::Checked) {
            view->addMethodCriteria((TMethodID)i);
        }
    }
    // Select items by stats
    view->setSelectByStats(ui->boxSelectByStats->isChecked());
    if (ui->rbAliveRatio->isChecked()) {
        view->setStatsCriteria(TView::VC_AliveRatio);
    } else if (ui->rbDeadRatio->isChecked()) {
        view->setStatsCriteria(TView::VC_DeadRatio);
    } else if (ui->rbUnknownRatio->isChecked()) {
        view->setStatsCriteria(TView::VC_UnknownRatio);
    } else if (ui->rbReplyGreater->isChecked()) {
        view->setStatsCriteria(TView::VC_ReplyGT);
    } else if (ui->rbReplyLess->isChecked()) {
        view->setStatsCriteria(TView::VC_ReplyLT);
    } else if (ui->rbStatusDuration->isChecked()) {
        view->setStatsCriteria(TView::VC_Duration);
    }
    view->setAliveRatioValue(ui->spinAlive->value());
    view->setDeadRatioValue(ui->spinDead->value());
    view->setUnknownRatioValue(ui->spinUnknown->value());
    view->setReplyGTValue(ui->spinReplyGreater->value());
    view->setReplyLTValue(ui->spinReplyLess->value());
    view->setDurationGreater(ui->cmbDurationCriteria->currentIndex() == 0);
    view->setDurationValue(ui->spinDurationValue->value());
    // Select items by test properties
    view->setSelectByTestName(ui->chkTestName->isChecked());
    view->setSelectByComment(ui->chkComment->isChecked());
    view->setSelectByTarget(ui->chkTarget->isChecked());
    view->setSelectByAgent(ui->chkTestBy->isChecked());
    view->setTestNameValue(ui->cmbTestName->currentText());
    view->setCommentValue(ui->cmbComment->currentText());
    view->setTargetValue(ui->cmbTarget->currentText());
    view->setAgentValue(ui->cmbTestBy->currentText());
    // Select items using expressions
    view->setSelectUsingExpression(ui->boxSelectUsingExpression->isChecked());
    view->setExpressionValue(ui->cmbSelectUsingExpression->currentText());
}

/******************************************************************/

void ViewCriteriaPropertiesWidget::reset()
{
    ui->boxSelectByStatus->setChecked(false);
    ui->boxSelectByMethod->setChecked(false);
    ui->boxSelectByStats->setChecked(false);
    ui->rbAliveRatio->setChecked(true);
    ui->spinAlive->setValue(0.0);
    ui->spinDead->setValue(0.0);
    ui->spinUnknown->setValue(0.0);
    ui->spinReplyGreater->setValue(0.0);
    ui->spinReplyLess->setValue(0.0);
    ui->cmbDurationCriteria->setCurrentIndex(0);
    ui->spinDurationValue->setValue(1);
    ui->chkTestName->setChecked(false);
    ui->chkComment->setChecked(false);
    ui->chkTarget->setChecked(false);
    ui->chkTestBy->setChecked(false);
    ui->boxSelectUsingExpression->setChecked(false);
}

/******************************************************************/

void ViewCriteriaPropertiesWidget::on_btnSelectExpression_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Add test to view if"));
    dlg.setScript(ui->cmbSelectUsingExpression->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbSelectUsingExpression->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

void ViewCriteriaPropertiesWidget::on_rbStatusDuration_toggled(bool checked)
{
    ui->cmbDurationCriteria->setEnabled(checked);
    ui->spinDurationValue->setEnabled(checked);
}

/******************************************************************/

} // namespace SDPO

