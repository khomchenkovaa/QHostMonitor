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
    ui->chkGenerateReports->setChecked(s->value(SKEY_REPORTS_AutoCreate, SVAL_REPORTS_AutoCreate).toInt());
    ui->spinGenerateReports->setValue (s->value(SKEY_REPORTS_Interval, SVAL_REPORTS_Interval).toInt());

    ui->chkCreateReport_1->setChecked    (s->value(SKEY_REPORTS_CreateReport1, SVAL_REPORTS_CreateReport1).toInt());
    ui->cmbCreateReport_1->setCurrentText(s->value(SKEY_REPORTS_ReportType1, SVAL_REPORTS_ReportType1).toString());
    ui->editReportFile_1->setText        (s->value(SKEY_REPORTS_ReportFile1,curFolder + SVAL_REPORTS_ReportFile1).toString());

    ui->chkCreateReport_2->setChecked    (s->value(SKEY_REPORTS_CreateReport2, SVAL_REPORTS_CreateReport2).toInt());
    ui->cmbCreateReport_2->setCurrentText(s->value(SKEY_REPORTS_ReportType2, SVAL_REPORTS_ReportType2).toString());
    ui->editReportFile_2->setText        (s->value(SKEY_REPORTS_ReportFile2,curFolder + SVAL_REPORTS_ReportFile2).toString());

    ui->chkCreateReport_3->setChecked    (s->value(SKEY_REPORTS_CreateReport3, SVAL_REPORTS_CreateReport3).toInt());
    ui->cmbCreateReport_3->setCurrentText(s->value(SKEY_REPORTS_ReportType3, SVAL_REPORTS_ReportType3).toString());
    ui->editReportFile_3->setText        (s->value(SKEY_REPORTS_ReportFile3,curFolder + SVAL_REPORTS_ReportFile3).toString());

    ui->chkCreateReport_4->setChecked    (s->value(SKEY_REPORTS_CreateReport4, SVAL_REPORTS_CreateReport4).toInt());
    ui->cmbCreateReport_4->setCurrentText(s->value(SKEY_REPORTS_ReportType4, SVAL_REPORTS_ReportType4).toString());
    ui->editReportFile_4->setText        (s->value(SKEY_REPORTS_ReportFile4,curFolder + SVAL_REPORTS_ReportFile4).toString());

    ui->chkCreateReport_5->setChecked    (s->value(SKEY_REPORTS_CreateReport5, SVAL_REPORTS_CreateReport5).toInt());
    ui->cmbCreateReport_5->setCurrentText(s->value(SKEY_REPORTS_ReportType5, SVAL_REPORTS_ReportType5).toString());
    ui->editReportFile_5->setText        (s->value(SKEY_REPORTS_ReportFile5,curFolder + SVAL_REPORTS_ReportFile5).toString());

    ui->chkCreateReport_6->setChecked    (s->value(SKEY_REPORTS_CreateReport6, SVAL_REPORTS_CreateReport6).toInt());
    ui->cmbCreateReport_6->setCurrentText(s->value(SKEY_REPORTS_ReportType6, SVAL_REPORTS_ReportType6).toString());
    ui->editReportFile_6->setText        (s->value(SKEY_REPORTS_ReportFile6,curFolder + SVAL_REPORTS_ReportFile6).toString());

    ui->chkExecuteActionProfile->setChecked    (s->value(SKEY_REPORTS_ExecuteActions, SVAL_REPORTS_ExecuteActions).toInt());
    ui->cmbSelectActionProfile->setCurrentIndex(s->value(SKEY_REPORTS_ActionsProfile, SVAL_REPORTS_ActionsProfile).toInt());
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





