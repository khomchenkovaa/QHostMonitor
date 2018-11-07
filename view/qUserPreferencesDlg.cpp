#include "qUserPreferencesDlg.h"
#include "ui_qUserPreferencesDlg.h"
#include "qPalettesWin.h"
#include "qUserPreferencesCopyDlg.h"
#include "io/ioUserProfileLoader.h"
#include <QInputDialog>

namespace SDPO {

/******************************************************************/

UserPreferencesDlg::UserPreferencesDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPreferencesDlg)
{
    ui->setupUi(this);
    m_PalettesModel = new PalettesTreeModel(this);
    ui->trvColors->setModel(m_PalettesModel);
    initColors();
    init();
}

/******************************************************************/

UserPreferencesDlg::~UserPreferencesDlg()
{
    delete ui;
    delete m_PalettesModel;
}

/******************************************************************/

void UserPreferencesDlg::on_listUserProfiles_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (previous) {
        save(ui->listUserProfiles->row(previous));
    }
    if (current) {
        load(ui->listUserProfiles->row(current));
        on_trwMonitorColors_currentItemChanged(ui->trwMonitorColors->currentItem(), 0);
    }
}

/******************************************************************/

void UserPreferencesDlg::on_btnColorScheme_clicked()
{
    PalettesWin dlg;
    dlg.init(ui->editColorScheme->text());
    if (dlg.exec() == QDialog::Accepted) {
        ui->editColorScheme->setText(dlg.getSelected());
    }
}

/******************************************************************/

void UserPreferencesDlg::on_editColorScheme_textChanged(const QString &colorScheme)
{
    if (colorScheme.isEmpty()) return;
    GColorProfile profile = GData::getColorProfile(colorScheme);
    m_PalettesModel->setProfile(profile);
    QString style = QString("color: %1; background-color: %2; font: 8pt \"DejaVu Sans\";").arg(profile.htmlText.at(0).name(),profile.htmlText.at(1).name());
    ui->trvColors->setStyleSheet(style);
}

/******************************************************************/

void UserPreferencesDlg::on_btnCopy_clicked()
{
    int idx = ui->listUserProfiles->currentRow();
    if (idx == -1) return;

    UserPreferencesCopyDlg dlg;
    // set items from m_userProfiles
    QStringList profiles;
    for (int i=0; i< m_userProfiles.count(); i++) {
        profiles.append(m_userProfiles.at(i).name);
    }
    dlg.setItems(profiles, idx);
    if (dlg.exec() == QDialog::Accepted) {
        QList<int> ids = dlg.getSelectedIds();
        if (ids.isEmpty()) return;
        save(idx);
        GUserProfile current = m_userProfiles.at(idx);
        // for each checked id
        foreach(int id, ids) {
            GUserProfile profile = m_userProfiles.at(id);
            QString id = profile.id;
            QString name = profile.name;
            QString password = profile.password;
            bool enabled = profile.enabled;
            QString email = profile.email;
            QString pager = profile.pager;
            QString icq = profile.icq;
            GUserProfile newProfile = current.clone();
            newProfile.id = id;
            newProfile.name = name;
            newProfile.password = password;
            newProfile.enabled = enabled;
            newProfile.email = email;
            newProfile.pager = pager;
            newProfile.icq = icq;
            m_userProfiles.replace(idx,newProfile);
        }
    }
}

/******************************************************************/

void UserPreferencesDlg::on_trwMonitorColors_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous)
    if (!current)  return;
    foreach(QAbstractButton *btn, ui->btnGroupColors->buttons()) {
        btn->setText(QString());
        btn->setHidden(current->childCount());
    }
    if (current->childCount()) return;
    GUserProfile profile = m_userProfiles.at(ui->listUserProfiles->currentRow());
    QTreeWidgetItem *parent = current->parent();
    GIPMonitor monitor;
    if (parent->text(0).contains("TCP")) {
        monitor = profile.tcpMonitor;
    } else if (parent->text(0).contains("UDP")) {
        monitor = profile.udpMonitor;
    } else if (parent->text(0).contains("ICMP")) {
        monitor = profile.icmpMonitor;
    }
    int idx=-1;
    switch(parent->indexOfChild(current)) {
    case 0: idx = m_Colors.indexOf(monitor.backgroundColor); break;
    case 1: idx = m_Colors.indexOf(monitor.gridColor); break;
    case 2: idx = m_Colors.indexOf(monitor.inPacketsColor); break;
    case 3: idx = m_Colors.indexOf(monitor.outPacketsColor); break;
    case 4: idx = m_Colors.indexOf(monitor.errorColor); break;
    }
    if (idx != -1) {
        QAbstractButton *btn = ui->btnGroupColors->button(idx);
        btn->setText("FG");
        btn->setChecked(true);
    }
    connect(ui->btnGroupColors,SIGNAL(buttonClicked(int)),this,SLOT(onMonitorColorChanged(int)));

}

