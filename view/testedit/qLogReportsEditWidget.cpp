#include "qLogReportsEditWidget.h"
#include "ui_qLogReportsEditWidget.h"
#include "tTest.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

LogReportsEditWidget::LogReportsEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogReportsEditWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

LogReportsEditWidget::~LogReportsEditWidget()
{
    delete ui;
}

/******************************************************************/

void LogReportsEditWidget::init(TTest *item)
{
    reset();
    ui->chkCommonLog->setChecked(item->isUseCommonLog());
    ui->cmbCommonLogMode->setCurrentIndex(item->getCommonLogMode());
    ui->chkPrivateLog->setChecked(item->isUsePrivateLog());
    ui->editPrivateLogFile->setText(item->getPrivateLog());
    ui->cmbPrivateLogMode->setCurrentIndex(item->getPrivateLogMode());
    ui->chkHtmlReport->setChecked(item->isExcludeFromHtmlReport());
    ui->chkWmlReport->setChecked(item->isExcludeFromWmlReport());
    ui->chkDbfReport->setChecked(item->isExcludeFromDbfReport());
}

/******************************************************************/

void LogReportsEditWidget::save(TTest *item)
{
    item->setUseCommonLog(ui->chkCommonLog->isChecked());
    item->setCommonLogMode(ui->cmbCommonLogMode->currentIndex());
    item->setUsePrivateLog(ui->chkPrivateLog->isChecked());
    item->setPrivateLog(ui->editPrivateLogFile->text());
    item->setPrivateLogMode(ui->cmbPrivateLogMode->currentIndex());
    item->setExcludeFromHtmlReport(ui->chkHtmlReport->isChecked());
    item->setExcludeFromWmlReport(ui->chkWmlReport->isChecked());
    item->setExcludeFromDbfReport(ui->chkDbfReport->isChecked());
}

/******************************************************************/

void LogReportsEditWidget::reset()
{
    ui->chkCommonLog->setChecked(true);
    ui->cmbCommonLogMode->setCurrentIndex(0);
    ui->chkPrivateLog->setChecked(false);
    ui->editPrivateLogFile->clear();
    ui->cmbPrivateLogMode->setCurrentIndex(0);
    ui->chkHtmlReport->setChecked(false);
    ui->chkWmlReport->setChecked(false);
    ui->chkDbfReport->setChecked(false);
}

/******************************************************************/

void LogReportsEditWidget::on_btnPrivateLogFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Browse"),
                                                    ui->editPrivateLogFile->text(),
                                                    "HTML log files(*.htm);;Test log files(*.txt);;DBF log files(*.dbf);;Plug-in log files(*.plg);;All log formats(*.htm *.txt *.dbf *.plg);;All files(*.*)");
    if (!fileName.isEmpty()) {
        ui->editPrivateLogFile->setText(fileName);
    }
}

/******************************************************************/

} // namespace SDPO

