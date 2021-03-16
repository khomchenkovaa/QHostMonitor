#ifndef NMIBTREEMODEL_H
#define NMIBTREEMODEL_H

#include "snmp.h"

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

namespace SDPO {

class MibTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit MibTreeModel(QObject *parent = nullptr);

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setRoot(const MibNode &root);
    MibNode nodeFromIndex(const QModelIndex& index) const;

    QModelIndex indexFromOid(const QString& oid) const;
    QModelIndex indexFromNode(const MibNode& node) const;

private:
    MibNode m_Root;
};

class MibTreeProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    MibTreeProxyModel(QObject *parent = nullptr);
protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
};


} // namespace SDPO

#endif // NMIBTREEMODEL_H
