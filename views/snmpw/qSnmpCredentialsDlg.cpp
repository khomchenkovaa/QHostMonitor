#include "qSnmpCredentialsDlg.h"
#include "ui_qSnmpCredentialsDlg.h"

#include "ioSnmpCredentialsLoader.h"

#include <QtWidgets>

using namespace SDPO;

/*****************************************************************/

QSnmpCredentialsDlg::QSnmpCredentialsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSnmpCredentialsDlg)
{
    ui->setupUi(this);
}

/*****************************************************************/

QSnmpCredentialsDlg::~QSnmpCredentialsDlg()
{
    delete ui;
}

/*****************************************************************/

void QSnmpCredentialsDlg::init(int idx)
{
     ui->listProfiles->clear();
     m_Profiles.clear();
     foreach (const SnmpProfile &profile, SnmpProfile::credentials) {
         m_Profiles.append(SnmpProfile(profile));
         ui->listProfiles->addItem(profile.name);
     }
     connect(ui->cmbSnmpVersion, SIGNAL(currentIndexChanged(int)),this,SLOT(valueChanged()));
     connect(ui->cmbAuthorization, SIGNAL(currentIndexChanged(int)),this,SLOT(valueChanged()));
     connect(ui->cmbPrivacyType, SIGNAL(currentIndexChanged(int)),this,SLOT(valueChanged()));
     ui->listProfiles->setCurrentRow(idx);
}

/*****************************************************************/

int QSnmpCredentialsDlg::getSelected() const
{
    return ui->listProfiles->currentRow();
}

/*****************************************************************/

void QSnmpCredentialsDlg::on_btnNew_clicked()
{
    bool ok;
    QString newName = QInputDialog::getText(this, tr("New SNMP account"),tr("Account name"), QLineEdit::Normal, QString(), &ok);
    if (!ok) {
        return;
    }
    foreach (const SnmpProfile &profile, m_Profiles) {
        if(profile.name == newName) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        QMessageBox::warning(this, tr("Warning"),
                             QString("Account '%1' already exists").arg(newName));
        return;
    }
    SnmpProfile newProfile;
    newProfile.name = newName;
    m_Profiles.append(newProfile);
    ui->listProfiles->addItem(newName);
    ui->listProfiles->setCurrentRow(m_Profiles.count()-1);
}

/*****************************************************************/

void QSnmpCredentialsDlg::on_btnRename_clicked()
{
    int idx = ui->listProfiles->currentRow();
    SnmpProfile profile = m_Profiles.at(idx);
    bool ok;
    QString newName = QInputDialog::getText(this, tr("Rename account"),
                                            tr("Rename to"),
                                            QLineEdit::Normal,
                                            profile.name, &ok);
    if (!ok) {
        return; // Cancel pressed
    }
    for (int i=0; i < m_Profiles.count(); i++) {
        if (i == idx) {
            continue;
        }
        if(m_Profiles.at(i).name == newName) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        QMessageBox::warning(this, tr("Warning"),
                             QString("Account '%1' already exists").arg(newName));
        return;
    }
    SnmpProfile newProfile(profile);
    newProfile.name = newName;
    m_Profiles.replace(idx,newProfile);
    ui->listProfiles->currentItem()->setText(newName);
    ui->listProfiles->setCurrentRow(idx);
    load(idx);
}

/*****************************************************************/

void QSnmpCredentialsDlg::on_btnDelete_clicked()
{
    int idx = ui->listProfiles->currentRow();
    m_Profiles.removeAt(idx);
    QListWidgetItem *item = ui->listProfiles->takeItem(idx);
    delete item;
    if (idx >= m_Profiles.count()) {
        idx = m_Profiles.count() - 1;
    }
    ui->listProfiles->setCurrentRow(idx);
}

/*****************************************************************/

void SDPO::QSnmpCredentialsDlg::on_listProfiles_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (previous) {
        save(ui->listProfiles->row(previous));
    }
    if (current) {
        load(ui->listProfiles->row(current));
    }
}

