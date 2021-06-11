#ifndef HOSTMONDLGS_H
#define HOSTMONDLGS_H

#include "testmethod.h"

#include <QDialog>
#include <QVariant>

namespace Ui {
    class HostMonDlg;
}

namespace SDPO {

class TNode;
class TTest;
class HMListService;

class HostMonDlg : public QDialog
{
    Q_OBJECT

    Ui::HostMonDlg *ui;
    HMListService  *m_HML;
    TTest          *m_Item;
    bool            changed;

public:
    explicit HostMonDlg(HMListService *hml, QWidget *parent = 0);
    ~HostMonDlg();

signals:
    void testAdded(TTest *test);
    void testChanged(TTest *test);

public slots:
    void init(TTest *item = nullptr);
    void init(TMethodID method, QVariant data = QVariant());

private slots:
    void reset();
    void hideDependencies(bool hide);
    void hideOptional(bool hide);
    void on_btnOk_clicked();
    void on_btnLinks_clicked();
    void on_btnWarningCondition_clicked();
    void on_btnNormalCondition_clicked();
    void on_btnTuneUpReply_clicked();

private:
    void setupUI();
    bool saveTest();
};

} // namespace SDPO

#endif // HOSTMONDLGS_H
