#include "qExportToTxtDlg.h"
#include "ui_qExportToTxtDlg.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

ExportToTxtDlg::ExportToTxtDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportToTxtDlg)
{
    ui->setupUi(this);
}

/******************************************************************/

ExportToTxtDlg::~ExportToTxtDlg()
{
    delete ui;
}

/******************************************************************/

void ExportToTxtDlg::on_btnTargerFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Export to text file"),
                                                    ui->editTargetFile->text(),"TextFiles(*.hmi *.txt)");
    if (!fileName.isEmpty()) {
        ui->editTargetFile->setText(fileName);
    }
}

/******************************************************************/

QString ExportToTxtDlg::targetFile() const
{
    return ui->editTargetFile->text();
}

/******************************************************************/

bool ExportToTxtDlg::isFolderIncluded() const
{
    return ui->chbxIncludeFolder->isChecked();
}

/******************************************************************/

bool ExportToTxtDlg::isLinksIncluded() const
{
    return ui->chbxIncludeLinks->isChecked();
}

/******************************************************************/

int ExportToTxtDlg::exportType() const
{
    //! TODO refactor to ENUM
    if (ui->rbtnAllTests->isChecked()) return 0;
    if (ui->rbtnFolderWithSubs->isChecked()) return 1;
    if (ui->rbtnFolderOnly->isChecked()) return 2;
    if (ui->rbtnTestsSelected->isChecked()) return 3;
    return -1;
}

/******************************************************************/

void ExportToTxtDlg::setSelectedTests(const bool value)
{
    ui->rbtnTestsSelected->setEnabled(value);
}

/******************************************************************/

} // namespace SDPO {
