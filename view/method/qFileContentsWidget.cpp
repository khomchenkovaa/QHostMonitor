#include "qFileContentsWidget.h"
#include "ui_qFileContentsWidget.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

FileContentsWidget::FileContentsWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::FileContentsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

FileContentsWidget::~FileContentsWidget()
{
    delete ui;
}

/******************************************************************/

void FileContentsWidget::on_btnEditFile_clicked()
{
   QString dirName = QFileDialog::getExistingDirectory(this,tr("Select Directory"),ui->lineEditFile->text());
   if (!dirName.isEmpty()) {
       ui->lineEditFile->setText(dirName);
   }

/******************************************************************/

} // namespace SDPO

}
