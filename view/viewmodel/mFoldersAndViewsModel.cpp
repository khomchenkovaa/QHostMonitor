#include "mFoldersAndViewsModel.h"
#include "tRoot.h"
#include "hmListService.h"

namespace SDPO {

/******************************************************************/

FoldersAndViewsModel::FoldersAndViewsModel(HMListService *hml, ModelMode mode, QObject *parent) :
    QAbstractItemModel(parent),
    m_HML(hml),
    m_root(m_HML->rootItem()),
    m_mode(mode)
{
}

/******************************************************************/

QVariant FoldersAndViewsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TNode *item = static_cast<TNode*>(index.internalPointer());

    return item->getName();
}

/******************************************************************/

Qt::ItemFlags FoldersAndViewsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

/******************************************************************/

QModelIndex FoldersAndViewsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TNode *parentItem;

    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<TNode*>(parent.internalPointer());

    TNode *childItem = 0;

    if (!(parentItem->parentNode()) && m_mode == VIEWS) {
        childItem = parentItem->lastChild();
    } else {
        childItem = parentItem->child(row, false);
    }

    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

/******************************************************************/

QModelIndex FoldersAndViewsModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TNode *childItem = static_cast<TNode*>(index.internalPointer());
    TNode *parentItem = childItem->parentNode();

    if (parentItem == m_root)
        return QModelIndex();

    return createIndex(parentItem->row(false), 0, parentItem);
}

/******************************************************************/

int FoldersAndViewsModel::rowCount(const QModelIndex &parent) const
{
    int cnt=0;
    if (!parent.isValid()) {
        if (m_root->parentNode() || m_mode == FOLDERS_AND_VIEWS ) {
            cnt = m_root->childCount(false);
        } else {
            cnt = 1;
        }
    } else {
        TNode *parentItem = static_cast<TNode*>(parent.internalPointer());
        cnt = parentItem->childCount(false);
    }

    return cnt;
}

/******************************************************************/

int FoldersAndViewsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

/******************************************************************/

QModelIndex FoldersAndViewsModel::appendFolder(QString nodeName, const QModelIndex &parent)
{
    TNode *node = itemFromIndex(parent);
    QModelIndex result = parent;
    if (node) {
        int row = rowCount(parent);
        beginInsertRows(parent, row, row);
        node->appendChild(new TFolder(m_HML->nextID(), nodeName, node));
        endInsertRows();
        result = index(row,0,parent);
    }
    return result;
}

/******************************************************************/

QModelIndex FoldersAndViewsModel::appendView(QString nodeName)
{
    TNode *node = m_HML->rootView();
    QModelIndex idx = index(0,0);
    if (node) {
        int row = rowCount(idx);
        beginInsertRows(idx, row, row);
        TView *newView = new TView(m_HML->nextID(), nodeName, qobject_cast<TFolder*>(m_HML->rootFolder()), node);
        node->appendChild(newView);
        endInsertRows();       
        idx = index(row,0,idx);
    }
    return idx;
}

/******************************************************************/

QModelIndex FoldersAndViewsModel::deleteFolder(const QModelIndex &folder)
{
    if (!folder.isValid()) {
        return folder;
    }
    // delete all childs
    TNode *node = itemFromIndex(folder);
    while (node->childCount(false)) {
        QModelIndex idx = indexFromItem(node->lastChild());
        deleteFolder(idx);
    }
    // delete all related views
    //! TODO m_nodesModel->removeViews(node);
    // delete current
    QModelIndex parent = folder.parent();
    QModelIndex result;
    int row = node->row(false);
    beginRemoveRows(parent, row, row);
    m_HML->rootItem()->removeNode(node);
    endRemoveRows();
    // constructing new index
    TNode *parentNode = itemFromIndex(parent);
    if (row) {
        result = index(row-1,0,parent);
    } else if (parentNode->childCount(false)) {
        result = index(0,0,parent);
    } else {
        result = parent;
    }
    return result;
}

/******************************************************************/

QModelIndex FoldersAndViewsModel::deleteView(const QModelIndex &view)
{
    if (!view.isValid()) {
        return view;
    }
    // delete current
    TNode *node = itemFromIndex(view);
    QModelIndex parent = view.parent();
    QModelIndex result;
    int row = node->row(false);
    beginRemoveRows(parent, row, row);
    m_HML->rootItem()->removeNode(node);
    endRemoveRows();
    // constructing new index
    TNode *parentNode = itemFromIndex(parent);
    if (row) {
        result = index(row-1,0,parent);
    } else if (parentNode->childCount(false)) {
        result = index(0,0,parent);
    } else {
        result = parent;
    }
    return result;

}

/******************************************************************/

TNode *FoldersAndViewsModel::itemFromIndex(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    TNode *item = static_cast<TNode*>(index.internalPointer());
    return item;
}

/******************************************************************/

TNode *FoldersAndViewsModel::invisibleRootItem() const
{
    return m_root;
}

/******************************************************************/

QModelIndex FoldersAndViewsModel::indexFromItem(TNode *item) const
{
    if (!item) {
        return QModelIndex();
    }
    int row = item->row(false);
    if (item == m_root || item->parentNode()->getType() == TNode::ROOT) {
        return index(row,0);
    }
    return index(row,0,indexFromItem(item->parentNode()));
}

/******************************************************************/

QModelIndex FoldersAndViewsModel::indexFromPath(const QString &path) const
{
    QModelIndex idx;
    QStringList pathList = path.split(PATH_DELIMITER);
    foreach(QString str, pathList) {
        if (str.isEmpty()) continue;
        if (!hasIndex(0,0,idx)) {
            break;
        }
        QModelIndex next = index(0,0,idx);
        QModelIndexList mods = match(next,Qt::DisplayRole,str);
        if (mods.isEmpty()) {
            break;
        }
        idx = mods.at(0);
    }
    return idx;
}

/******************************************************************/

} // namespace SDPO
