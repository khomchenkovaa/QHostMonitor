#include "qGlobalUserVariables.h"
#include "ui_qGlobalUserVariables.h"
#include "global/gUserVars.h"

namespace SDPO {

/*****************************************************************/

GlobalUserVariables::GlobalUserVariables(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlobalUserVariables)
{
    ui->setupUi(this);
    ui->tableVariables->setModel(new GlobalUserVarsTableModel(this));
    ui->tableVariables->resizeColumnsToContents();
}

/*****************************************************************/

GlobalUserVariables::~GlobalUserVariables()
{
    delete ui;
}

/*****************************************************************/

GlobalUserVarsTableModel::GlobalUserVarsTableModel(QWidget *parent) :
    QAbstractTableModel(parent)
{
    m_header << "Variable" << "Value";
}

/*****************************************************************/

int GlobalUserVarsTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return GUserVars::variables.count();
}

/*****************************************************************/

int GlobalUserVarsTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

/*****************************************************************/

QVariant GlobalUserVarsTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= GUserVars::variables.count()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        QList<QString> keys = GUserVars::variables.keys();
        switch(index.column()) {
        case 0: return keys.at(index.row());
        case 1: return GUserVars::variables.value(keys.at(index.row()));
        }
    }
    return QVariant();
}

/*****************************************************************/

bool GlobalUserVarsTableModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (idx.isValid() && role == Qt::EditRole) {
        QList<QString> keys = GUserVars::variables.keys();
        switch (idx.column()) {
        case 0:
            GUserVars::replace(keys.at(idx.row()), value.toString());
            emit dataChanged(index(0,0), index(idx.row(),1));
            break;
        case 1:
            GUserVars::add(keys.at(idx.row()), value.toString());
            emit dataChanged(idx, idx);
            break;
        }
        return true;
    }
    return false;
}

/*****************************************************************/

QVariant GlobalUserVarsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_header.at(section);
    }
    return QVariant();
}

/*****************************************************************/

Qt::ItemFlags GlobalUserVarsTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

/*****************************************************************/


} // namespace SDPO
