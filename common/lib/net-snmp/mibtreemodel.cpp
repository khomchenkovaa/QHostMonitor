#include "mibtreemodel.h"

#include <QIcon>
#include <QDebug>

using namespace SDPO;

/*****************************************************************/

MibTreeModel::MibTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

/*****************************************************************/

QModelIndex MibTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    if(!m_Root.isValid()) { // model is not initialized
        return QModelIndex();
    }

    if(column != 0) { // one column only
        return QModelIndex();
    }

    MibNode parentNode = nodeFromIndex(parent);
    if (!parentNode.isValid()) { // root
        if (row != 0) { // one root only
            return QModelIndex();
        }
        return createIndex(0, 0, m_Root.node);
    }

    if(row < 0 || row >= parentNode.childCount()) { // illegal row
        return QModelIndex();
    }

    MibNode child = parentNode.childAt(row);

    return createIndex(row, column, child.node);
}

/*****************************************************************/

QModelIndex MibTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    MibNode node = nodeFromIndex(index);
    MibNode parentNode = node.parent();

    if(!parentNode.isValid())
        return QModelIndex();

    int row = parentNode.indexOf();

    return createIndex(row, 0, parentNode.node);
}

/*****************************************************************/

int MibTreeModel::rowCount(const QModelIndex &parent) const
{
    MibNode parentNode = nodeFromIndex(parent);

    if(!parentNode.isValid())
        return 1;

    return parentNode.childCount();
}

/*****************************************************************/

int MibTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

/*****************************************************************/

QVariant MibTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.column() != 0) {
        return QVariant();
    }

    MibNode node = nodeFromIndex(index);
    if(!node.isValid()) {
        return QVariant();
    }

    switch (role) {
    case Qt::DisplayRole:
        return node.labelAndId();
    case Qt::DecorationRole:
        if (node.isTable()) {
            return QIcon(":/img/test/snmp_table.png");
        }
        if (node.hasChildren()) {
            return QIcon(":/img/folder.png");
        }
        if (node.type() == MibTypeNotif || node.type() == MibTypeTrap) {
            return QIcon(":/img/test/snmp_trap.png");
        }
        if (node.access() == MibAccessReadWrite) {
            return QIcon(":/img/action/enableTest.png");
        }
        if (node.access() == MibAccessNoAccess) {
            return QIcon(":/img/action/key.png");
        }
        return QIcon(":/img/test/snmp_get.png");
    }

    return QVariant();
}

/*****************************************************************/

QVariant MibTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole && section == 0)
        return tr("Object");

    return QVariant();
}

/*****************************************************************/

void MibTreeModel::setRoot(const MibNode& root)
{
    beginResetModel();
    m_Root = root;
    endResetModel();
}

/*****************************************************************/

MibNode MibTreeModel::nodeFromIndex(const QModelIndex &index) const
{
    return index.isValid() ? index.internalPointer() : nullptr;
}

/*****************************************************************/

QModelIndex MibTreeModel::indexFromOid(const QString &oid) const
{
    MibOid mibOid = MibOid::parse(oid);
    if (mibOid.hasError())
        return QModelIndex();
    MibNode node = MibNode::findByOid(mibOid);
    if (!node.isValid())
        return QModelIndex();
    return indexFromNode(node);
}

/*****************************************************************/

QModelIndex MibTreeModel::indexFromNode(const MibNode& node) const
{
    if (node == m_Root) {
        return index(0, 0);
    } else {
        QModelIndex parentIndex = indexFromNode(node.parent());
        int row = node.indexOf();
        return index(row,0,parentIndex);
    }
}

/*****************************************************************/

MibTreeProxyModel::MibTreeProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

/*****************************************************************/

bool MibTreeProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    MibNode leftNode = left.internalPointer();
    MibNode rightNode = right.internalPointer();

    return leftNode.subID() < rightNode.subID();
}

/*****************************************************************/
