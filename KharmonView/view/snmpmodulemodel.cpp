#include "snmpmodulemodel.h"

using namespace KharmonView;

/*****************************************************************/

SnmpModuleModel::SnmpModuleModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_Object(Q_NULLPTR)
{
    m_Header
        << "Index"
        << "Name"
        << "Desc"
        << "Type"
        << "Status"
        << "Status Desc"
        << "Last Change Date"
        << "URI";
}

/*****************************************************************/

QVariant SnmpModuleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    return m_Header.at(section);
}

/*****************************************************************/

QModelIndex SnmpModuleModel::index(int row, int column, const QModelIndex &parent) const
{
    if (m_Object == Q_NULLPTR) {
        return QModelIndex();
    }

    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    if (parent.isValid()) {
        return QModelIndex();
    }

    return createIndex(row, column);
}

/*****************************************************************/

QModelIndex SnmpModuleModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

/*****************************************************************/

int SnmpModuleModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    if (m_Object == Q_NULLPTR) {
        return 0;
    }

    return m_Object->snmpModList()->size();
}

/*****************************************************************/

int SnmpModuleModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_Header.count();
}

/*****************************************************************/

QVariant SnmpModuleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (m_Object == Q_NULLPTR) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    SnmpModule module = m_Object->snmpModList()->at(index.row());

    switch (index.column()) {
    case 0: return QString::number(module.modIndex); break;
    case 1: return module.modName; break;
    case 2: return module.modDesc; break;
    case 3: return module.modType; break;
    case 4: return module.modStatus; break;
    case 5: return module.modStatusDesc; break;
    case 6: return module.modLastChangeDate; break;
    case 7: return module.modURI; break;
    }

    // FIXME: Implement me!
    return QVariant();
}

/*****************************************************************/

void SnmpModuleModel::setObject(SnmpObject *snmpObject)
{
    beginResetModel();
    m_Object = snmpObject;
    endResetModel();
}

/*****************************************************************/