/******************************************************************/

void UserPreferencesDlg::on_btnLeft_clicked()
{
    if (ui->listSortColumns->selectedItems().count()) {
        int idx = ui->listSortColumns->currentRow();
        QListWidgetItem *item = ui->listSortColumns->takeItem(idx);
        if (!item) return;
        if (!ui->listSortColumns->count()) return;
        if (idx >= ui->listSortColumns->count()) {
            idx = ui->listSortColumns->count() - 1;
        }
        ui->listSortColumns->setCurrentRow(idx);
    }
}

/******************************************************************/

void UserPreferencesDlg::on_btnRight_clicked()
{
    if (ui->listVisibleColumns->selectedItems().count()) {
        QListWidgetItem *columnItem = ui->listVisibleColumns->currentItem();
        if (!columnItem) return;
        for(int i=0; i < ui->listSortColumns->count(); i++) {
            if (ui->listSortColumns->item(i)->text() == columnItem->text()) {
                return;
            }
        }
        QListWidgetItem *item = new QListWidgetItem(columnItem->text());
        item->setData(Qt::UserRole, true);
        ui->listSortColumns->addItem(item);
    }
}

/******************************************************************/

void UserPreferencesDlg::on_btnUp_clicked()
{
    if (ui->listVisibleColumns->selectedItems().count()) {
        int idx = ui->listVisibleColumns->currentRow();
        if (!idx) return;
        QListWidgetItem *item = ui->listVisibleColumns->takeItem(idx);
        if (!item) return;
        ui->listVisibleColumns->insertItem(idx-1, item);
        ui->listVisibleColumns->setCurrentItem(item);
    } else if (ui->listSortColumns->selectedItems().count()) {
        int idx = ui->listSortColumns->currentRow();
        if (!idx) return;
        QListWidgetItem *item = ui->listSortColumns->takeItem(idx);
        if (!item) return;
        ui->listSortColumns->insertItem(idx-1, item);
        ui->listSortColumns->setCurrentItem(item);
    }
}

/******************************************************************/

void UserPreferencesDlg::on_btnDown_clicked()
{
    if (ui->listVisibleColumns->selectedItems().count()) {
        int idx = ui->listVisibleColumns->currentRow();
        if (idx >= ui->listVisibleColumns->count() - 1) return;
        QListWidgetItem *item = ui->listVisibleColumns->takeItem(idx);
        if (!item) return;
        ui->listVisibleColumns->insertItem(idx+1, item);
        ui->listVisibleColumns->setCurrentItem(item);
    } else if (ui->listSortColumns->selectedItems().count()) {
        int idx = ui->listSortColumns->currentRow();
        if (idx >= ui->listSortColumns->count() - 1) return;
        QListWidgetItem *item = ui->listSortColumns->takeItem(idx);
        if (!item) return;
        ui->listSortColumns->insertItem(idx+1, item);
        ui->listSortColumns->setCurrentItem(item);
    }
}

/******************************************************************/

void UserPreferencesDlg::on_btnRename_clicked()
{
    if (ui->listVisibleColumns->selectedItems().count()) {
        QListWidgetItem *columnItem = ui->listVisibleColumns->currentItem();
        if (!columnItem) return;
        QString title = columnItem->text();
        bool ok;
        QString name = QInputDialog::getText(this, tr("Rename column"),tr("Column name"), QLineEdit::Normal, title, &ok);
        if (!ok) return;
        if (name == title) return;
        for(int i=0; i < ui->listSortColumns->count(); i++) {
            if (ui->listSortColumns->item(i)->text() == title) {
                ui->listSortColumns->item(i)->setText(name);
            }
        }
        columnItem->setText(name);
    }
}

