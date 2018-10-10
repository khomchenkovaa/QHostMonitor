#ifndef QMAINFORM_H
#define QMAINFORM_H

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
class TNode;
class HostMonDlg;
class OptionsForm;
class AboutDlg;

class MainForm : public QMainWindow
{
    Q_OBJECT

    Ui::MainForm *ui;
    HostMonDlg   *hostMonDlg;

    QMenu   *trayIconMenu;
    QAction *showAction;
    QAction *startStopAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;

    HMListService        *m_HML;
    TestListSortingModel *m_filterModel;
    TestListModel        *m_model;
    FoldersAndViewsModel *m_folders;
    FoldersAndViewsModel *m_views;
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

    void setupFolders(HMListService *hml);
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

    void changeEvent(QEvent*event);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayActionExecute();
    void setTrayIconActions();
    void showTrayIcon();

private slots:
    void onTestListContextMenu(const QPoint &pos);
    void onTestListSelectionChanged();
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
    void on_actExit_triggered();
    // Monitoring menu
    void on_actEnableAlerts_triggered();
    void on_actDisableAlerts_triggered();
    void on_actPause_triggered();
    // Test menu (new)
    void on_actTestPing_triggered();
    void on_actTestTrace_triggered();
    void on_actTestHTTP_triggered();
    void on_actTestURL_triggered();
    void on_actTestSMTP_triggered();
    void on_actTestPOP3_triggered();
    void on_actTestIMAP_triggered();
    void on_actMailRelay_triggered();
    void on_actTestTCP_triggered();
    void on_actTestUDP_triggered();
    void on_actTestRadius_triggered();
    void on_actTestDNS_triggered();
    void on_actTestDHCP_triggered();
    void on_actTestNTP_triggered();
    void on_actTestLDAP_triggered();
    void on_actTestDICOM_triggered();
    void on_actTestRAS_triggered();
    void on_actTestDriveFreeSpace_triggered();
    void on_actTestCompareFiles_triggered();
    void on_actTestNTEventsLog_triggered();
    void on_actTestService_triggered();
    void on_actTestProcess_triggered();
    void on_actTestCPUUsage_triggered();
    void on_actDominantProcess_triggered();
    void on_actPerformanceCounter_triggered();
    void on_actTestWMI_triggered();
    void on_actTestUNC_triggered();
    void on_actTestFolderFileSize_triggered();
    void on_actTestCountFiles_triggered();
    void on_actTestFolderFileAvailability_triggered();
    void on_actTestFileIntegrity_triggered();
    void on_actTestTextLog_triggered();
    void on_actInterbase_triggered();
    void on_actMSSQL_triggered();
    void on_actMySQL_triggered();
    void on_actOracle_triggered();
    void on_actPostgreSQL_triggered();
    void on_actSybase_triggered();
    void on_actTestODBCQuery_triggered();
    void on_actTestSNMPGet_triggered();
    void on_actSNMPTrap_triggered();
    void on_actTestTrafficMonitor_triggered();
    void on_actTestActiveScript_triggered();
    void on_actScriptManager_triggered();
    void onShellScript();
    void on_actTestExternal_triggered();
    void on_actTestSSH_triggered();
    void on_actTestITTemperatureMonitor_triggered();
    void on_actTestHMMonitor_triggered();
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
    void on_actFoldersTree_triggered(bool checked);
    void on_actFolderLine_triggered(bool checked);
    void on_actInfoPane_triggered(bool checked);
    void on_actQuickLog_triggered(bool checked);
    void on_actStatusBar_triggered(bool checked);
    // Profiles menu
    void on_actPatterns_triggered();
    void on_actConnectionManager_triggered();
    void on_actProfilesScriptManager_triggered();
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
    void on_btnToolbarAlert_clicked();
    void on_trvTestList_doubleClicked(const QModelIndex &index);

private:
    TNode *getItemFromFolderPath(QString path);
    TNode *getItemFromViewsPath(QString path);
    void activateActions(const bool actionEnabled);
};

} // namespace SDPO

#endif // QMAINFORM_H
