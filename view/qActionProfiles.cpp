#include "qActionProfiles.h"
#include "ui_qActionProfiles.h"
#include "qActionProfilesAddMenu.h"
#include "qActionPropertiesDialog.h"
#include "gData.h"
#include <QtWidgets>

namespace SDPO {

/******************************************************************/

ActionProfiles::ActionProfiles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActionProfiles)
{
    ui->setupUi(this);
    m_badModel = new ActionsTreeModel(this);
    ui->trvBad->setModel(m_badModel);
    connect(ui->trvBad->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(onBadCurrentChanged()));
    m_goodModel = new ActionsTreeModel(this);
    ui->trvGood->setModel(m_goodModel);
    connect(ui->trvGood->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(onGoodCurrentChanged()));
}

/******************************************************************/

ActionProfiles::~ActionProfiles()
{
    delete ui;
}

/******************************************************************/

void ActionProfiles::currentChanged()
{
    int idx = ui->lstProfiles->currentRow();
    if (idx >= GData::actionProfiles.count()) {
        idx = GData::actionProfiles.count()-1;
    }
    GActionProfile profile = GData::actionProfiles.at(idx);
    m_badModel->setActionList(profile.onBad);
    if (profile.onBad.count()) {
        ui->trvBad->resizeColumnToContents(0);
    }
    ui->txtBad->clear();
    m_goodModel->setActionList(profile.onGood);
    if (profile.onGood.count()) {
        ui->trvGood->resizeColumnToContents(0);
    }
    ui->txtGood->clear();
    ui->txtComment->clear();
    foreach(const QString &line, profile.comments) {
        ui->txtComment->appendPlainText(line);
    }
}

/******************************************************************/

void ActionProfiles::onBadCurrentChanged()
{
    int idx = ui->lstProfiles->currentRow();
    if (idx > GData::actionProfiles.count()) return;
    GActionProfile profile = GData::actionProfiles.at(idx);
    QModelIndex index = ui->trvBad->currentIndex();
    if (index.isValid() && index.row() < profile.onBad.count()) {
        TestAction* action = profile.onBad.at(index.row());
        ui->txtBad->setPlainText(action->description(true).join("\n"));
    }
}

/******************************************************************/

void ActionProfiles::onGoodCurrentChanged()
{
    int idx = ui->lstProfiles->currentRow();
    if (idx > GData::actionProfiles.count()) return;
    GActionProfile profile = GData::actionProfiles.at(idx);
    QModelIndex index = ui->trvGood->currentIndex();
    if (index.isValid() && index.row() < profile.onGood.count()) {
        TestAction* action = profile.onGood.at(index.row());
        ui->txtGood->setPlainText(action->description(false).join("\n"));
    }
}

/******************************************************************/

void ActionProfiles::on_btnProfilesNew_clicked()
{
    bool ok;
    QString newName = QInputDialog::getText(this, tr("New profile"), tr("Profile name"), QLineEdit::Normal, QString(), &ok);
    if (!ok) return;
    foreach (const GActionProfile &profile, GData::actionProfiles) {
        if(profile.name == newName) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        QMessageBox::warning(this, tr("Action profiles"),
                             QString("Profile named '%1' already exists").arg(newName));
        return;
    }
    GActionProfile newProfile;
    newProfile.name = newName;
    GData::actionProfiles.append(newProfile);
    ui->lstProfiles->addItem(newName);
    ui->lstProfiles->setCurrentRow(GData::actionProfiles.count()-1);
}

/******************************************************************/

void ActionProfiles::on_btnProfilesCopy_clicked()
{
    int idx = ui->lstProfiles->currentRow();
    GActionProfile profile = GData::actionProfiles.at(idx);
    bool ok;
    QString newName = QInputDialog::getText(this, tr("Copy profile"),
                                            tr("New profile's name"),
                                            QLineEdit::Normal,
                                            QString("Copy of %1").arg(profile.name), &ok);
    if (!ok) {
        return;
    }
    foreach (const GActionProfile &tmp, GData::actionProfiles) {
        if(tmp.name == newName) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        QMessageBox::warning(this, tr("Copy profile"),
                             QString("Profile named '%1' already exists").arg(newName));
        return;
    }
    GActionProfile newProfile;
    newProfile.name = newName;
    newProfile.comments = profile.comments;
    foreach (TestAction* item, profile.onBad) {
        newProfile.onBad.append(item->clone());
    }
    foreach (TestAction* item, profile.onGood) {
        newProfile.onGood.append(item->clone());
    }
    GData::actionProfiles.append(newProfile);
    ui->lstProfiles->addItem(newName);
    ui->lstProfiles->setCurrentRow(GData::actionProfiles.count()-1);

}

