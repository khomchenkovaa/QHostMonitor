#ifndef MFOLDERSANDVIEWSMODEL_H
#define MFOLDERSANDVIEWSMODEL_H

#include <QAbstractItemModel>
#include "tTest.h"

namespace SDPO {

class FoldersAndViewsModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum ModelMode { FOLDERS_AND_VIEWS, FOLDERS, VIEWS };

private:
    TNode *m_root;
    ModelMode m_mode;
public:
    explicit FoldersAndViewsModel(TNode *root, ModelMode mode, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    
    QModelIndex appendFolder(QString nodeName, const QModelIndex &parent = QModelIndex());
    QModelIndex appendView(QString nodeName);
    QModelIndex deleteFolder(const QModelIndex &folder);
    QModelIndex deleteView(const QModelIndex &view);

    TNode *itemFromIndex(const QModelIndex &index) const;
    TNode *invisibleRootItem() const;
    QModelIndex indexFromItem(TNode *item) const;
    QModelIndex indexFromPath(const QString& path) const;

};

} // namespace SDPO

#endif // MFOLDERSANDVIEWSMODEL_H
