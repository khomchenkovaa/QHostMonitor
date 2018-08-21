#ifndef QCOLUMNSPROPERTIESWIDGET_H
#define QCOLUMNSPROPERTIESWIDGET_H

#include <QWidget>
#include "global/gProfiles.h"

namespace Ui {
class ColumnsPropertiesWidget;
}

QT_BEGIN_NAMESPACE
class QListWidgetItem;
QT_END_NAMESPACE

namespace SDPO {

class TNode;

class ColumnsPropertiesWidget : public QWidget
{
    Q_OBJECT

    Ui::ColumnsPropertiesWidget *ui;
    QColumnList m_columns;
    QSortPairList m_sort;

public:
    explicit ColumnsPropertiesWidget(QWidget *parent = 0);
    ~ColumnsPropertiesWidget();

    void init(TNode *node = 0);
    void save(TNode *node);
    void reset();

private slots:
    void on_btnLeft_clicked();
    void on_btnRight_clicked();
    void on_btnUp_clicked();
    void on_btnDown_clicked();
    void on_btnCheckAll_clicked();
    void on_btnUncheckAll_clicked();
    void on_btnAscending_toggled(bool checked);
    void on_btnDescending_toggled(bool checked);
    void on_listVisibleColumns_itemSelectionChanged();
    void on_listSortBy_itemSelectionChanged();
    void on_rbUseOwnColumnSettings_toggled(bool checked);

    void on_listSortBy_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
};

} // namespace SDPO

#endif // QCOLUMNSPROPERTIESWIDGET_H
