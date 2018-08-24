#include "qOperatorsDlg.h"
#include "ui_qOperatorsDlg.h"

namespace SDPO {

/******************************************************************/

OperatorsDlg::OperatorsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperatorsDlg)
{
    ui->setupUi(this);
    init();
}

/******************************************************************/

OperatorsDlg::~OperatorsDlg()
{
    delete ui;
}

/******************************************************************/

void OperatorsDlg::on_listUserProfiles_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (previous) {
        save(ui->listUserProfiles->row(previous));
    }
    if (current) {
        load(ui->listUserProfiles->row(current));
    }
}

/******************************************************************/

void OperatorsDlg::init()
{
    int idx = 0;
    ui->listUserProfiles->clear();
    m_userProfiles.clear();
    for (int i=0; i< GData::userProfiles.count(); i++) {
        GUserProfile profile = GData::userProfiles.at(i);
        m_userProfiles.append(profile.clone());
        ui->listUserProfiles->addItem(profile.id);
    }
    ui->listUserProfiles->setCurrentRow(idx);
}

/******************************************************************/

void OperatorsDlg::load(const int idx)
{
    GUserProfile profile = m_userProfiles.at(idx);
    ui->cmbID->setCurrentText(profile.id);
    ui->cmbFullName->setCurrentText(profile.name);
    ui->cmbPassword->setCurrentText(profile.password);
    ui->cmbPasswordConfirm->setCurrentText(profile.password);
    ui->cmbStatus->setCurrentIndex(profile.enabled?0:1);
    ui->cmbEmail->setCurrentText(profile.email);
    ui->cmbPager->setCurrentText(profile.pager);
    ui->cmbICQ->setCurrentText(profile.icq);
    //! TODO user rights
}

/******************************************************************/

void OperatorsDlg::save(const int idx)
{
    GUserProfile profile = m_userProfiles.at(idx);
    profile.id = ui->cmbID->currentText();
    profile.name = ui->cmbFullName->currentText();
    //! TODO check password
    profile.password = ui->cmbPassword->currentText();
    profile.enabled = (ui->cmbStatus->currentIndex() == 0);
    profile.email = ui->cmbEmail->currentText();
    profile.pager = ui->cmbPager->currentText();
    profile.icq = ui->cmbICQ->currentText();
    //! TODO user rights
    m_userProfiles.replace(idx, profile);
}

/******************************************************************/

} // namespace SDPO
