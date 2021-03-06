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

void ViewersOptionsWidget::init(QSettings *s)
{

    ui->cmbTxtLogFiles->setCurrentIndex (s->value(SKEY_LOGVIEWER_TextViewerMode, SVAL_LOGVIEWER_TextViewerMode).toInt());
    ui->cmbHtmlLogFiles->setCurrentIndex(s->value(SKEY_LOGVIEWER_HtmlViewerMode, SVAL_LOGVIEWER_HtmlViewerMode).toInt());
    ui->cmbDbfLogFile->setCurrentIndex  (s->value(SKEY_LOGVIEWER_DbfViewerMode, SVAL_LOGVIEWER_DbfViewerMode).toInt());
    on_SelectLogViewer();
    connect(ui->cmbTxtLogFiles, SIGNAL(currentIndexChanged(int)), this, SLOT(on_SelectLogViewer()));
    connect(ui->cmbHtmlLogFiles, SIGNAL(currentIndexChanged(int)), this, SLOT(on_SelectLogViewer()));
    connect(ui->cmbDbfLogFile, SIGNAL(currentIndexChanged(int)), this, SLOT(on_SelectLogViewer()));

    ui->editViewersTxtLogFiles->setText (s->value(SKEY_LOGVIEWER_TextViewerCmd, SVAL_LOGVIEWER_TextViewerCmd).toString());
    ui->editViewersHtmlLogFiles->setText(s->value(SKEY_LOGVIEWER_HtmlViewerCmd).toString());
    ui->editViewersDbfLogFiles->setText (s->value(SKEY_LOGVIEWER_DbfViewerCmd).toString());
}

/******************************************************************/

void ViewersOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_LOGVIEWER_TextViewerMode, ui->cmbTxtLogFiles->currentIndex());
    s->setValue(SKEY_LOGVIEWER_HtmlViewerMode, ui->cmbHtmlLogFiles->currentIndex());
    s->setValue(SKEY_LOGVIEWER_DbfViewerMode, ui->cmbDbfLogFile->currentIndex());

    s->setValue(SKEY_LOGVIEWER_TextViewerCmd, ui->editViewersTxtLogFiles->text());
    s->setValue(SKEY_LOGVIEWER_HtmlViewerCmd, ui->editViewersHtmlLogFiles->text());
    s->setValue(SKEY_LOGVIEWER_DbfViewerCmd, ui->editViewersDbfLogFiles->text());
}

/******************************************************************/

void ViewersOptionsWidget::on_SelectLogViewer()
{
    bool txtLogEnabled = (ui->cmbTxtLogFiles->currentIndex() == 2);
    ui->lblViewersTxtLogFiles->setEnabled(txtLogEnabled);
    ui->editViewersTxtLogFiles->setEnabled(txtLogEnabled);
    ui->btnViewersTxtLogFiles->setEnabled(txtLogEnabled);

    bool htmlLogEnabled = (ui->cmbHtmlLogFiles->currentIndex() == 2);
    ui->lblViewersHtmlLogFiles->setEnabled(htmlLogEnabled);
    ui->editViewersHtmlLogFiles->setEnabled(htmlLogEnabled);
    ui->btnViewersHtmlLogFiles->setEnabled(htmlLogEnabled);

    bool dbfLogEnabled = (ui->cmbDbfLogFile->currentIndex() == 2);
    ui->lblViewersDbfLogFiles->setEnabled(dbfLogEnabled);
    ui->editViewersDbfLogFiles->setEnabled(dbfLogEnabled);
    ui->btnViewersDbfLogFiles->setEnabled(dbfLogEnabled);
}

/******************************************************************/

} // namespace SDPO


