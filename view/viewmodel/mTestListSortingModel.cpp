#include "mTestListSortingModel.h"
#include "mTestListModel.h"
#include "tNode.h"

namespace SDPO {

/******************************************************************/

TestListSortingModel::TestListSortingModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

/******************************************************************/

bool TestListSortingModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    TestListModel *model = qobject_cast<TestListModel*>(sourceModel());

    TNode *leftNode = model->itemFromIndex(source_left);
    TNode *rightNode = model->itemFromIndex(source_right);

    if (leftNode->getType() == TNode::VIEW) {
        return sortOrder() == Qt::AscendingOrder;
    }

    if (leftNode->getPath() != rightNode->getPath()) {
        if (sortOrder() == Qt::AscendingOrder) {
            return (leftNode->getPath() < rightNode->getPath());
        } else {
            return (rightNode->getPath() < leftNode->getPath());
        }
    }

    if (leftNode->getType() == TNode::FOLDER) {
        return sortOrder() == Qt::AscendingOrder;
    }

    QVariant leftData = model->data(source_left, Qt::DisplayRole);
    QVariant rightData = model->data(source_right, Qt::DisplayRole);

    return (leftData < rightData);
}

/******************************************************************/

} // namespace SDPO
