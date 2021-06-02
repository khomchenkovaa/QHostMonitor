#include "qFolderDlg.h"
#include "ui_qFolderDlg.h"
#include "tNode.h"
#include "viewmodel/mFoldersAndViewsModel.h"
#include <QModelIndex>

namespace SDPO {

/******************************************************************/

FolderDlg::FolderDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FolderDlg)
{
    ui->setupUi(this);

    ui->btnCopy->setVisible(false);
    ui->btnEdit->setVisible(false);
    ui->btnDisable->setVisible(false);
}

/******************************************************************/

FolderDlg::~FolderDlg()
{
    delete m_model;
    delete ui;
}

/******************************************************************/

QString FolderDlg::path()
{
    QModelIndex idx = ui->treeView->currentIndex();
    if (!idx.isValid()) {
        return QString();
    }
    TNode *item = m_model->itemFromIndex(idx);
    return item->getPath();
}

/******************************************************************/

void FolderDlg::setModel(FoldersAndViewsModel *model, QString path)
{
    m_model = model;
    ui->treeView->setModel(m_model);
    QModelIndex idx = m_model->indexFromPath(path);
    ui->treeView->setCurrentIndex(idx);
}

/******************************************************************/

void FolderDlg::activateButtons() {
    ui->btnCopy->setVisible(true);
    ui->btnEdit->setVisible(true);
    ui->btnDisable->setVisible(true);
    on_btnCopy_clicked();
}

/******************************************************************/

bool FolderDlg::isDisabled()
{
    return ui->btnDisable->isChecked();
}

/******************************************************************/

bool FolderDlg::isEdit()
{
    return ui->btnEdit->isChecked();
}

/******************************************************************/

void FolderDlg::on_btnCopy_clicked()
{
    ui->btnCopy->setChecked(true);
    ui->btnEdit->setChecked(false);
    ui->btnDisable->setChecked(false);
}

/******************************************************************/

void FolderDlg::on_btnEdit_clicked()
{
    ui->btnCopy->setChecked(false);
    ui->btnEdit->setChecked(true);
    ui->btnDisable->setChecked(false);
}

/******************************************************************/

void FolderDlg::on_btnDisable_clicked()
{
    ui->btnCopy->setChecked(false);
    ui->btnEdit->setChecked(false);
    ui->btnDisable->setChecked(true);
}

/******************************************************************/

} // namespace SDPO

