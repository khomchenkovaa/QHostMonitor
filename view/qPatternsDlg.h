#ifndef QPATTERNSDLG_H
#define QPATTERNSDLG_H

#include <QDialog>
#include <QAbstractTableModel>
#include "global/tMethod.h"

namespace Ui {
class PatternsDlg;
}

namespace SDPO {

class PatternsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PatternsDlg(QWidget *parent = 0);
    ~PatternsDlg();

private:
    Ui::PatternsDlg *ui;
};

class PatternsTableModel : public QAbstractTableModel
{
    Q_OBJECT

    QStringList m_header;

public:
    explicit PatternsTableModel(QWidget *parent = 0);


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

#endif // QPATTERNSDLG_H
