#include "mibtreemodel.h"

#include <QIcon>
#include <QDebug>

using namespace SDPO;

/*****************************************************************/

MibTreeModel::MibTreeModel(QObject *parent)
    : QAbstractItemModel(parent),
      m_Root(nullptr)
{
}

/*****************************************************************/

MibTreeModel::~MibTreeModel()
{
    m_Root = nullptr;
}

/*****************************************************************/

QModelIndex MibTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!m_Root)
        return QModelIndex();

    MibTree *parentNode = nodeFromIndex(parent);

    MibTree *child = parentNode? parentNode->child_list : m_Root;
    for(int cnt = 0; cnt != row; ++cnt ) {
        child = child->next_peer;
        if (!child) {
            break;
        }
    }

    return createIndex(row, column, child);
}

/*****************************************************************/

QModelIndex MibTreeModel::parent(const QModelIndex &index) const
{
    MibTree *node = nodeFromIndex(index);

    if(!node)
        return QModelIndex();

    MibTree *parentNode = node->parent;

    if(!parentNode)
        return QModelIndex();

    MibTree *grandParentNode = parentNode->parent;

    int row = 0;
    MibTree *child = grandParentNode ? grandParentNode->child_list : m_Root;
    for(; child != parentNode; child = child->next_peer) {
        if (!child) {
            break;
        }
        ++row;
    }

    return createIndex(row, index.column(), parentNode);

}

/*****************************************************************/

int MibTreeModel::rowCount(const QModelIndex &parent) const
{
    MibTree *parentNode = nodeFromIndex(parent);

    if(!parentNode)
        return 1;

    int cnt = 0;
    for(MibTree *child = parentNode->child_list; child; child = child->next_peer) {
        cnt++;
    }

    return cnt;
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

    MibTree *node = nodeFromIndex(index);
    if(!node) {
        return QVariant();
    }

    switch (role) {
    case Qt::DisplayRole:
        return QString("%1 (%2)").arg(node->label).arg(node->subid);
    case Qt::DecorationRole:
        if (node->child_list) {
            if (node->child_list->indexes) {
                return QIcon(":/img/test/snmp_table.png");
            }
            return QIcon(":/img/folder.png");
        }
        if (node->type == MibTypeNotif || node->type == MibTypeTrap) {
            return QIcon(":/img/test/snmp_trap.png");
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

void MibTreeModel::setRoot(MibTree *root)
{
    beginResetModel();
    m_Root = root;
    endResetModel();
}

/*****************************************************************/

MibTree *MibTreeModel::nodeFromIndex(const QModelIndex &index) const
{
    return index.isValid() ? static_cast<MibTree *> (index.internalPointer()) : nullptr;
}

/*****************************************************************/

QModelIndex MibTreeModel::indexFromOid(QString oid) const
{
    QStringList ids = oid.split(".",QString::SkipEmptyParts);
    if (ids.isEmpty()) {
        return index(0,0);
    }
    ids.removeFirst();
    MibTree *tp = m_Root;
    foreach(QString id, ids) {
        u_long subId = id.toULong();
        MibTree *child = tp->child_list;
        for(; child; child = child->next_peer) {
            if (subId == child->subid) {
                break;
            }
        }
        if (!child) {
            break;
        }
        tp = child;
    }
    return indexFromNode(tp);
}

/*****************************************************************/

QModelIndex MibTreeModel::indexFromNode(MibTree *node) const
{
    if (node == m_Root) {
        return index(0, 0);
    } else {
        QModelIndex parentIndex = indexFromNode(node->parent);
        int row = 0;
        MibTree *child = node->parent ? node->parent->child_list : m_Root;
        for(; child != node; child = child->next_peer) {
            if (!child) {
                break;
            }
            ++row;
        }
        return index(row,0,parentIndex);
    }
}

/*****************************************************************/

QModelIndex MibTreeModel::findByName(const QString &name, const QModelIndex &parent) const
{
    int childCount = rowCount(parent);
    for (int i=0; i<childCount; i++) {
        QModelIndex idx = findByName(name, index(i,0,parent));
        if (idx.isValid()) {
            return idx;
        }
    }
    MibTree *node = static_cast<MibTree *>(parent.internalPointer());
    if (name.compare(node->label, Qt::CaseInsensitive) == 0) {
        return parent;
    }
    return QModelIndex();
}

/*****************************************************************/

MibTreeProxyModel::MibTreeProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

/*****************************************************************/

bool MibTreeProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    MibTree *leftNode = static_cast<MibTree *>(left.internalPointer());
    MibTree *rightNode = static_cast<MibTree *>(right.internalPointer());

    return leftNode->subid < rightNode->subid;
}

/*****************************************************************/
