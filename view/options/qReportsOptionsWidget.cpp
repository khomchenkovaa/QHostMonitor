#include "qReportsOptionsWidget.h"
#include "ui_qReportsOptionsWidget.h"
#include <QFileDialog>
#include "qActionProfiles.h"
#include "io/ioActionProfileLoader.h"
#include "gData.h"
#include "qReportProfilesDlg.h"


namespace SDPO {

/******************************************************************/

ReportsOptionsWidget::ReportsOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::ReportsOptionsWidget)
{
    ui->setupUi(this);
    curFolder = QCoreApplication::applicationDirPath() + "/logs/";
}

/******************************************************************/

ReportsOptionsWidget::~ReportsOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void ReportsOptionsWidget::on_btnelectReportFile_1_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editReportFile_1->text());
    if (!fileName.isEmpty()) {
        ui->editReportFile_1->setText(fileName);
    }
}

/******************************************************************/

void ReportsOptionsWidget::on_btnelectReportFile_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editReportFile_2->text());
    if (!fileName.isEmpty()) {
        ui->editReportFile_2->setText(fileName);
    }
}

/******************************************************************/

void ReportsOptionsWidget::on_btnelectReportFile_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editReportFile_3->text());
    if (!fileName.isEmpty()) {
        ui->editReportFile_3->setText(fileName);
    }
}

/******************************************************************/

void ReportsOptionsWidget::on_btnelectReportFile_4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editReportFile_4->text());
    if (!fileName.isEmpty()) {
        ui->editReportFile_4->setText(fileName);
    }
}

/******************************************************************/

void ReportsOptionsWidget::on_btnelectReportFile_5_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editReportFile_5->text());
    if (!fileName.isEmpty()) {
        ui->editReportFile_5->setText(fileName);
    }
}

/******************************************************************/

void ReportsOptionsWidget::on_btnelectReportFile_6_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editReportFile_6->text());
    if (!fileName.isEmpty()) {
        ui->editReportFile_6->setText(fileName);
    }
}

/******************************************************************/

void ReportsOptionsWidget::reset_ActionProfileSelect()
{
    ui->cmbSelectActionProfile->clear();
    foreach(const GActionProfile &profile, GData::actionProfiles) {
        ui->cmbSelectActionProfile->addItem(profile.name);
    }
}

/******************************************************************/

void ReportsOptionsWidget::on_btnSelectActionProfile_clicked()
{
    IOActionProfileLoader load;
    ActionProfiles dlg;
    dlg.init(ui->cmbSelectActionProfile->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        load.save();
        reset_ActionProfileSelect();
        ui->cmbSelectActionProfile->setCurrentIndex(dlg.getSelected());
    } else {
        load.load();
    }
}

/******************************************************************/

void ReportsOptionsWidget::on_btnCreateReport_1_clicked()
{
 // do nothing
}

/******************************************************************/

