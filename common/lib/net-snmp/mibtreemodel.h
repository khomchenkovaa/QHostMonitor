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
    ~MibTreeModel() Q_DECL_OVERRIDE;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setRoot(MibTree *root);
    MibTree *nodeFromIndex(const QModelIndex& index) const;

    QModelIndex indexFromOid(QString oid) const;
    QModelIndex indexFromNode(MibTree *node) const;
    QModelIndex findByName(const QString& name, const QModelIndex& parent) const;

private:
    MibTree *m_Root;
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