/******************************************************************/

void UserPreferencesDlg::on_btnCheckAll_clicked()
{
    for(int i=0; i < ui->listVisibleColumns->count(); i++) {
        ui->listVisibleColumns->item(i)->setCheckState(Qt::Checked);
    }
}

/******************************************************************/

void UserPreferencesDlg::on_btnUncheckAll_clicked()
{
    for(int i=0; i < ui->listVisibleColumns->count(); i++) {
        ui->listVisibleColumns->item(i)->setCheckState(Qt::Unchecked);
    }
}

/******************************************************************/

void UserPreferencesDlg::on_btnSortAscending_toggled(bool checked)
{
    if (checked && ui->listSortColumns->currentItem()) {
        ui->listSortColumns->currentItem()->setData(Qt::UserRole, true);
    }
}

/******************************************************************/

void UserPreferencesDlg::on_btnSortDescending_toggled(bool checked)
{
    if (checked && ui->listSortColumns->currentItem()) {
        ui->listSortColumns->currentItem()->setData(Qt::UserRole, false);
    }
}

/******************************************************************/

void UserPreferencesDlg::on_listVisibleColumns_itemSelectionChanged()
{
    if (ui->listVisibleColumns->selectedItems().count()) {
        ui->listSortColumns->clearSelection();
        if (ui->listVisibleColumns->currentItem()) {
            ui->btnUp->setEnabled(ui->listVisibleColumns->currentRow());
            ui->btnDown->setEnabled(ui->listVisibleColumns->currentRow()+1 < ui->listVisibleColumns->count());
            ui->btnLeft->setEnabled(false);
            ui->btnRight->setEnabled(true);
            ui->btnRename->setEnabled(true);
        }
    }
}

/******************************************************************/

void UserPreferencesDlg::on_listSortColumns_itemSelectionChanged()
{
    if (ui->listSortColumns->selectedItems().count()) {
        ui->listVisibleColumns->clearSelection();
        ui->btnRename->setEnabled(false);
        if (ui->listSortColumns->currentItem()) {
            ui->btnUp->setEnabled(ui->listSortColumns->currentRow());
            ui->btnDown->setEnabled(ui->listSortColumns->currentRow()+1 < ui->listSortColumns->count());
            ui->btnLeft->setEnabled(true);
            ui->btnRight->setEnabled(false);
        }
    }
}

/******************************************************************/

void UserPreferencesDlg::on_listSortColumns_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous)
    if (current) {
        if (current->data(Qt::UserRole).toBool()) {
            ui->btnSortAscending->setChecked(true);
        } else {
            ui->btnSortDescending->setChecked(true);
        }
    }
}

/******************************************************************/

void UserPreferencesDlg::onMonitorColorChanged(int id)
{
    if (!(ui->btnGroupColors->button(id)->isChecked())) return;
    // get profile
    int idx = ui->listUserProfiles->currentRow();
    if (idx == -1) return;
    GUserProfile profile = m_userProfiles.at(idx);
    // get current
    QTreeWidgetItem *current = ui->trwMonitorColors->currentItem();
    if (!current)  return;
    if (current->childCount()) return;
    // change buttons
    foreach(QAbstractButton *btn, ui->btnGroupColors->buttons()) {
        btn->setText(QString());
    }
    ui->btnGroupColors->button(id)->setText("FG");
    // change value
    QTreeWidgetItem *parent = current->parent();
    QColor color = m_Colors.at(id);
    if (parent->text(0).contains("TCP")) {
        switch(parent->indexOfChild(current)) {
        case 0: profile.tcpMonitor.backgroundColor.setNamedColor(color.name()); break;
        case 1: profile.tcpMonitor.gridColor = color; break;
        case 2: profile.tcpMonitor.inPacketsColor = color; break;
        case 3: profile.tcpMonitor.outPacketsColor = color; break;
        case 4: profile.tcpMonitor.errorColor = color; break;
        }
    } else if (parent->text(0).contains("UDP")) {
        switch(parent->indexOfChild(current)) {
        case 0: profile.udpMonitor.backgroundColor = color; break;
        case 1: profile.udpMonitor.gridColor = color; break;
        case 2: profile.udpMonitor.inPacketsColor = color; break;
        case 3: profile.udpMonitor.outPacketsColor = color; break;
        case 4: profile.udpMonitor.errorColor = color; break;
        }
    } else if (parent->text(0).contains("ICMP")) {
        switch(parent->indexOfChild(current)) {
        case 0: profile.icmpMonitor.backgroundColor = color; break;
        case 1: profile.icmpMonitor.gridColor = color; break;
        case 2: profile.icmpMonitor.inPacketsColor = color; break;
        case 3: profile.icmpMonitor.outPacketsColor = color; break;
        case 4: profile.icmpMonitor.errorColor = color; break;
        }
    }
    m_userProfiles.replace(idx,profile);
}

