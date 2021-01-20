#include "snmptablemodel.h"

using namespace SDPO;

/*****************************************************************/

SnmpTableModel::SnmpTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

/*****************************************************************/

QVariant SnmpTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return m_Headers.at(section).label();
    }

    return QVariant();
}

/*****************************************************************/

int SnmpTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_Values.size();
}

/*****************************************************************/

int SnmpTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_Headers.size();
}

/*****************************************************************/

QVariant SnmpTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        SnmpValueList row = m_Values.at(index.row());
        return row.at(index.column()).val;
    }

    return QVariant();
}

/*****************************************************************/

void SnmpTableModel::addRow(const SnmpValueList &row, const QModelIndex &parent)
{
    beginInsertRows(parent, m_Values.size(), m_Values.size());
    SnmpValueList newRow(row);
    m_Values.append(newRow);
    endInsertRows();
}

/*****************************************************************/

void SnmpTableModel::setHeaders(const QList<MibNode> &headers)
{
    beginResetModel();
    m_Headers.clear();
    m_Headers.append(headers);
    endResetModel();
}

/*****************************************************************/

void SnmpTableModel::setValues(const SnmpValueTable &values)
{
    beginResetModel();
    m_Values.clear();
    endResetModel();
    foreach(const SnmpValueList& row, values) {
        addRow(row);
    }
}

/*****************************************************************/

void SnmpTableModel::clear()
{
    beginResetModel();
    m_Headers.clear();
    m_Values.clear();
    endResetModel();
}

/*****************************************************************/
