#ifndef TESTMETHODSELECTDLG_H
#define TESTMETHODSELECTDLG_H

#include "testmethod.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QStandardItem;
class QTreeView;
class QTextEdit;
class QDialogButtonBox;
QT_END_NAMESPACE

namespace SDPO {

class TestMethodSelectDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TestMethodSelectDlg(QWidget *parent = nullptr);
    ~TestMethodSelectDlg() {};

    void setCurrent(const int methodId);
    int getCurrent() const;

private slots:
    void onTreeTestMethodsChanged();

private:
    void setupUI();
    void createStandardItemModel();
    QStandardItem *createItem(const TMethodID methodId);
    QStandardItem *createGroupItem(const int groupId);

private: //UI
    QTreeView        *uiTestMethods;
    QTextEdit        *uiTestDescription;
    QDialogButtonBox *uiButtonBox;
};

} // namespace SDPO

#endif // TESTMETHODSELECTDLG_H