/******************************************************************/

void UserPreferencesDlg::initColors()
{
    m_Colors << QColor("#000000") << QColor("#941613") << QColor("#005e00") << QColor("#868601");
    m_Colors << QColor("#060384") << QColor("#661c6c") << QColor("#297671") << QColor("#bfbfbf");
    m_Colors << QColor("#808080") << QColor("#fe0000") << QColor("#00fe00") << QColor("#fefe00");
    m_Colors << QColor("#0000d1") << QColor("#fe00fe") << QColor("#00fefe") << QColor("#fefefe");
    ui->btnGroupColors->setId(ui->btnColor11,0);
    ui->btnGroupColors->setId(ui->btnColor12,1);
    ui->btnGroupColors->setId(ui->btnColor13,2);
    ui->btnGroupColors->setId(ui->btnColor14,3);
    ui->btnGroupColors->setId(ui->btnColor15,4);
    ui->btnGroupColors->setId(ui->btnColor16,5);
    ui->btnGroupColors->setId(ui->btnColor17,6);
    ui->btnGroupColors->setId(ui->btnColor18,7);
    ui->btnGroupColors->setId(ui->btnColor21,8);
    ui->btnGroupColors->setId(ui->btnColor22,9);
    ui->btnGroupColors->setId(ui->btnColor23,10);
    ui->btnGroupColors->setId(ui->btnColor24,11);
    ui->btnGroupColors->setId(ui->btnColor25,12);
    ui->btnGroupColors->setId(ui->btnColor26,13);
    ui->btnGroupColors->setId(ui->btnColor27,14);
    ui->btnGroupColors->setId(ui->btnColor28,15);
    foreach(QAbstractButton *btn, ui->btnGroupColors->buttons()) {
        btn->setText(QString());
        btn->setHidden(true);
    }
    connect(ui->btnGroupColors,SIGNAL(buttonClicked(int)),this,SLOT(onMonitorColorChanged(int)));
}

/******************************************************************/

void UserPreferencesDlg::init()
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

