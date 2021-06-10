#ifndef TESTMETHODSELECTDLG_H
#define TESTMETHODSELECTDLG_H

#include <QDialog>
#include <QStandardItem>
#include "testmethod.h"

namespace Ui {
class TestMethodSelectDlg;
}

namespace SDPO {

class TestMethodSelectDlg : public QDialog
{
    Q_OBJECT

    Ui::TestMethodSelectDlg *ui;

public:
    explicit TestMethodSelectDlg(QWidget *parent = nullptr);
    ~TestMethodSelectDlg();

    void setCurrent(const int methodId);
    int getCurrent() const;

private slots:
    void onTreeTestMethodsChanged();

private:
    void setupUI();
    void createStandardItemModel();
    QStandardItem *createItem(const TMethodID methodId);
    QStandardItem *createGroupItem(const int groupId);
};

} // namespace SDPO

#endif // TESTMETHODSELECTDLG_H
