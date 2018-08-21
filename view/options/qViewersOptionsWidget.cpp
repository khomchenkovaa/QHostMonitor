#include "qViewersOptionsWidget.h"
#include "ui_qViewersOptionsWidget.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

ViewersOptionsWidget::ViewersOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::ViewersOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

ViewersOptionsWidget::~ViewersOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void ViewersOptionsWidget::on_btnViewersTxtLogFiles_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editViewersTxtLogFiles->text());
    if (!fileName.isEmpty()) {
        ui->editViewersTxtLogFiles->setText(fileName);
    }
}

/******************************************************************/

void ViewersOptionsWidget::on_btnViewersHtmlLogFiles_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editViewersHtmlLogFiles->text());
    if (!fileName.isEmpty()) {
        ui->editViewersHtmlLogFiles->setText(fileName);
    }
}

/******************************************************************/

void ViewersOptionsWidget::on_btnViewersDbfLogFiles_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editViewersDbfLogFiles->text());
    if (!fileName.isEmpty()) {
        ui->editViewersDbfLogFiles->setText(fileName);
    }
}

/******************************************************************/

void ViewersOptionsWidget::init()
{
   QVariant value = Settings::get(Settings::LogViewer, Settings::TextViewerMode, QVariant(0));
         ui->cmbTxtLogFiles->setCurrentIndex(value.toInt());
         on_SelectLogViewer();
         connect(ui->cmbTxtLogFiles, SIGNAL(currentIndexChanged(int)), this, SLOT(on_SelectLogViewer()));

    value = Settings::get(Settings::LogViewer, Settings::HTMLViewerMode, QVariant(1));
         ui->cmbHtmlLogFiles->setCurrentIndex(value.toInt());
         on_SelectLogViewer();
         connect(ui->cmbHtmlLogFiles, SIGNAL(currentIndexChanged(int)), this, SLOT(on_SelectLogViewer()));

    value = Settings::get(Settings::LogViewer, Settings::DBFViewerMode, QVariant(0));
         ui->cmbDbfLogFile->setCurrentIndex(value.toInt());
         on_SelectLogViewer();
         connect(ui->cmbDbfLogFile, SIGNAL(currentIndexChanged(int)), this, SLOT(on_SelectLogViewer()));

    value = Settings::get(Settings::LogViewer, Settings::TextViewerCmd, QVariant("notepad.exe %log%"));
         ui->editViewersTxtLogFiles->setText(value.toString());

    value = Settings::get(Settings::LogViewer, Settings::HTMLViewerCmd, QVariant());
         ui->editViewersHtmlLogFiles->setText(value.toString());

    value = Settings::get(Settings::LogViewer, Settings::DBFViewerCmd, QVariant());
         ui->editViewersDbfLogFiles->setText(value.toString());
}

/******************************************************************/

void ViewersOptionsWidget::prepareToSave()
{
    Settings::set(Settings::LogViewer, Settings::TextViewerMode) = QVariant(ui->cmbTxtLogFiles->currentIndex());
    Settings::set(Settings::LogViewer, Settings::HTMLViewerMode) = QVariant(ui->cmbHtmlLogFiles->currentIndex());
    Settings::set(Settings::LogViewer, Settings::DBFViewerMode) = QVariant(ui->cmbDbfLogFile->currentIndex());
    Settings::set(Settings::LogViewer, Settings::TextViewerCmd) = QVariant(ui->editViewersTxtLogFiles->text());
    Settings::set(Settings::LogViewer, Settings::HTMLViewerCmd) = QVariant(ui->editViewersHtmlLogFiles->text());
    Settings::set(Settings::LogViewer, Settings::DBFViewerCmd) = QVariant(ui->editViewersDbfLogFiles->text());
}

/******************************************************************/

void ViewersOptionsWidget::on_SelectLogViewer()
{
    int indexTxtLog = ui->cmbTxtLogFiles->currentIndex();
        switch (indexTxtLog) {
        case 0:
            ui->lblViewersTxtLogFiles->setDisabled(true);
            ui->editViewersTxtLogFiles->setDisabled(true);
            ui->btnViewersTxtLogFiles->setDisabled(true);
            break;
        case 1:
            ui->lblViewersTxtLogFiles->setDisabled(true);
            ui->editViewersTxtLogFiles->setDisabled(true);
            ui->btnViewersTxtLogFiles->setDisabled(true);
            break;
        case 2:
            ui->lblViewersTxtLogFiles->setEnabled(true);
            ui->editViewersTxtLogFiles->setEnabled(true);
            ui->btnViewersTxtLogFiles->setEnabled(true);
            break;
        }
    int indexHtmlLog = ui->cmbHtmlLogFiles->currentIndex();
        switch (indexHtmlLog) {
        case 0:
            ui->lblViewersHtmlLogFiles->setDisabled(true);
            ui->editViewersHtmlLogFiles->setDisabled(true);
            ui->btnViewersHtmlLogFiles->setDisabled(true);
            break;
        case 1:
            ui->lblViewersHtmlLogFiles->setDisabled(true);
            ui->editViewersHtmlLogFiles->setDisabled(true);
            ui->btnViewersHtmlLogFiles->setDisabled(true);
            break;
        case 2:
            ui->lblViewersHtmlLogFiles->setEnabled(true);
            ui->editViewersHtmlLogFiles->setEnabled(true);
            ui->btnViewersHtmlLogFiles->setEnabled(true);
            break;
        }
    int indexDbfLog = ui->cmbDbfLogFile->currentIndex();
        switch (indexDbfLog) {
        case 0:
            ui->lblViewersDbfLogFiles->setDisabled(true);
            ui->editViewersDbfLogFiles->setDisabled(true);
            ui->btnViewersDbfLogFiles->setDisabled(true);
            break;
        case 1:
            ui->lblViewersDbfLogFiles->setDisabled(true);
            ui->editViewersDbfLogFiles->setDisabled(true);
            ui->btnViewersDbfLogFiles->setDisabled(true);
            break;
        case 2:
            ui->lblViewersDbfLogFiles->setEnabled(true);
            ui->editViewersDbfLogFiles->setEnabled(true);
            ui->btnViewersDbfLogFiles->setEnabled(true);
            break;
        }
}

/******************************************************************/

} // namespace SDPO


