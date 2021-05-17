#ifndef SNMPOBJECTMODEL_H
#define SNMPOBJECTMODEL_H

#include "snmpobject.h"
#include <QAbstractItemModel>

namespace KharmonView {

class SnmpObjectModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SnmpObjectModel(QObject *parent = nullptr);

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void beginResetModel() {
        QAbstractItemModel::beginResetModel();
    }

    void endResetModel() {
        QAbstractItemModel::endResetModel();
    }

    SnmpObject* nodeFromIndex(const QModelIndex& index) const;

};

} // namespace KharmonView

#endif // SNMPOBJECTMODEL_H