/******************************************************************/

void ActionProfiles::on_btnProfilesRename_clicked()
{
    int idx = ui->lstProfiles->currentRow();
    GActionProfile profile = GData::actionProfiles.at(idx);
    bool ok;
    QString newName = QInputDialog::getText(this, tr("Rename action profile"), tr("Rename to"), QLineEdit::Normal, profile.name, &ok);
    if (!ok) return;
    for (int i=0; i < GData::actionProfiles.count(); i++) {
        if (i == idx) {
            continue;
        }
        if(GData::actionProfiles.at(i).name == newName) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        QMessageBox::warning(this, tr("Rename action profile"),
                             QString("Profile named '%1' already exists").arg(newName));
        return;
    }
    profile.name = newName;
    //GActionProfile::actionProfileList.replace(idx,profile);
    ui->lstProfiles->currentItem()->setText(newName);
    ui->lstProfiles->setCurrentRow(GData::actionProfiles.count()-1);
}

/******************************************************************/

void ActionProfiles::on_btnProfilesDelete_clicked()
{
    int idx = ui->lstProfiles->currentRow();
    GActionProfile profile = GData::actionProfiles.at(idx);
    int ret = QMessageBox::question(this,tr("Confirm"),
                  tr("The action profile you are deleting may be used in some test configurations.\nDelete anyway?"),
                  QMessageBox::Yes | QMessageBox::No,
                  QMessageBox::Yes);
    if (ret == QMessageBox::No) {
        return;
    }
    profile.clearActions();
    GData::actionProfiles.removeAt(idx);
    QListWidgetItem *item = ui->lstProfiles->takeItem(idx);
    delete item;
    if (idx >= GData::actionProfiles.count()) {
        idx = GData::actionProfiles.count() - 1;
    }
    ui->lstProfiles->setCurrentRow(idx);
}

/******************************************************************/

void ActionProfiles::on_btnProfilesSort_clicked()
{

}

/******************************************************************/

void ActionProfiles::on_btnBadAdd_clicked()
{
    int idx = ui->lstProfiles->currentRow();
    if (idx > GData::actionProfiles.count()) {
        return;
    }
    GActionProfile profile = GData::actionProfiles.at(idx);

    ActionProfilesAddMenu mnuDlg;
    if(mnuDlg.exec() == QDialog::Accepted) {
        int result = mnuDlg.getResult();
        ActionPropertiesDialog prDlg;
        prDlg.setAddFlag(true);
        prDlg.setIndex(result);
        if (prDlg.exec() == QDialog::Accepted) {
            TestAction *newAction = prDlg.getResult();
            if (!newAction) return;
            profile.onBad.append(newAction);
            GData::actionProfiles.replace(idx,profile);
            m_badModel->setActionList(profile.onBad);
        }
    }
}

/******************************************************************/

void ActionProfiles::on_btnBadEdit_clicked()
{
    int idx = ui->lstProfiles->currentRow();
    if (idx > GData::actionProfiles.count()) {
        return;
    }
    GActionProfile profile = GData::actionProfiles.at(idx);
    QModelIndex index = ui->trvBad->currentIndex();
    if (!index.isValid() || index.row() >= profile.onBad.count()) {
        return;
    }
    TestAction* action = profile.onBad.at(index.row());
    ActionPropertiesDialog prDlg;
    prDlg.setAddFlag(true);
    prDlg.init(action);
    if (prDlg.exec() == QDialog::Accepted) {
        TestAction *newAction = prDlg.getResult();
        if (action != newAction) {
            profile.onBad.replace(index.row(),newAction);
            delete action;
        }
    }

}

/******************************************************************/

void ActionProfiles::on_btnBadDel_clicked()
{
    int idx = ui->lstProfiles->currentRow();
    if (idx > GData::actionProfiles.count()) {
        return;
    }
    GActionProfile profile = GData::actionProfiles.at(idx);
    QModelIndex index = ui->trvBad->currentIndex();
    if (!index.isValid() || index.row() >= profile.onBad.count()) {
        return;
    }
    profile.onBad.removeAt(index.row());
    GData::actionProfiles.replace(idx,profile);
    m_badModel->setActionList(profile.onBad);
}

/******************************************************************/

