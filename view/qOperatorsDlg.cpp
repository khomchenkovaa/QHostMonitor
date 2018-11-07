#include "qOperatorsDlg.h"
#include "ui_qOperatorsDlg.h"
#include "io/ioUserProfileLoader.h"
#include "qFolderDlg.h"

#include <QMenu>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

namespace SDPO {

/******************************************************************/

OperatorsDlg::OperatorsDlg(HMListService *hml, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperatorsDlg),
    m_HML(hml)
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
    if (previous && previous->text() == ui->cmbID->currentText()) {
        if (!save(ui->listUserProfiles->row(previous) + 1)) {
            ui->listUserProfiles->selectionModel()->clearSelection();
            ui->listUserProfiles->setCurrentItem(previous);
            return;
        }
    }
    if (current && current->text() != ui->cmbID->currentText()) {
        load(ui->listUserProfiles->row(current) + 1);
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
        if (i) { // skip <Default>
            ui->listUserProfiles->addItem(profile.id);
        }
    }
    ui->listUserProfiles->setCurrentRow(idx);
}

/******************************************************************/

void OperatorsDlg::load(const int idx)
{
    GUserProfile profile = m_userProfiles.at(idx);
    ui->cmbID->setCurrentText(profile.id);
    ui->cmbFullName->setCurrentText(profile.name);
    ui->editPassword->setText(profile.password);
    ui->editConfirm->setText(profile.password);
    ui->cmbStatus->setCurrentIndex(profile.enabled?0:1);
    ui->cmbEmail->setCurrentText(profile.email);
    ui->cmbPager->setCurrentText(profile.pager);
    ui->cmbICQ->setCurrentText(profile.icq);
    ui->listAcceptRemoteConnection->clear();
    foreach (const QIpPair &pair, profile.rccFrom) {
        QListWidgetItem *item = new QListWidgetItem(pair.first);
        item->setCheckState( pair.second ? Qt::Checked : Qt::Unchecked );
        ui->listAcceptRemoteConnection->addItem(item);
    }
    ui->listUserRights->clear();
    for (int i = (int)PermissionID::PRM_CREATE; i <= (int)PermissionID::PRM_READ; i++) {
        QListWidgetItem *item = new QListWidgetItem(TEnums::permissionName((PermissionID)i));
        item->setCheckState( profile.hasPermission((PermissionID)i) ? Qt::Checked : Qt::Unchecked );
        ui->listUserRights->addItem(item);
    }
    ui->chkRccLimit->setChecked(profile.rccLimit);
    ui->spinRccLimit->setValue(profile.rccNumber);
    ui->editFolder->clear();
    if (profile.allowAll) {
        ui->rbAllFoldersAnyHml->setChecked(true);
    } else {
        bool contains = false;
        foreach(const QFoldersPair &pair, profile.folders) {
            if (m_HML->guid() == pair.first) {
                contains = true;
                ui->rbFolder->setChecked(true);
                ui->editFolder->setText(pair.second);
                break;
            }
        }
        if (!contains) {
            ui->rbNoAccessToHml->setChecked(true);
        }
    }
    setFieldsState(profile.id);
}

/******************************************************************/

bool OperatorsDlg::save(const int idx)
{
    if (ui->editPassword->text() != ui->editConfirm->text()) {
        QMessageBox::warning(this, tr("Warning"), tr("Passwords mismatch"));
        return false;
    }
    GUserProfile profile = m_userProfiles.at(idx);
    profile.id = ui->cmbID->currentText();
    profile.name = ui->cmbFullName->currentText();
    profile.password = ui->editPassword->text();
    profile.enabled = (ui->cmbStatus->currentIndex() == 0);
    profile.email = ui->cmbEmail->currentText();
    profile.pager = ui->cmbPager->currentText();
    profile.icq = ui->cmbICQ->currentText();
    for (int i=0; i<ui->listAcceptRemoteConnection->count();i++) {
        QListWidgetItem *item = ui->listAcceptRemoteConnection->item(i);
        QIpPair pair;
        pair.first = item->text();
        pair.second = (item->checkState() == Qt::Checked);
    }
    for (int i = (int)PermissionID::PRM_CREATE; i <= (int)PermissionID::PRM_READ; i++) {
        QListWidgetItem *item = ui->listUserRights->item(i);
        profile.setPermission((PermissionID)i, item->checkState() == Qt::Checked);
    }
    profile.rccLimit = ui->chkRccLimit->isChecked();
    profile.rccNumber = ui->spinRccLimit->value();
    profile.allowAll = ui->rbAllFoldersAnyHml->isChecked();
    if (ui->rbFolder->isChecked()) {
        QFoldersPair pair;
        pair.first = m_HML->guid();
        pair.second = ui->editFolder->text();
        bool found = false;
        for (int i=0; i<profile.folders.count();i++) {
            if (pair.first == profile.folders.at(i).first) {
                found = true;
                profile.folders.replace(i, pair);
                break;
            }
        }
        if (!found) {
            profile.folders.append(pair);
        }
    }
    if (ui->rbNoAccessToHml->isChecked()) {
        for (int i=0; i<profile.folders.count();i++) {
            if (m_HML->guid() == profile.folders.at(i).first) {
                profile.folders.removeAt(i);
                break;
            }
        }
    }
    m_userProfiles.replace(idx, profile);
    return true;
}

