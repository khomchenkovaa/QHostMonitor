#include "mibtreemodel.h"

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

    SnmpMibTree *parentNode = nodeFromIndex(parent);

    SnmpMibTree *child = parentNode? parentNode->child_list : m_Root;
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
    SnmpMibTree *node = nodeFromIndex(index);

    if(!node)
        return QModelIndex();

    SnmpMibTree *parentNode = node->parent;

    if(!parentNode)
        return QModelIndex();

    SnmpMibTree *grandParentNode = parentNode->parent;

    int row = 0;
    SnmpMibTree *child = grandParentNode ? grandParentNode->child_list : m_Root;
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
    SnmpMibTree *parentNode = nodeFromIndex(parent);

    if(!parentNode)
        return 1;

    int cnt = 0;
    for(SnmpMibTree *child = parentNode->child_list; child; child = child->next_peer) {
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
    if(role != Qt::DisplayRole)
        return QVariant();

    SnmpMibTree *node = nodeFromIndex(index);

    if(!node)
        return QVariant();

    if(index.column() == 0) {
        return QString("%1 (%2)").arg(node->label).arg(node->subid);
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

void MibTreeModel::setRoot(SnmpMibTree *root)
{
    beginResetModel();
    m_Root = root;
    endResetModel();
}

/*****************************************************************/

SnmpMibTree *MibTreeModel::nodeFromIndex(const QModelIndex &index) const
{
    return index.isValid() ? static_cast<SnmpMibTree *> (index.internalPointer()) : nullptr;
}

/*****************************************************************/

QModelIndex MibTreeModel::indexFromOid(QString oid) const
{
    QStringList ids = oid.split(".",QString::SkipEmptyParts);
    if (ids.isEmpty()) {
        return index(0,0);
    }
    ids.removeFirst();
    SnmpMibTree *tp = m_Root;
    foreach(QString id, ids) {
        u_long subId = id.toULong();
        SnmpMibTree *child = tp->child_list;
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

QModelIndex MibTreeModel::indexFromNode(SnmpMibTree *node) const
{
    if (node == m_Root) {
        return index(0, 0);
    } else {
        QModelIndex parentIndex = indexFromNode(node->parent);
        int row = 0;
        SnmpMibTree *child = node->parent ? node->parent->child_list : m_Root;
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
    SnmpMibTree *node = static_cast<SnmpMibTree *>(parent.internalPointer());
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
    SnmpMibTree *leftNode = static_cast<SnmpMibTree *>(left.internalPointer());
    SnmpMibTree *rightNode = static_cast<SnmpMibTree *>(right.internalPointer());

    return leftNode->subid < rightNode->subid;
}

/*****************************************************************/
