#include "qFolderPropertiesDlg.h"
#include "ui_qFolderPropertiesDlg.h"

namespace SDPO {

/******************************************************************/

FolderPropertiesDlg::FolderPropertiesDlg(TFolder *folder, HMListService *hml, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FolderPropertiesDlg),
    m_folder(folder),
    m_HML(hml)
{
    ui->setupUi(this);
    init();
    connect(ui->btnBoxFolderProperties, SIGNAL(accepted()), this, SLOT(save()));
}

/******************************************************************/

FolderPropertiesDlg::~FolderPropertiesDlg()
{
    m_folder = nullptr;
    m_HML = nullptr;
    delete ui;
}

/******************************************************************/

void FolderPropertiesDlg::init()
{
    if (!m_folder) return;
    ui->lblFolderID->setText(QString::number(m_folder->getID()));
    ui->editSourceFolder->setText(m_folder->getPath());
    ui->tabColumns->init(m_folder);
    ui->tabColors->init(m_folder);
    //! TODO reports
    //! TODO statistics
    ui->tabRegional->init(m_folder);
    ui->tabComment->init(m_folder);
    //! TODO variables
    ui->tabSpecials->init(m_folder);
}

/******************************************************************/

void FolderPropertiesDlg::save()
{
    if (!m_folder) return;
    ui->tabColumns->save(m_folder);
    ui->tabColors->save(m_folder);
    //! TODO reports
    //! TODO statistics
    ui->tabRegional->save(m_folder);
    ui->tabComment->save(m_folder);
    //! TODO variables
    ui->tabSpecials->save(m_folder);
}

/******************************************************************/

} // namespace SDPO

