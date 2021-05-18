#ifndef SNMPMODULEMODEL_H
#define SNMPMODULEMODEL_H

#include "snmpobject.h"

#include <QAbstractItemModel>

namespace KharmonView {

class SnmpModuleModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SnmpModuleModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setObject(SnmpObject* snmpObject);

private:
    SnmpObject* m_Object;
    QStringList m_Header;

};

} // namespace KharmonView

#endif // SNMPMODULEMODEL_H
