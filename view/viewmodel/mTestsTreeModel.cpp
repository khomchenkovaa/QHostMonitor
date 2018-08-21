#include "mTestsTreeModel.h"

namespace SDPO {

/******************************************************************/

TestsTreeModel::TestsTreeModel(TNode *root, QObject *parent) :
    QAbstractItemModel(parent),
    m_root(root)
{
}

/******************************************************************/

QVariant TestsTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TNode *item = static_cast<TNode*>(index.internalPointer());

    return item->getName();
}

/******************************************************************/

Qt::ItemFlags TestsTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

/******************************************************************/

QModelIndex TestsTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TNode *parentItem;

    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<TNode*>(parent.internalPointer());

    TNode *childItem = parentItem->child(row, true);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

/******************************************************************/

QModelIndex TestsTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TNode *childItem = static_cast<TNode*>(index.internalPointer());
    TNode *parentItem = childItem->parentNode();

    if (parentItem == m_root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

/******************************************************************/

int TestsTreeModel::rowCount(const QModelIndex &parent) const
{
    TNode *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<TNode*>(parent.internalPointer());

    return parentItem->childCount(true);
}

/******************************************************************/

int TestsTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

/******************************************************************/
} // namespace SDPO
