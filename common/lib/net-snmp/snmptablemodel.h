#ifndef SNMPTABLEMODEL_H
#define SNMPTABLEMODEL_H

#include "snmp.h"

#include <QAbstractTableModel>

namespace SDPO {

class SnmpTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit SnmpTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    void addRow(const SnmpValueList& row, const QModelIndex &parent = QModelIndex());
    void setHeaders(const QList<MibNode>& headers);
    void setValues(const SnmpValueTable& values);
    void clear();

private:
    QList<MibNode> m_Headers;
    SnmpValueTable m_Values;
};

} // namespace SDPO

#endif // SNMPTABLEMODEL_H