void UserPreferencesDlg::load(const int idx)
{
    GUserProfile profile = m_userProfiles.at(idx);
    // Palette/Details
    switch(profile.style) {
    case TestListStyle::Report:
        ui->rbStyleReport->setChecked(true);
        break;
    case TestListStyle::List:
        ui->rbStyleList->setChecked(true);
        break;
    case TestListStyle::Icon:
        ui->rbStyleIcon->setChecked(true);
        break;
    case TestListStyle::SmallIcon:
        ui->rbStyleSmallIcon->setChecked(true);
        break;
    }
    ui->chkShowGridLines->setChecked(profile.showGridLines);
    ui->chkGridForLog->setChecked(profile.gridForLogViewer);
    ui->chkShowTestsIn->setChecked(profile.showTestsInSubfolders);
    ui->editColorScheme->setText(profile.colorScheme);
    // IP Monitor
    ui->dspinRefreshTime->setValue(profile.ipmRefreshTime);
    ui->chkShowPacketCounters->setChecked(profile.ipmShowPacketsCounter);
    ui->spinTcpMonitorVertical->setValue(profile.tcpMonitor.vLinesNumber);
    ui->spinTcpMonitorHorizontal->setValue(profile.tcpMonitor.hLinesNumber);
    ui->spinUdpMonitorVertical->setValue(profile.udpMonitor.vLinesNumber);
    ui->spinUdpMonitorHorizontal->setValue(profile.udpMonitor.hLinesNumber);
    ui->spinIcmpMonitorVertical->setValue(profile.icmpMonitor.vLinesNumber);
    ui->spinIcmpMonitorHorizontal->setValue(profile.icmpMonitor.hLinesNumber);
    // Columns
    ui->listVisibleColumns->clear();
    for(int i=0; i < profile.columns.count(); i++) {
        QListWidgetItem *item = new QListWidgetItem(profile.columns.at(i).title);
        item->setCheckState( profile.columns.at(i).checked ? Qt::Checked : Qt::Unchecked );
        item->setData(Qt::UserRole, profile.columns.at(i).macro);
        ui->listVisibleColumns->addItem(item);
    }
    ui->listSortColumns->clear();
    for(int i=0; i < profile.sort.count(); i++) {
        QListWidgetItem *item = new QListWidgetItem(profile.sort.at(i).first);
        item->setData(Qt::UserRole, profile.sort.at(i).second);
        ui->listSortColumns->addItem(item);
    }
}

/******************************************************************/

void UserPreferencesDlg::save(const int idx)
{
    GUserProfile profile = m_userProfiles.at(idx);
    // Palette/Details
    if (ui->rbStyleReport->isChecked()) {
        profile.style = TestListStyle::Report;
    } else if (ui->rbStyleList->isChecked()) {
        profile.style = TestListStyle::List;
    } else if (ui->rbStyleIcon->isChecked()) {
        profile.style = TestListStyle::Icon;
    } else if (ui->rbStyleSmallIcon->isChecked()) {
        profile.style = TestListStyle::SmallIcon;
    }
    profile.showGridLines = ui->chkShowGridLines->isChecked();
    profile.gridForLogViewer = ui->chkGridForLog->isChecked();
    profile.showTestsInSubfolders = ui->chkShowTestsIn->isChecked();
    profile.colorScheme = ui->editColorScheme->text();
    // IP Monitor
    profile.ipmRefreshTime = ui->dspinRefreshTime->value();
    profile.ipmShowPacketsCounter = ui->chkShowPacketCounters->isChecked();
    profile.tcpMonitor.vLinesNumber = ui->spinTcpMonitorVertical->value();
    profile.tcpMonitor.hLinesNumber = ui->spinTcpMonitorHorizontal->value();
    profile.udpMonitor.vLinesNumber = ui->spinUdpMonitorVertical->value();
    profile.udpMonitor.hLinesNumber = ui->spinUdpMonitorHorizontal->value();
    profile.icmpMonitor.vLinesNumber = ui->spinIcmpMonitorVertical->value();
    profile.icmpMonitor.hLinesNumber = ui->spinIcmpMonitorHorizontal->value();
    // Columns
    profile.columns.clear();
    for(int i=0; i < ui->listVisibleColumns->count(); i++) {
        QListWidgetItem *item = ui->listVisibleColumns->item(i);
        TLColumn column;
        column.title = item->text();
        column.checked = (item->checkState() == Qt::Checked);
        column.macro = item->data(Qt::UserRole).toString();
        profile.columns.append(column);
    }
    profile.sort.clear();
    for(int i=0; i < ui->listSortColumns->count(); i++) {
        QListWidgetItem *item = ui->listSortColumns->item(i);
        QSortPair pair;
        pair.first = item->text();
        pair.second = item->data(Qt::UserRole).toBool();
        profile.sort.append(pair);
    }
    m_userProfiles.replace(idx, profile);
}

/******************************************************************/

void UserPreferencesDlg::on_buttonBox_accepted()
{
    int idx = ui->listUserProfiles->currentRow();
    if (idx != -1) {
        save(idx);
        for (int i=0; i< m_userProfiles.count(); i++) {
            GUserProfile profile = m_userProfiles.at(i);
            GData::userProfiles.replace(i, profile);
        }
        IOUserProfileLoader loader;
        loader.save();
    }
}

/******************************************************************/

} // namespace SDPO

