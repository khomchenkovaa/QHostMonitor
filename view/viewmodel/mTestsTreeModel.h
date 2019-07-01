#ifndef MTESTSTREEMODEL_H
#define MTESTSTREEMODEL_H

#include <QAbstractItemModel>
#include "tTest.h"

namespace SDPO {

class TestsTreeModel : public QAbstractItemModel {
    Q_OBJECT

    TNode *m_root;
public:
    explicit TestsTreeModel(TNode *root, QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // MTESTSTREEMODEL_H