/******************************************************************/

void OperatorsDlg::setFieldsState(const QString &name)
{
    ui->cmbFullName->setEnabled(true);
    ui->editPassword->setEnabled(true);
    ui->editConfirm->setEnabled(true);
    ui->cmbStatus->setEnabled(true);
    ui->cmbEmail->setEnabled(true);
    ui->cmbPager->setEnabled(true);
    ui->cmbICQ->setEnabled(true);
    ui->listAcceptRemoteConnection->setEnabled(true);
    ui->listUserRights->setEnabled(true);
    ui->chkRccLimit->setEnabled(true);
    ui->spinRccLimit->setEnabled(true);
    ui->rbAllFoldersAnyHml->setEnabled(true);
    ui->rbFolder->setEnabled(true);
    ui->rbNoAccessToHml->setEnabled(true);
    ui->editFolder->setEnabled(true);
    ui->btnFolder->setEnabled(true);
    if (name == ROLE_ADMIN) {
        ui->cmbStatus->setDisabled(true);
    } else if (name == ROLE_LOCAL) {
        ui->editPassword->setDisabled(true);
        ui->editConfirm->setDisabled(true);
        ui->cmbStatus->setDisabled(true);
        ui->cmbEmail->setDisabled(true);
        ui->cmbPager->setDisabled(true);
        ui->cmbICQ->setDisabled(true);
        ui->listAcceptRemoteConnection->setDisabled(true);
        ui->chkRccLimit->setDisabled(true);
        ui->spinRccLimit->setDisabled(true);
        ui->rbAllFoldersAnyHml->setDisabled(true);
        ui->rbFolder->setDisabled(true);
        ui->rbNoAccessToHml->setDisabled(true);
        ui->editFolder->setDisabled(true);
        ui->btnFolder->setDisabled(true);
    } else if (name == ROLE_WATCHDOG) {
        ui->listUserRights->setDisabled(true);
        ui->chkRccLimit->setDisabled(true);
        ui->spinRccLimit->setDisabled(true);
        ui->rbAllFoldersAnyHml->setDisabled(true);
        ui->rbFolder->setDisabled(true);
        ui->rbNoAccessToHml->setDisabled(true);
        ui->editFolder->setDisabled(true);
        ui->btnFolder->setDisabled(true);
    }
}

/******************************************************************/

void OperatorsDlg::on_btnBoxUserProfiles_accepted()
{
    // save current
    int idx = ui->listUserProfiles->currentRow();
    if (idx != -1) {
        if (!save(idx+1)) return;
    }
    // if something removed
    while(m_userProfiles.count() < GData::userProfiles.count()) {
        GData::userProfiles.removeLast();
    }
    // if something edited or added
    for (int i=0; i< m_userProfiles.count(); i++) {
        GUserProfile profile = m_userProfiles.at(i);
        if (i < GData::userProfiles.count()) {
            GData::userProfiles.replace(i, profile);
        } else {
            GData::userProfiles.append(profile);
        }
    }
    // save all
    IOUserProfileLoader loader;
    loader.save();
    accept();
}

/******************************************************************/

void OperatorsDlg::on_btnFolder_clicked()
{
    FolderDlg folderDlg;
    folderDlg.setWindowTitle(tr("Select folder"));
    FoldersAndViewsModel *model = new FoldersAndViewsModel(m_HML, FoldersAndViewsModel::FOLDERS);
    folderDlg.setModel(model, ui->editFolder->text());
    if (QDialog::Accepted == folderDlg.exec()) {
        ui->editFolder->setText(folderDlg.path());
    }
}

/******************************************************************/

void OperatorsDlg::on_btnNew_clicked()
{
    // save current
    int row = ui->listUserProfiles->currentRow();
    if (row == -1) return;
    int idx = row + 1;
    if (!save(idx+1)) return;
    // ask new name
    bool ok;
    QString	newName = QInputDialog::getText(this, tr("New profile"), tr("Operator name"), QLineEdit::Normal, QString(), &ok);
    if (!ok || newName.isEmpty()) return;
    for (int i=0; i<m_userProfiles.count(); i++) {
        if (m_userProfiles.at(i).id == newName) {
            QMessageBox::warning(this, tr("Warning"), tr("Operator '%1' already exists").arg(newName));
            return;
        }
    }
    GUserProfile defaultProfile = m_userProfiles.at(0);
    GUserProfile profile = defaultProfile.clone();
    profile.id = newName;
    m_userProfiles.append(profile);
    ui->listUserProfiles->addItem(newName);
    ui->listUserProfiles->setCurrentRow(ui->listUserProfiles->count()-1);
}

