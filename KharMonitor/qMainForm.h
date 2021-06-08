#ifndef QMAINFORM_H
#define QMAINFORM_H

#include "testmethod.h"

#include <QMainWindow>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
class QModelIndex;
class QFileDialog;
class QItemSelection;
QT_END_NAMESPACE

namespace Ui {
    class MainForm;
}

namespace SDPO {

class TTest;
class MonitoringService;
class FoldersAndViewsModel;
class TestListModel;
class TestListSortingModel;
class HMListService;
class ActionService;
class TNode;
class HostMonDlg;
class OptionsForm;

class MainForm : public QMainWindow
{
    Q_OBJECT

    Ui::MainForm      *ui;
    HMListService     *m_HML;
    ActionService     *m_ActionService;
    MonitoringService *m_MonitoringService;
    HostMonDlg        *hostMonDlg;

    TestListSortingModel *m_filterModel;
    TestListModel        *m_model;
    FoldersAndViewsModel *m_folders;
    FoldersAndViewsModel *m_views;
    QMenu *mnuTestAddShellScript;
public:
    explicit MainForm(HMListService *hml, ActionService *act, MonitoringService *monitoring, QWidget *parent = 0);
    ~MainForm();

    void setupFolders();
    void init();

public slots:
    void resetModel();
    void resetScriptMenu();
    //void onNewFolder(QString path, QString name);
    //void onNewView (QString name);
    void onTestAdded(TTest* test);
    void onTestChanged(TTest* test);
    void onTreeFolderChanged();
    void onTreeViewChanged();
    void onActionWinPopup(TTest *test);
    void onMonitoringStarted(bool value);
    void onAlertsEnabled(bool value);

    void changeEvent(QEvent*event);

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void onTestListContextMenu(const QPoint &pos);
    void onTestListSelectionChanged();
    void onViewPanelsChanged();
    // File menu
    void on_actNewTestList_triggered();
    void on_actLoadTestList_triggered();
    void on_actAppendFromHML_triggered();
    void on_actImportFromTxtFile_triggered();
    void on_actExportToTxtFile_triggered();
    void on_actExecuteScript_triggered();
    void on_actSave_triggered();
    void on_actSaveAs_triggered();
    void on_actProperties_triggered();
    // Monitoring menu
    void on_actPause_triggered();
    // Test menu (new)
    void onTestActionTriggered();
    void on_actScriptManager_triggered();
    void onShellScript();
    // Test menu (other)
    void on_actTestEdit_triggered();
    void on_actTestCopy_triggered();
    void on_actLink_triggered();
    void on_actLinkInfo_triggered();
    void on_actTestRemove_triggered();
    void on_actTestRemoveWithLinks_triggered();
    void on_actTestPause_triggered();
    void on_actPlannedPause_triggered();
    void on_actRefreshSelectedTests_triggered();
    void on_actResetSelectedTests_triggered();
    void on_actAcknowledge_triggered();
    void on_actTestInfo_triggered();
    void on_actHistoryCharts_triggered();
    // View menu
    // Profiles menu
    void on_actPatterns_triggered();
    void on_actConnectionManager_triggered();
    void on_actProfilesScriptManager_triggered();
    void on_actSnmpCredentials_triggered();
    void on_actColorSchemes_triggered();
    void on_actMailProfiles_triggered();
    void on_actReportProfiles_triggered();
    void on_actGlobalMacroVars_triggered();
    void on_actActionsProfiles_triggered();
    // User menu
    void on_actGuiPreferences_triggered();
    void on_actOperators_triggered();
    void on_actLoginAs_triggered();
    // Options menu
    void on_actOptions_triggered();
    // Tools menu
    void on_actToolsLocalInfo_triggered();
    // Help menu
    void on_actAbout_triggered();
    // Folder panel
    void on_tabFoldersTree_currentChanged(int index);
    void on_btnNewFolder_clicked();
    void on_btnNewSubfolder_clicked();
    void on_btnFolderProperties_clicked();
    void on_btnDelFolder_clicked();
    // Views panel
    void on_btnViewAdd_clicked();
    void on_btnViewProperties_clicked();
    void on_btnViewDel_clicked();
    // Test list panel
    void on_btnFoldersLineTree_clicked();
    void on_btnToolbarAdd_clicked();
    void on_btnToolbarEdit_clicked();
    void on_btnToolbarDel_clicked();
    void on_btnToolbarRefresh_clicked();
    void on_btnToolbarReset_clicked();
    void on_trvTestList_doubleClicked(const QModelIndex &index);

private:
    void setupUI();
    void setupTrayIcon();
    void setupTestActions();
    QAction* createTestAction(TMethodID methodID);

private:
    TNode *getItemFromFolderPath(QString path);
    TNode *getItemFromViewsPath(QString path);
    void activateActions(const bool actionEnabled);
};

} // namespace SDPO

#endif // QMAINFORM_H
