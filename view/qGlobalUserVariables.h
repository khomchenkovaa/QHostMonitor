#ifndef QGLOBALUSERVARIABLES_H
#define QGLOBALUSERVARIABLES_H

#include <QDialog>
#include <QAbstractTableModel>

namespace Ui {
class GlobalUserVariables;
}

namespace SDPO {

class GlobalUserVariables : public QDialog
{
    Q_OBJECT

public:
    explicit GlobalUserVariables(QWidget *parent = 0);
    ~GlobalUserVariables();

private:
    Ui::GlobalUserVariables *ui;
};


class GlobalUserVarsTableModel : public QAbstractTableModel
{
    Q_OBJECT

    QStringList m_header;

public:
    explicit GlobalUserVarsTableModel(QWidget *parent = 0);


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

} // namespace SDPO

#endif // QGLOBALUSERVARIABLES_H
