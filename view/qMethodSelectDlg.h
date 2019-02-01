#ifndef QMETHODSELECTDLG_H
#define QMETHODSELECTDLG_H

#include <QDialog>
#include <QStandardItem>
#include "global/tMethod.h"

namespace Ui {
class MethodSelectDlg;
}

namespace SDPO {

class MethodSelectDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MethodSelectDlg(QWidget *parent = 0);
    ~MethodSelectDlg();

    void setCurrent(const int methodId);
    int getCurrent() const;

private slots:
    void onTreeTestMethodsChanged();

private:
    Ui::MethodSelectDlg *ui;

    void createStandardItemModel();
    QStandardItem *createItem(const TMethodID methodId);
    QStandardItem *createGroupItem(const int groupId);
};

} // namespace SDPO

#endif // QMETHODSELECTDLG_H
