#include "qDynamicViewPropertiesDlg.h"
#include "ui_qDynamicViewPropertiesDlg.h"
#include "qFolderDlg.h"
#include "hmListService.h"

namespace SDPO {

/******************************************************************/

DynamicViewPropertiesDlg::DynamicViewPropertiesDlg(TView *view, HMListService *hml, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DynamicViewPropertiesDlg),
    m_view(view),
    m_HML(hml)
{
    ui->setupUi(this);
    init();
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

/******************************************************************/

DynamicViewPropertiesDlg::~DynamicViewPropertiesDlg()
{
    m_view = 0;
    m_HML = 0;
    delete ui;
}

/******************************************************************/

void DynamicViewPropertiesDlg::init()
{
    if (!m_view) return;

    ui->editViewName->setText(m_view->getName());
    m_SourceFolder = m_view->getSourceFolder();
    ui->editSourceFolder->setText(m_SourceFolder->getPath());
    ui->chkIncludeSubfolders->setChecked(m_view->isRecursive());
    ui->tabViewCriteria->init(m_view);
    ui->tabColumns->init(m_view);
    ui->tabColors->init(m_view);
    //! TODO Reports
    ui->tabComment->init(m_view);
}

/******************************************************************/

void DynamicViewPropertiesDlg::on_btnSelectSubfolders_clicked()
{
    FolderDlg dlg;
    dlg.setWindowTitle(tr("Select source folder"));
    FoldersAndViewsModel *model = new FoldersAndViewsModel(m_HML->rootItem(), FoldersAndViewsModel::FOLDERS);
    dlg.setModel(model, m_SourceFolder->getPath());
    if (QDialog::Accepted != dlg.exec()) {
        return;
    }
    QString path = dlg.path();
    TNode *node = m_HML->nodeByPath(path);
    m_SourceFolder = qobject_cast<TFolder*>(node);
    ui->editSourceFolder->setText(m_SourceFolder->getPath());
}

/******************************************************************/

void DynamicViewPropertiesDlg::save()
{
    if (!m_view) return;

    m_view->setName(ui->editViewName->text());
    m_view->setSourceFolder(m_SourceFolder);
    m_view->setRecursive(ui->chkIncludeSubfolders->isChecked());
    ui->tabViewCriteria->save(m_view);
    ui->tabColumns->save(m_view);
    ui->tabColors->save(m_view);
    //! TODO Reports
    ui->tabComment->save(m_view);
    m_view->updateList();

    this->accept();
}

/******************************************************************/

} // namespace SDPO

