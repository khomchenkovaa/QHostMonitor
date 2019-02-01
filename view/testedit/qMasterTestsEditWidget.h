#ifndef QMASTERTESTSEDITWIDGET_H
#define QMASTERTESTSEDITWIDGET_H

#include "tTest.h"
#include <QWidget>

namespace Ui {
class MasterTestsEditWidget;
}

namespace SDPO {

class MasterTestsEditWidget : public QWidget
{
    Q_OBJECT

    QList<TTestPair> m_masterTests;
    QStringList m_conditions;
    TNode *m_root;

public:
    explicit MasterTestsEditWidget(QWidget *parent = 0);
    ~MasterTestsEditWidget();

    void init(TTest *item = 0);
    void save(TTest *item);
    void reset(TNode *root);

private slots:
    void on_btnMasterTestUp_clicked();
    void on_btnMasterTestDown_clicked();
    void on_btnMasterTestAdd_clicked();
    void on_btnMasterTestDelete_clicked();
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void updateMasterTests();

private:
    Ui::MasterTestsEditWidget *ui;
};

} // namespace SDPO

#endif // QMASTERTESTSEDITWIDGET_H
