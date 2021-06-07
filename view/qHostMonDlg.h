#ifndef HOSTMONDLGS_H
#define HOSTMONDLGS_H

#include "tEnums.h"
#include "testmethod.h"

#include <QDialog>
#include <QVariant>

namespace Ui {
    class HostMonDlg;
}

namespace SDPO {

class TNode;
class TTest;
class TestMethod;
class HMListService;

class HostMonDlg : public QDialog
{
    Q_OBJECT

    Ui::HostMonDlg *ui;
    HMListService  *m_HML;
    TTest          *m_Item;
    QVariant        m_Data;
    bool            changed;

public:
    explicit HostMonDlg(HMListService *hml, QWidget *parent = 0);
    ~HostMonDlg();

signals:
    void testAdded(TTest *test);
    void testChanged(TTest *test);

public slots:
    void init(TTest *item = 0);
    void init(TMethodID method, QVariant data = QVariant());

private slots:
    void reset();
    void refreshName();
    void refreshComment();
    void openMethodSelectDialog();
    void hideDependencies(bool hide);
    void hideOptional(bool hide);
    void on_btnOk_clicked();
    void on_btnLinks_clicked();
    void on_btnSchedulesDlg_clicked();
    void on_btnScheduleRegular_clicked();
    void on_btnScheduleIrregular_clicked();
    void on_btnScheduleByExpression_clicked();
    void on_cmbSchedIrregularMode_currentIndexChanged(int index);
    void on_btnWarningCondition_clicked();
    void on_btnNormalCondition_clicked();
    void on_btnTuneUpReply_clicked();

private:
    void setupUI();
    void saveTest(TestMethod *testMethod);
    QString getTestName() const;
    QString getTestComment() const;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);

};

} // namespace SDPO

#endif // HOSTMONDLGS_H
