#include "qCommonViewPropertiesDlg.h"
#include "ui_qCommonViewPropertiesDlg.h"

namespace SDPO {

/******************************************************************/

CommonViewPropertiesDlg::CommonViewPropertiesDlg(TFolder *folder, HMListService *hml, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommonViewPropertiesDlg),
    m_folder(folder),
    m_HML(hml)
{
    ui->setupUi(this);
    init();
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

/******************************************************************/

CommonViewPropertiesDlg::~CommonViewPropertiesDlg()
{
    m_folder = 0;
    m_HML = 0;
    delete ui;
}

/******************************************************************/

void CommonViewPropertiesDlg::save()
{
    if (!m_folder) return;
    ui->tabColumns->save(m_folder);
    ui->tabColors->save(m_folder);
    ui->tabComment->save(m_folder);
    this->accept();
}

/******************************************************************/

void CommonViewPropertiesDlg::init()
{
    if (!m_folder) return;
    ui->tabColumns->init(m_folder);
    ui->tabColors->init(m_folder);
    ui->tabComment->init(m_folder);
}

/******************************************************************/

} // namespace SDPO
