#include "qColumnsPropertiesWidget.h"
#include "ui_qColumnsPropertiesWidget.h"
#include "tFolder.h"
#include "tView.h"

namespace SDPO {

/******************************************************************/

ColumnsPropertiesWidget::ColumnsPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColumnsPropertiesWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

ColumnsPropertiesWidget::~ColumnsPropertiesWidget()
{
    delete ui;
}

/******************************************************************/

void ColumnsPropertiesWidget::init(TNode *node)
{
    if (!node) {
        reset();
        return;
    }
    if (node->getType() != TNode::FOLDER && node->getType() != TNode::VIEW) {
        reset();
        return;
    }


    if (node->getType() == TNode::FOLDER) {
        ui->rbUseOwnColumnSettings->setText(tr("Use folder's own column settings"));
    } else if (node->getType() == TNode::VIEW){
        ui->rbUseOwnColumnSettings->setText(tr("Use views's own column settings"));
    }

    if (node->isUseOwnColumnSettings()) {
        ui->rbUseOwnColumnSettings->setChecked(true);
    } else {
        ui->rbUseInheritable->setChecked(true);
    }

    if (node->isRootFolder()) {
        ui->rbUseInheritable->setText(tr("Apply user specific settings"));
    } else {
        ui->rbUseInheritable->setText(tr("Use inheritable settings from parent"));
    }
    m_columns.append(node->getColumns());
    ui->listVisibleColumns->clear();
    for(int i=0; i < m_columns.count(); i++) {
        QListWidgetItem *item = new QListWidgetItem(m_columns.at(i).title);
        item->setCheckState( m_columns.at(i).checked ? Qt::Checked : Qt::Unchecked );
        item->setData(Qt::UserRole, m_columns.at(i).macro);
        ui->listVisibleColumns->addItem(item);
    }
    m_sort.append(node->getSort());
    ui->listSortBy->clear();
    for(int i=0; i < m_sort.count(); i++) {
        QListWidgetItem *item = new QListWidgetItem(m_sort.at(i).first);
        item->setData(Qt::UserRole, m_sort.at(i).second);
        ui->listSortBy->addItem(item);
    }
}

/******************************************************************/

void ColumnsPropertiesWidget::save(TNode *node)
{
    if (!node) {
        return;
    }
    node->setUseOwnColumnSettings(ui->rbUseOwnColumnSettings->isChecked());
    m_columns.clear();
    for(int i=0; i < ui->listVisibleColumns->count(); i++) {
        QListWidgetItem *item = ui->listVisibleColumns->item(i);
        TLColumn column;
        column.title = item->text();
        column.checked = (item->checkState() == Qt::Checked);
        column.macro = item->data(Qt::UserRole).toString();
        m_columns.append(column);
    }
    node->setColumns(m_columns);
    m_sort.clear();
    for(int i=0; i < ui->listSortBy->count(); i++) {
        QListWidgetItem *item = ui->listSortBy->item(i);
        QSortPair pair;
        pair.first = item->text();
        pair.second = item->data(Qt::UserRole).toBool();
        m_sort.append(pair);
    }
    node->setSort(m_sort);
}

/******************************************************************/

void ColumnsPropertiesWidget::reset()
{
    ui->rbUseOwnColumnSettings->setChecked(false);
    m_columns.clear();
    m_sort.clear();
}

/******************************************************************/

void ColumnsPropertiesWidget::on_btnLeft_clicked()
{
    if (ui->listSortBy->selectedItems().count()) {
        int idx = ui->listSortBy->currentRow();
        QListWidgetItem *item = ui->listSortBy->takeItem(idx);
        if (!item) return;
        if (!ui->listSortBy->count()) return;
        if (idx >= ui->listSortBy->count()) {
            idx = ui->listSortBy->count() - 1;
        }
        ui->listSortBy->setCurrentRow(idx);
    }
}

/******************************************************************/

void ColumnsPropertiesWidget::on_btnRight_clicked()
{
    if (ui->listVisibleColumns->selectedItems().count()) {
        QListWidgetItem *columnItem = ui->listVisibleColumns->currentItem();
        if (!columnItem) return;
        for(int i=0; i < ui->listSortBy->count(); i++) {
            if (ui->listSortBy->item(i)->text() == columnItem->text()) {
                return;
            }
        }
        QListWidgetItem *item = new QListWidgetItem(columnItem->text());
        item->setData(Qt::UserRole, true);
        ui->listSortBy->addItem(item);
    }
}

/******************************************************************/

void ColumnsPropertiesWidget::on_btnUp_clicked()
{
    if (ui->listVisibleColumns->selectedItems().count()) {
        int idx = ui->listVisibleColumns->currentRow();
        if (!idx) return;
        QListWidgetItem *item = ui->listVisibleColumns->takeItem(idx);
        if (!item) return;
        ui->listVisibleColumns->insertItem(idx-1, item);
        ui->listVisibleColumns->setCurrentItem(item);
    } else if (ui->listSortBy->selectedItems().count()) {
        int idx = ui->listSortBy->currentRow();
        if (!idx) return;
        QListWidgetItem *item = ui->listSortBy->takeItem(idx);
        if (!item) return;
        ui->listSortBy->insertItem(idx-1, item);
        ui->listSortBy->setCurrentItem(item);
    }
}

/******************************************************************/

void ColumnsPropertiesWidget::on_btnDown_clicked()
{
    if (ui->listVisibleColumns->selectedItems().count()) {
        int idx = ui->listVisibleColumns->currentRow();
        if (idx >= ui->listVisibleColumns->count() - 1) return;
        QListWidgetItem *item = ui->listVisibleColumns->takeItem(idx);
        if (!item) return;
        ui->listVisibleColumns->insertItem(idx+1, item);
        ui->listVisibleColumns->setCurrentItem(item);
    } else if (ui->listSortBy->selectedItems().count()) {
        int idx = ui->listSortBy->currentRow();
        if (idx >= ui->listSortBy->count() - 1) return;
        QListWidgetItem *item = ui->listSortBy->takeItem(idx);
        if (!item) return;
        ui->listSortBy->insertItem(idx+1, item);
        ui->listSortBy->setCurrentItem(item);
    }
}

/******************************************************************/

void ColumnsPropertiesWidget::on_btnCheckAll_clicked()
{
    for(int i=0; i < ui->listVisibleColumns->count(); i++) {
        ui->listVisibleColumns->item(i)->setCheckState(Qt::Checked);
    }
}

/******************************************************************/

void ColumnsPropertiesWidget::on_btnUncheckAll_clicked()
{
    for(int i=0; i < ui->listVisibleColumns->count(); i++) {
        ui->listVisibleColumns->item(i)->setCheckState(Qt::Unchecked);
    }
}

/******************************************************************/

void ColumnsPropertiesWidget::on_btnAscending_toggled(bool checked)
{
    if (checked && ui->listSortBy->currentItem()) {
        ui->listSortBy->currentItem()->setData(Qt::UserRole, true);
    }
}

/******************************************************************/

void ColumnsPropertiesWidget::on_btnDescending_toggled(bool checked)
{
    if (checked && ui->listSortBy->currentItem()) {
        ui->listSortBy->currentItem()->setData(Qt::UserRole, false);
    }
}

/******************************************************************/

void ColumnsPropertiesWidget::on_listVisibleColumns_itemSelectionChanged()
{
    if (ui->listVisibleColumns->selectedItems().count()) {
        ui->listSortBy->clearSelection();
        if (ui->listVisibleColumns->currentItem()) {
            ui->btnUp->setEnabled(ui->listVisibleColumns->currentRow());
            ui->btnDown->setEnabled(ui->listVisibleColumns->currentRow()+1 < ui->listVisibleColumns->count());
            ui->btnLeft->setEnabled(false);
            ui->btnRight->setEnabled(true);
        }
    }
}

/******************************************************************/

void ColumnsPropertiesWidget::on_listSortBy_itemSelectionChanged()
{
    if (ui->listSortBy->selectedItems().count()) {
        ui->listVisibleColumns->clearSelection();
        if (ui->listSortBy->currentItem()) {
            ui->btnUp->setEnabled(ui->listSortBy->currentRow());
            ui->btnDown->setEnabled(ui->listSortBy->currentRow()+1 < ui->listSortBy->count());
            ui->btnLeft->setEnabled(true);
            ui->btnRight->setEnabled(false);
        }
    }
}

/******************************************************************/

void ColumnsPropertiesWidget::on_listSortBy_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous)
    if (current) {
        if (current->data(Qt::UserRole).toBool()) {
            ui->btnAscending->setChecked(true);
        } else {
            ui->btnDescending->setChecked(true);
        }
    }
}

/******************************************************************/

void ColumnsPropertiesWidget::on_rbUseOwnColumnSettings_toggled(bool checked)
{
    ui->listVisibleColumns->setEnabled(checked);
    ui->listSortBy->setEnabled(checked);
    ui->btnCheckAll->setEnabled(checked);
    ui->btnUncheckAll->setEnabled(checked);
    ui->btnAscending->setEnabled(checked);
    ui->btnDescending->setEnabled(checked);
    ui->btnLeft->setEnabled(checked);
    ui->btnRight->setEnabled(checked);
    ui->btnUp->setEnabled(checked);
    ui->btnDown->setEnabled(checked);
    if (checked) {
        ui->listVisibleColumns->setCurrentRow(0);
    } else {
        ui->listVisibleColumns->clearSelection();
        ui->listSortBy->clearSelection();
    }
}

/******************************************************************/

} // namespace SDPO

