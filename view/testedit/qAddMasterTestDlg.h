#ifndef QADDMASTERTESTDLG_H
#define QADDMASTERTESTDLG_H

#include <QDialog>
#include <QPair>

#include "tTest.h"

namespace Ui {
class AddMasterTestDlg;
}

namespace SDPO {

class AddMasterTestDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddMasterTestDlg(TNode *root, QWidget *parent = 0);
    ~AddMasterTestDlg();

    QPair<TTest*,int> getResult() const;

private slots:
    void onNodeSelected(const QModelIndex &current, const QModelIndex &previous);

private:
    Ui::AddMasterTestDlg *ui;
};

} // namespace SDPO

#endif // QADDMASTERTESTDLG_H
