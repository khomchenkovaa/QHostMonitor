#include "qTextLogWidget.h"
#include "ui_qTextLogWidget.h"
#include "qTextLogPropertiesDlg.h"
#include <QFileDialog>

namespace SDPO {

TextLogWidget::TextLogWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::TextLogWidget)
{
    ui->setupUi(this);
    connect(ui->btnBadDlg,SIGNAL(clicked()),this,SLOT(openTextLogPropertiesDlg()));
    connect(ui->btnGoodDlg,SIGNAL(clicked()),this,SLOT(openTextLogPropertiesDlg()));
    connect(ui->btnDisplayDlg,SIGNAL(clicked()),this,SLOT(openTextLogPropertiesDlg()));
}

TextLogWidget::~TextLogWidget()
{
    delete ui;
}

void TextLogWidget::openTextLogPropertiesDlg()
{
    TextLogPropertiesDlg dlg;
    dlg.exec();
}

void TextLogWidget::on_btnFileDlg_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editFile->text());
    if (!fileName.isEmpty()) {
        ui->editFile->setText(fileName);
    }
}

} // namespace SDPO


