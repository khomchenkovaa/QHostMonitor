#ifndef HOSTMONDLGS_H
#define HOSTMONDLGS_H

#include "testmethod.h"

#include <QDialog>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QComboBox;
class QPlainTextEdit;
QT_END_NAMESPACE

namespace SDPO {

class TNode;
class TTest;
class HMListService;
class TestEditWidget;
class TestScheduleWidget;
class AlertsEditWidget;
class LogReportsEditWidget;
class MasterEditWidget;
class DependenciesEditWidget;
class OptionalProcessingWidget;

class HostMonDlg : public QDialog
{
    Q_OBJECT

    HMListService *m_HML;
    TTest         *m_Item;
    bool           changed;

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
    void onPrevClicked();
    void onNextClicked();
    void onLinksClicked();
    void onOkClicked();
    void onAddClicked();
    void onHelpClicked();

private:
    void setupUI();
    bool saveTest();

private: // UI
    TestEditWidget           *uiTestEdit;
    TestScheduleWidget       *uiSchedule;
    AlertsEditWidget         *uiAlerts;
    LogReportsEditWidget     *uiLogsReports;
    MasterEditWidget         *uiMaster;
    DependenciesEditWidget   *uiDependencies;
    OptionalProcessingWidget *uiOptional;
    QComboBox                *cmbEnabled;
    QPlainTextEdit           *textWarnMemo;
    QPushButton              *btnLinks;
};

} // namespace SDPO

#endif // HOSTMONDLGS_H