void ReportsOptionsWidget::init(QSettings *s)
{
    reset_ActionProfileSelect();
    ui->chkGenerateReports->setChecked(s->value(SKEY_REPORTS_AutoCreate,0).toInt());
    ui->spinGenerateReports->setValue(s->value(SKEY_REPORTS_Interval,5).toInt());

    ui->chkCreateReport_1->setChecked(s->value(SKEY_REPORTS_CreateReport1,1).toInt());
    ui->cmbCreateReport_1->setCurrentText(s->value(SKEY_REPORTS_ReportType1,8).toString());
    ui->editReportFile_1->setText(s->value(SKEY_REPORTS_ReportFile1,curFolder + "dbf-full.dbf").toString());

    ui->chkCreateReport_2->setChecked(s->value(SKEY_REPORTS_CreateReport2,1).toInt());
    ui->cmbCreateReport_2->setCurrentText(s->value(SKEY_REPORTS_ReportType2,6).toString());
    ui->editReportFile_2->setText(s->value(SKEY_REPORTS_ReportFile2,curFolder + "dbf-big.dbf").toString());

    ui->chkCreateReport_3->setChecked(s->value(SKEY_REPORTS_CreateReport3,1).toInt());
    ui->cmbCreateReport_3->setCurrentText(s->value(SKEY_REPORTS_ReportType3,1).toString());
    ui->editReportFile_3->setText(s->value(SKEY_REPORTS_ReportFile3,curFolder + "rep-admin.htm").toString());

    ui->chkCreateReport_4->setChecked(s->value(SKEY_REPORTS_CreateReport4,1).toInt());
    ui->cmbCreateReport_4->setCurrentText(s->value(SKEY_REPORTS_ReportType4,2).toString());
    ui->editReportFile_4->setText(s->value(SKEY_REPORTS_ReportFile4,curFolder + "rep-man.htm").toString());

    ui->chkCreateReport_5->setChecked(s->value(SKEY_REPORTS_CreateReport5,1).toInt());
    ui->cmbCreateReport_5->setCurrentText(s->value(SKEY_REPORTS_ReportType5,3).toString());
    ui->editReportFile_5->setText(s->value(SKEY_REPORTS_ReportFile5,curFolder + "rep-boss.htm").toString());

    ui->chkCreateReport_6->setChecked(s->value(SKEY_REPORTS_CreateReport6,1).toInt());
    ui->cmbCreateReport_6->setCurrentText(s->value(SKEY_REPORTS_ReportType6,4).toString());
    ui->editReportFile_6->setText(s->value(SKEY_REPORTS_ReportFile6,curFolder + "rep-full.htm").toString());

    ui->chkExecuteActionProfile->setChecked(s->value(SKEY_REPORTS_ExecuteActions,0).toInt());
    ui->cmbSelectActionProfile->setCurrentIndex(s->value(SKEY_REPORTS_ActionsProfile).toInt());
}

/******************************************************************/

void ReportsOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_REPORTS_AutoCreate, ui->chkGenerateReports->isChecked()?1:0);
    s->setValue(SKEY_REPORTS_Interval, ui->spinGenerateReports->value());

    s->setValue(SKEY_REPORTS_CreateReport1, ui->chkCreateReport_1->isChecked()?1:0);
    s->setValue(SKEY_REPORTS_ReportType1, ui->cmbCreateReport_1->currentText());
    s->setValue(SKEY_REPORTS_ReportFile1, ui->editReportFile_1->text());

    s->setValue(SKEY_REPORTS_CreateReport2, ui->chkCreateReport_2->isChecked()?1:0);
    s->setValue(SKEY_REPORTS_ReportType2, ui->cmbCreateReport_2->currentText());
    s->setValue(SKEY_REPORTS_ReportFile2, ui->editReportFile_2->text());

    s->setValue(SKEY_REPORTS_CreateReport3, ui->chkCreateReport_3->isChecked()?1:0);
    s->setValue(SKEY_REPORTS_ReportType3, ui->cmbCreateReport_3->currentText());
    s->setValue(SKEY_REPORTS_ReportFile3, ui->editReportFile_3->text());

    s->setValue(SKEY_REPORTS_CreateReport4, ui->chkCreateReport_4->isChecked()?1:0);
    s->setValue(SKEY_REPORTS_ReportType4, ui->cmbCreateReport_4->currentText());
    s->setValue(SKEY_REPORTS_ReportFile4, ui->editReportFile_4->text());

    s->setValue(SKEY_REPORTS_CreateReport5, ui->chkCreateReport_5->isChecked()?1:0);
    s->setValue(SKEY_REPORTS_ReportType5, ui->cmbCreateReport_5->currentText());
    s->setValue(SKEY_REPORTS_ReportFile5, ui->editReportFile_5->text());

    s->setValue(SKEY_REPORTS_CreateReport6, ui->chkCreateReport_6->isChecked()?1:0);
    s->setValue(SKEY_REPORTS_ReportType6, ui->cmbCreateReport_6->currentText());
    s->setValue(SKEY_REPORTS_ReportFile6, ui->editReportFile_6->text());

    s->setValue(SKEY_REPORTS_ExecuteActions, ui->chkExecuteActionProfile->isChecked()?1:0);
    s->setValue(SKEY_REPORTS_ActionsProfile, ui->cmbSelectActionProfile->currentIndex());
}

/******************************************************************/

} // namespace SDPO





