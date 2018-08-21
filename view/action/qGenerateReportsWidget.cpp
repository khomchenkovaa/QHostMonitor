#include "qGenerateReportsWidget.h"
#include "ui_qGenerateReportsWidget.h"
#include "action/tGenerateReportsAction.h"

namespace SDPO {

/******************************************************************/

GenerateReportsWidget::GenerateReportsWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::GenerateReportsWidget)
{
    ui->setupUi(this);
    on_selectGenerateReports();
    connect(ui->rdGenerateReportsForContaining, SIGNAL(clicked()),this,SLOT(on_selectGenerateReports()));
    connect(ui->rdGenerateReportsForSpecific, SIGNAL(clicked()),this,SLOT(on_selectGenerateReports()));
}

/******************************************************************/

GenerateReportsWidget::~GenerateReportsWidget()
{
    delete ui;
}

/******************************************************************/

void GenerateReportsWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::Report) {
        return;
    }
    GenerateReportsAction *action = qobject_cast<GenerateReportsAction *>(item);
    ui->rdGenerateReportsForContaining->setChecked(action->isGenerateReportFolder());
    ui->rdGenerateReportsForSpecific->setChecked(action->isGenerateReportSpecificFolder());
    on_selectGenerateReports();
    ui->lineEditReportsForSpecific->setText(action->getReportSelect());
    ui->cmbRecursiveMode->setCurrentText(action->getRecursiveMode());
    ui->chkUseReportPool->setChecked(action->isUseReportPool());
}

/******************************************************************/

TestAction *GenerateReportsWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::Report) {
            item = new GenerateReportsAction();
        }
   GenerateReportsAction *action = qobject_cast<GenerateReportsAction *>(item);
   action->setGenerateReportFolder(ui->rdGenerateReportsForContaining->isChecked());
   action->setGenerateReportSpecificFolder(ui->rdGenerateReportsForSpecific->isChecked());
   action->setReportSelect(ui->lineEditReportsForSpecific->text());
   action->setRecursiveMode(ui->cmbRecursiveMode->currentText());
   action->setUseReportPool(ui->chkUseReportPool->isChecked());
   return action;
}

/******************************************************************/

void GenerateReportsWidget::on_selectGenerateReports()
{
    if(ui->rdGenerateReportsForContaining->isChecked()) {
            ui->lineEditReportsForSpecific->setDisabled(true);
            ui->btnSelectFolder->setDisabled(true);
            ui->btnOpenFolderProperties->setDisabled(true);
    }else{
            ui->lineEditReportsForSpecific->setEnabled(true);
            ui->btnSelectFolder->setEnabled(true);
            ui->btnOpenFolderProperties->setEnabled(true);
          }
}

/******************************************************************/

} // namespace SDPO
