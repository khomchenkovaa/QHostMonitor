#include "snmpobjectmodel.h"

#include <QIcon>

using namespace KharmonView;

/*****************************************************************/

SnmpObjectModel::SnmpObjectModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

/*****************************************************************/

QModelIndex SnmpObjectModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    if (SnmpObject::root == nullptr) {
        return QModelIndex();
    }

    if(column != 0) { // one column only
        return QModelIndex();
    }

    SnmpObject* parentObj = nodeFromIndex(parent);

    return createIndex(row, 0, parentObj->childAt(row));
}

/*****************************************************************/

QModelIndex SnmpObjectModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    SnmpObject* curObj = nodeFromIndex(index);
    SnmpObject* parentObj = qobject_cast<SnmpObject*>(curObj->parent());
    if (parentObj == nullptr || parentObj == SnmpObject::root) {
        return QModelIndex();
    }
    SnmpObject* superObj = qobject_cast<SnmpObject*>(parentObj->parent());

    return createIndex(superObj->indexOf(parentObj), 0, parentObj);
}

/*****************************************************************/

int SnmpObjectModel::rowCount(const QModelIndex &parent) const
{
    SnmpObject* parentObj = nodeFromIndex(parent);

    return parentObj->childCount();
}

/*****************************************************************/

int SnmpObjectModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

/*****************************************************************/

QVariant SnmpObjectModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.column() != 0) {
        return QVariant();
    }

    SnmpObject* node = nodeFromIndex(index);

    int status = node->snmpStatus()->statStatus;
    if (node->getModIdx()) {
        for (int i=0; i< node->snmpModList()->size(); ++i) {
            if (node->snmpModList()->at(i).modIndex == node->getModIdx()) {
                status = node->snmpModList()->at(i).modStatus;
                break;
            }
        }
    }

    switch (role) {
    case Qt::DisplayRole:
        return node->getName();
    case Qt::DecorationRole:
        return iconByStatus(status);
    }

    return QVariant();
}

/*****************************************************************/

QVariant SnmpObjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    if (section) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    return SnmpObject::objectTitle();
}

/*****************************************************************/

SnmpObject *SnmpObjectModel::nodeFromIndex(const QModelIndex &index) const
{
     return index.isValid() ?
                  static_cast<SnmpObject*>(index.internalPointer()) :
                           SnmpObject::root;
}

/*****************************************************************/

void SnmpObjectModel::nodeAdd(const QModelIndex &parent, SnmpObject *node)
{
    SnmpObject *parNode = nodeFromIndex(parent);
    beginInsertRows(parent, parNode->childCount(), parNode->childCount());
    parNode->append(node);
    endInsertRows();
}

/*****************************************************************/

void SnmpObjectModel::nodeChanged(const QModelIndex &index)
{
    emit dataChanged(index, index);
}

/*****************************************************************/

void SnmpObjectModel::nodeRemove(const QModelIndex &index)
{
      SnmpObject *node = nodeFromIndex(index);
      beginRemoveRows(parent(index), index.row(), index.row());
      SnmpObject *parNode = node->parentObj();
      parNode->remove(node);
      endRemoveRows();
}

/*****************************************************************/

QIcon SnmpObjectModel::iconByStatus(int status) const
{
    switch (status) {
    case 0: // normal
        return QIcon("://img/fugue/media-player-medium-green.png");
    case 1: // lowWarning
    case 2: // highWarning
        return QIcon("://img/fugue/media-player-medium-yellow.png");
    case 3: // initial
        return QIcon("://img/fugue/media-player-medium.png");
    case 10: // lowFail
    case 11: // highFail
    case 12: // fail
        return QIcon("://img/fugue/media-player-medium-red.png");
    case 101: // unknown
        return QIcon("://img/fugue/media-player-medium-red.png");
    }
    return QIcon();
}

/*****************************************************************/