/******************************************************************/

void OperatorsDlg::on_btnCopy_clicked()
{
    // save current
    int row = ui->listUserProfiles->currentRow();
    if (row == -1) return;
    int idx = row + 1;
    if (!save(idx+1)) return;
    // ask new name
    bool ok;
    QString	newName = QInputDialog::getText(this, tr("Copy profile"), tr("New operator's' name"), QLineEdit::Normal, QString(), &ok);
    if (!ok || newName.isEmpty()) return;
    for (int i=0; i<m_userProfiles.count(); i++) {
        if (m_userProfiles.at(i).id == newName) {
            QMessageBox::warning(this, tr("Warning"), tr("Operator '%1' already exists").arg(newName));
            return;
        }
    }
    GUserProfile curProfile = m_userProfiles.at(idx);
    GUserProfile profile = curProfile.clone();
    profile.id = newName;
    m_userProfiles.append(profile);
    ui->listUserProfiles->addItem(newName);
    ui->listUserProfiles->setCurrentRow(ui->listUserProfiles->count()-1);
}

/******************************************************************/

void OperatorsDlg::on_btnRename_clicked()
{
    // save current
    int row = ui->listUserProfiles->currentRow();
    if (row == -1) return;
    int idx = row + 1;
    if (m_userProfiles.at(idx).id == ROLE_DEFAULT
        || m_userProfiles.at(idx).id == ROLE_ADMIN
        || m_userProfiles.at(idx).id == ROLE_LOCAL
        || m_userProfiles.at(idx).id == ROLE_WATCHDOG) {
        QMessageBox::warning(this, tr("Warning"), tr("User '%1' must exists. You can not change name for this user.").arg(m_userProfiles.at(idx).id));
        return;
    }
    if (!save(idx+1)) return;
    // ask new name
    bool ok;
    QString	newName = QInputDialog::getText(this, tr("Rename operator"), tr("Rename to"), QLineEdit::Normal, QString(), &ok);
    if (!ok || newName.isEmpty()) return;
    for (int i=0; i<m_userProfiles.count(); i++) {
        if (i == idx) continue;
        if (m_userProfiles.at(i).id == newName) {
            QMessageBox::warning(this, tr("Warning"), tr("Operator '%1' already exists").arg(newName));
            return;
        }
    }
    GUserProfile profile = m_userProfiles.at(idx);
    profile.id = newName;
    m_userProfiles.replace(idx, profile);
    ui->listUserProfiles->item(row)->setText(newName);
    load(idx);
}

/******************************************************************/

void OperatorsDlg::on_btnDelete_clicked()
{
    int row = ui->listUserProfiles->currentRow();
    if (row == -1) return;
    int idx = row + 1;
    if (idx >= m_userProfiles.count()) return;
    if (m_userProfiles.at(idx).id == ROLE_DEFAULT
        || m_userProfiles.at(idx).id == ROLE_ADMIN
        || m_userProfiles.at(idx).id == ROLE_LOCAL
        || m_userProfiles.at(idx).id == ROLE_WATCHDOG) {
        QMessageBox::warning(this, tr("Warning"), tr("User '%1' must exists. You can not remove this user.").arg(m_userProfiles.at(idx).id));
        return;
    }
    QListWidgetItem *item = ui->listUserProfiles->takeItem(row);
    if (item) {
        delete item;
    }
    m_userProfiles.removeAt(idx);
    if (row == ui->listUserProfiles->count()) row--;
    ui->cmbID->clear();
    ui->listUserProfiles->setCurrentRow(row);
}

/******************************************************************/

void OperatorsDlg::on_listAcceptRemoteConnection_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu(this);
    menu.addAction(ui->actAddIP);
    menu.addAction(ui->actRemoveIP);
    ui->actRemoveIP->setEnabled(ui->listAcceptRemoteConnection->currentRow() != -1);
    menu.exec(ui->listAcceptRemoteConnection->mapToGlobal(pos));
}

/******************************************************************/

void OperatorsDlg::on_actAddIP_triggered()
{
    bool ok;
    QString	ip = QInputDialog::getText(this, tr("Add Item"), tr("Enter IP address"), QLineEdit::Normal, QString(), &ok);
    if (!ok || ip.isEmpty()) return;
    QListWidgetItem *item = new QListWidgetItem(ip);
    item->setCheckState( Qt::Checked );
    ui->listAcceptRemoteConnection->addItem(item);
}

/******************************************************************/

void OperatorsDlg::on_actRemoveIP_triggered()
{
    int idx = ui->listAcceptRemoteConnection->currentRow();
    if (idx != -1) {
        QListWidgetItem *item = ui->listAcceptRemoteConnection->takeItem(idx);
        if (item) {
            delete item;
        }
    }
}

/******************************************************************/

} // namespace SDPO







