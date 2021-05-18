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

    SnmpObject* curObj = nodeFromIndex(index);

    switch (role) {
    case Qt::DisplayRole:
        return curObj->getName();
    case Qt::DecorationRole:
        return QIcon(":/img/folder.png");
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