/*****************************************************************/

void QSnmpCredentialsDlg::valueChanged()
{
    if (ui->cmbSnmpVersion->currentIndex() == 2) { // SNMP v3
        ui->editContext->setEnabled(true);
        ui->cmbAuthorization->setEnabled(true);
    } else {
        ui->editContext->setEnabled(false);
        ui->cmbAuthorization->setEnabled(false);
        ui->cmbAuthorization->setCurrentIndex(0);
    }

    if (ui->cmbAuthorization->currentIndex()) {
        ui->editAuthPassword->setEnabled(true);
        ui->cmbPrivacyType->setEnabled(true);
    } else { // AuthNone
        ui->editAuthPassword->setEnabled(false);
        ui->cmbPrivacyType->setEnabled(false);
        ui->cmbPrivacyType->setCurrentIndex(0);
    }

    ui->editPrivacyPassword->setEnabled(ui->cmbPrivacyType->currentIndex());
}

/*****************************************************************/

void QSnmpCredentialsDlg::load(const int idx)
{
    SnmpProfile profile = m_Profiles.at(idx);
    ui->editProfileName->setText(profile.name);
    switch(profile.version) {
    case SNMPv1:  ui->cmbSnmpVersion->setCurrentIndex(0); break;
    case SNMPv2c: ui->cmbSnmpVersion->setCurrentIndex(1); break;
    case SNMPv3:  ui->cmbSnmpVersion->setCurrentIndex(2); break;
    case SNMPvDefault: break;
    }
    ui->editCommunity->setText(profile.community);
    ui->editContext->setText(profile.context);
    ui->cmbAuthorization->setCurrentIndex(static_cast<int>(profile.auth));
    ui->editAuthPassword->setText(profile.authPwd);
    ui->cmbPrivacyType->setCurrentIndex(static_cast<int>(profile.privType));
    ui->editPrivacyPassword->setText(profile.privPwd);
    ui->chkOpaqueData->setCheckState(profile.chkOpaque? Qt::Checked : Qt::Unchecked);
}

/*****************************************************************/

void QSnmpCredentialsDlg::save(const int idx)
{
    SnmpProfile profile = m_Profiles.at(idx);
    profile.name = ui->editProfileName->text();
    switch(ui->cmbSnmpVersion->currentIndex()) {
    case 0: profile.version = SNMPv1;  break;
    case 1: profile.version = SNMPv2c; break;
    case 2: profile.version = SNMPv3;  break;
    }
    profile.community = ui->editCommunity->text();
    profile.context = ui->editContext->text();
    profile.auth = static_cast<SnmpSecAuth>(ui->cmbAuthorization->currentIndex());
    profile.authPwd = ui->editAuthPassword->text();
    profile.privType = static_cast<SnmpSecPrivType>(ui->cmbPrivacyType->currentIndex());
    profile.privPwd = ui->editPrivacyPassword->text();
    profile.chkOpaque = (ui->chkOpaqueData->checkState() == Qt::Checked);
    m_Profiles.replace(idx, profile);
}

/*****************************************************************/

void SDPO::QSnmpCredentialsDlg::on_btnBox_accepted()
{
    // save current
    int idx = ui->listProfiles->currentRow();
    if (idx != -1) {
        save(idx);
    }
    // if something removed
    while(m_Profiles.count() < SnmpProfile::credentials.count()) {
        SnmpProfile::credentials.removeLast();
    }
    // if something edited or added
    for (int i=0; i< m_Profiles.count(); i++) {
        SnmpProfile profile = m_Profiles.at(i);
        if (i < SnmpProfile::credentials.count()) {
            SnmpProfile::credentials.replace(i, profile);
        } else {
            SnmpProfile::credentials.append(profile);
        }
    }
    // save all
    IOSnmpCredentialsLoader loader;
    loader.save();
    accept();
}

/*****************************************************************/
