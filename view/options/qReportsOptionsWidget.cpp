#include "qReportsOptionsWidget.h"
#include "ui_qReportsOptionsWidget.h"
#include <QFileDialog>
#include "qActionProfiles.h"
#include "global/ioActionProfileLoader.h"
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

    QVariant value = Settings::get(Settings::Reports, Settings::AutoCreate, QVariant(0));
    if (value.toInt() == 1) {
        ui->chkGenerateReports->setChecked(true);
    } else {
        ui->chkGenerateReports->setChecked(false);
    }

    value = Settings::get(Settings::Reports, Settings::Interval, QVariant(5));
    ui->spinGenerateReports->setValue(value.toInt());

    value = Settings::get(Settings::Reports, Settings::CreateReport1, QVariant(1));
    if (value.toInt() == 1) {
        ui->chkCreateReport_1->setChecked(true);
    } else {
        ui->chkCreateReport_1->setChecked(false);
    }

    value = Settings::get(Settings::Reports, Settings::ReportType1, QVariant());
    ui->cmbCreateReport_1->setCurrentText(value.toString());

    value = Settings::get(Settings::Reports, Settings::ReportFile1, QVariant(curFolder + "dbf-full.dbf"));
    ui->editReportFile_1->setText(value.toString());

    value = Settings::get(Settings::Reports, Settings::CreateReport2, QVariant(1));
    if (value.toInt() == 1) {
        ui->chkCreateReport_2->setChecked(true);
    } else {
        ui->chkCreateReport_2->setChecked(false);
    }

    value = Settings::get(Settings::Reports, Settings::ReportType2, QVariant());
    ui->cmbCreateReport_2->setCurrentText(value.toString());

    value = Settings::get(Settings::Reports, Settings::ReportFile2, QVariant(curFolder +"dbf-full.dbf"));
    ui->editReportFile_2->setText(value.toString());

    value = Settings::get(Settings::Reports, Settings::CreateReport3, QVariant(1));
    if (value.toInt() == 1) {
        ui->chkCreateReport_3->setChecked(true);
    } else {
        ui->chkCreateReport_3->setChecked(false);
    }

    value = Settings::get(Settings::Reports, Settings::ReportType3, QVariant());
    ui->cmbCreateReport_3->setCurrentText(value.toString());

    value = Settings::get(Settings::Reports, Settings::ReportFile3, QVariant(curFolder + "rep-admin.htm"));
    ui->editReportFile_3->setText(value.toString());

    value = Settings::get(Settings::Reports, Settings::CreateReport4, QVariant(1));
    if (value.toInt() == 1) {
        ui->chkCreateReport_4->setChecked(true);
    } else {
        ui->chkCreateReport_4->setChecked(false);
    }

    value = Settings::get(Settings::Reports, Settings::ReportType4, QVariant());
    ui->cmbCreateReport_4->setCurrentText(value.toString());

    value = Settings::get(Settings::Reports, Settings::ReportFile4, QVariant(curFolder + "rep-man.htm"));
    ui->editReportFile_4->setText(value.toString());

    value = Settings::get(Settings::Reports, Settings::CreateReport5, QVariant(1));
    if (value.toInt() == 1) {
        ui->chkCreateReport_5->setChecked(true);
    } else {
        ui->chkCreateReport_5->setChecked(false);
    }

    value = Settings::get(Settings::Reports, Settings::ReportType5, QVariant());
    ui->cmbCreateReport_5->setCurrentText(value.toString());

    value = Settings::get(Settings::Reports, Settings::ReportFile5, QVariant(curFolder + "dbf-full.dbf"));
    ui->editReportFile_5->setText(value.toString());

    value = Settings::get(Settings::Reports, Settings::CreateReport6, QVariant(1));
    if (value.toInt() == 1) {
        ui->chkCreateReport_6->setChecked(true);
    } else {
        ui->chkCreateReport_6->setChecked(false);
    }

    value = Settings::get(Settings::Reports, Settings::ReportType6, QVariant());
    ui->cmbCreateReport_6->setCurrentText(value.toString());

    value = Settings::get(Settings::Reports, Settings::ReportFile6, QVariant(curFolder + "dbf-full.dbf"));
    ui->editReportFile_6->setText(value.toString());

    value = Settings::get(Settings::Reports, Settings::ExecuteActions, QVariant(0));
    if (value.toInt() == 1) {
        ui->chkExecuteActionProfile->setChecked(true);
    } else {
        ui->chkExecuteActionProfile->setChecked(false);
    }

    value = Settings::get(Settings::Reports, Settings::ActionsProfile, QVariant());
    ui->cmbSelectActionProfile->setCurrentIndex(value.toInt());

}

/******************************************************************/

void ReportsOptionsWidget::prepareToSave(QSettings *s)
{
    Settings::set(Settings::Reports, Settings::AutoCreate) = QVariant(ui->chkGenerateReports->isChecked()?1:0);
    Settings::set(Settings::Reports, Settings::Interval) = QVariant(ui->spinGenerateReports->value());
    Settings::set(Settings::Reports, Settings::CreateReport1) = QVariant(ui->chkCreateReport_1->isChecked()?1:0);
    Settings::set(Settings::Reports, Settings::ReportType1) = QVariant(ui->cmbCreateReport_1->currentText());
    Settings::set(Settings::Reports, Settings::ReportFile1) = QVariant(ui->editReportFile_1->text());
    Settings::set(Settings::Reports, Settings::CreateReport2) = QVariant(ui->chkCreateReport_2->isChecked()?1:0);
    Settings::set(Settings::Reports, Settings::ReportType2) = QVariant(ui->cmbCreateReport_2->currentText());
    Settings::set(Settings::Reports, Settings::ReportFile2) = QVariant(ui->editReportFile_2->text());
    Settings::set(Settings::Reports, Settings::CreateReport3) = QVariant(ui->chkCreateReport_3->isChecked()?1:0);
    Settings::set(Settings::Reports, Settings::ReportType3) = QVariant(ui->cmbCreateReport_3->currentText());
    Settings::set(Settings::Reports, Settings::ReportFile3) = QVariant(ui->editReportFile_3->text());
    Settings::set(Settings::Reports, Settings::CreateReport4) = QVariant(ui->chkCreateReport_4->isChecked()?1:0);
    Settings::set(Settings::Reports, Settings::ReportType4) = QVariant(ui->cmbCreateReport_4->currentText());
    Settings::set(Settings::Reports, Settings::ReportFile4) = QVariant(ui->editReportFile_4->text());
    Settings::set(Settings::Reports, Settings::CreateReport5) = QVariant(ui->chkCreateReport_5->isChecked()?1:0);
    Settings::set(Settings::Reports, Settings::ReportType5) = QVariant(ui->cmbCreateReport_5->currentText());
    Settings::set(Settings::Reports, Settings::ReportFile5) = QVariant(ui->editReportFile_5->text());
    Settings::set(Settings::Reports, Settings::CreateReport6) = QVariant(ui->chkCreateReport_6->isChecked()?1:0);
    Settings::set(Settings::Reports, Settings::ReportType6) = QVariant(ui->cmbCreateReport_6->currentText());
    Settings::set(Settings::Reports, Settings::ReportFile6) = QVariant(ui->editReportFile_6->text());
    Settings::set(Settings::Reports, Settings::ExecuteActions) = QVariant(ui->chkExecuteActionProfile->isChecked()?1:0);
    Settings::set(Settings::Reports, Settings::ActionsProfile) = QVariant(ui->cmbSelectActionProfile->currentIndex());

}

/******************************************************************/

} // namespace SDPO





