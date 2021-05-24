#include "snmpmodulemodel.h"

#include <QIcon>

using namespace KharmonView;

/*****************************************************************/

SnmpModuleModel::SnmpModuleModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_Object(Q_NULLPTR)
{
    m_Header
        << "Name"
        << "Desc"
        << "Type"
        << "Status"
        << "Status Desc"
        << "Last Change Date"
        << "URI"
        << "Index"
        ;
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

    if (m_Object->getModIdx()) {
        return 1;
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

    if (role != Qt::DisplayRole && role != Qt::DecorationRole) {
        return QVariant();
    }

    int row = index.row();

    if (m_Object->getModIdx()) {
        for (int i=0; i< m_Object->snmpModList()->size(); ++i) {
            if (m_Object->snmpModList()->at(i).modIndex == m_Object->getModIdx()) {
                row = i;
                break;
            }
        }
    }

    SnmpModule module = m_Object->snmpModList()->at(row);

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: return module.modName; break;
        case 1: return module.modDesc; break;
        case 2: return module.modType; break;
        case 3: return module.modStatus; break;
        case 4: return module.modStatusDesc; break;
        case 5: return module.modLastChangeDate; break;
        case 6: return module.modURI; break;
        case 7: return QString::number(module.modIndex); break;
        }
    }

    if (role == Qt::DecorationRole && index.column() == 0) {
        switch (module.modStatus) {
        case 0: // normal
            return QIcon(":img/status/tstHostAlive.png");
        case 1: // lowWarning
        case 2: // highWarning
            return QIcon(":img/status/tstWaitForMaster.png");
        case 3: // initial
            return QIcon(":img/status/tstChecking.png");
        case 10: // lowFail
        case 11: // highFail
        case 12: // fail
            return QIcon(":img/status/tstNoAnswer.png");
        case 101: // unknown
            return QIcon(":img/status/tstUnknown.png");
        }
    }

    return QVariant();
}

/*****************************************************************/

SnmpObject *SnmpModuleModel::getObject()
{
    return m_Object;
}

/*****************************************************************/

void SnmpModuleModel::setObject(SnmpObject *snmpObject)
{
    beginResetModel();
    m_Object = snmpObject;
    endResetModel();
}

/*****************************************************************/
