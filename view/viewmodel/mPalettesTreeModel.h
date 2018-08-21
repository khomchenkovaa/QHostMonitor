#ifndef MPALETTESTREEMODEL_H
#define MPALETTESTREEMODEL_H

#include <QAbstractTableModel>
#include "gData.h"

namespace SDPO {

class PalettesTreeModel : public QAbstractTableModel
{
    Q_OBJECT

    QList<QStringList> m_data;
    QStringList m_hint;
    GColorProfile m_profile;
public:
    PalettesTreeModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setProfile(const GColorProfile profile);
    QColor getColor(const int row, const int idx) const;
    GColorProfile setColor(const int row, const int idx, const QColor color);

private:
    void fillData();

};

} // namespace SDPO

#endif // MPALETTESTREEMODEL_H
