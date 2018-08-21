#ifndef MTESTLISTSORTINGMODEL_H
#define MTESTLISTSORTINGMODEL_H

#include <QSortFilterProxyModel>

namespace SDPO {

class TestListSortingModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TestListSortingModel(QObject *parent = 0);

    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const Q_DECL_OVERRIDE;
signals:

public slots:

};

} // namespace SDPO

#endif // MTESTLISTSORTINGMODEL_H