void ActionProfiles::on_btnGoodAdd_clicked()
{
    int idx = ui->lstProfiles->currentRow();
    if (idx > GData::actionProfiles.count()) {
        return;
    }
    GActionProfile profile = GData::actionProfiles.at(idx);

    ActionProfilesAddMenu mnuDlg;
    if(mnuDlg.exec() == QDialog::Accepted) {
        int result = mnuDlg.getResult();
        ActionPropertiesDialog prDlg;
        prDlg.setAddFlag(false);
        prDlg.setIndex(result);
        if (prDlg.exec() == QDialog::Accepted) {
            TestAction *newAction = prDlg.getResult();
            if (!newAction) return;
            profile.onGood.append(newAction);
            GData::actionProfiles.replace(idx,profile);
            m_goodModel->setActionList(profile.onGood);
        }
    }
}

/******************************************************************/

void ActionProfiles::on_btnGoodEdit_clicked()
{
    int idx = ui->lstProfiles->currentRow();
    if (idx > GData::actionProfiles.count()) {
        return;
    }
    GActionProfile profile = GData::actionProfiles.at(idx);
    QModelIndex index = ui->trvGood->currentIndex();
    if (!index.isValid() || index.row() >= profile.onGood.count()) {
        return;
    }
    TestAction* action = profile.onGood.at(index.row());
    ActionPropertiesDialog prDlg;
    prDlg.setAddFlag(false);
    prDlg.init(action);
    if (prDlg.exec() == QDialog::Accepted) {
        TestAction *newAction = prDlg.getResult();
        if (action != newAction) {
            profile.onGood.replace(index.row(),newAction);
            delete action;
        }
    }
}

/******************************************************************/

void ActionProfiles::on_btnGoodDel_clicked()
{
    int idx = ui->lstProfiles->currentRow();
    if (idx > GData::actionProfiles.count()) {
        return;
    }
    GActionProfile profile = GData::actionProfiles.at(idx);
    QModelIndex index = ui->trvGood->currentIndex();
    if (!index.isValid() || index.row() >= profile.onGood.count()) {
        return;
    }
    profile.onGood.removeAt(index.row());
    GData::actionProfiles.replace(idx,profile);
    m_goodModel->setActionList(profile.onGood);
}

/******************************************************************/

void ActionProfiles::on_btnCommentAdd_clicked()
{
    bool ok;
    QString profileName = ui->lstProfiles->currentItem()->text();
    QString text = QInputDialog::getMultiLineText(this,
                   QString("Add your comments for '%1' profile").arg(profileName),
                   QString("Comments for '%1' profile").arg(profileName),
                   ui->txtComment->toPlainText(), &ok);
    if (ok) {
        ui->txtComment->setPlainText(text);
    }
}

/******************************************************************/

void ActionProfiles::on_btnFindReplace_clicked()
{

}

/******************************************************************/

void ActionProfiles::on_btnUsageReport_clicked()
{

}

/******************************************************************/

void ActionProfiles::init(int row)
{
    ui->lstProfiles->clear();
    foreach (const GActionProfile &profile, GData::actionProfiles) {
        ui->lstProfiles->addItem(profile.name);
    }
    connect(ui->lstProfiles, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(currentChanged()));
    ui->lstProfiles->setCurrentRow(row);
}

/******************************************************************/

int ActionProfiles::getSelected() const
{
    return ui->lstProfiles->currentRow();
}

/******************************************************************/
// ActionsTreeModel class
/******************************************************************/

ActionsTreeModel::ActionsTreeModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_header << tr("Action") << tr("Start after") << tr("Repeat");
}

/******************************************************************/

int ActionsTreeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

/******************************************************************/

int ActionsTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_header.count();
}

/******************************************************************/

QVariant ActionsTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= m_data.count()) {
        return QVariant();
    }
    if (role == Qt::DisplayRole) {
        TestAction *action = m_data.at(index.row());
        switch(index.column()) {
        case 0: // Action
            return action->getName();
        case 1: // Start after
            if (action->getMode() == TActionMode::Standard) {
                return action->getStartAfter();
            } else if (action->getMode() == TActionMode::Advanced) {
                return "expr";
            }
            return "sched";
        case 2: // Repeat
            if (action->getMode() == TActionMode::Standard) {
                return action->getRetries();
            } else if (action->getMode() == TActionMode::Advanced) {
                return "expr";
            }
            return "sched";
        }
    }
    return QVariant();
}

/******************************************************************/

QVariant ActionsTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_header.at(section);
    }
    return QVariant();
}

/******************************************************************/

void ActionsTreeModel::setActionList(QList<TestAction *> &actions)
{
    beginResetModel();
    m_data = actions;
    endResetModel();
}

/******************************************************************/

} // namespace SDPO




