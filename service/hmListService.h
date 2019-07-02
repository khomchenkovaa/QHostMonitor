#ifndef HMLISTSERVICE_H
#define HMLISTSERVICE_H

#include <QObject>
#include <QUuid>

#include "tRoot.h"

namespace SDPO {

struct HMListInfo {
    QUuid   guid;
    bool    modified;
    QString fileName;
    qint64  fileSize;
    bool    storeHistoricalData;
    int     count;

    HMListInfo() {
        clear();
    }

    void clear() {
        guid = QUuid::createUuid();
        modified = false;
        fileName = QString();
        fileSize = 0;
        storeHistoricalData = true;
        count = 3; // root = 0, rootFolder = 1, rootView = 2
    }

    int nextID() {
        return count++;
    }
};

class HMListService : public QObject
{
    Q_OBJECT

    HMListInfo  m_Info;
    TRoot      *m_Root;
    TNode      *m_CurFolder;

public:
    explicit HMListService(QObject *parent = nullptr);
    ~HMListService();

    // getters and setters
    HMListInfo info() const { return m_Info; }
    void       setInfo(const HMListInfo &in) { m_Info = in; }
    QUuid      guid() const { return m_Info.guid; }
    void       setGuid(const QUuid guid) { m_Info.guid = guid; }
    bool       isModelModified() const { return m_Info.modified; }
    QString    currentFileName() const { return m_Info.fileName; }
    void       setFileName(const QString &value) { m_Info.fileName = value; }
    qint64     fileSize() const { return m_Info.fileSize; }
    bool       isStoreHistoricalData() const { return m_Info.storeHistoricalData; }
    void       setStoreHistoricalData(const bool value) { m_Info.storeHistoricalData=value; }
    TNode     *currentFolder() { return m_CurFolder; }
    void       setCurrentFolder(TNode* folder) { m_CurFolder = folder; }

    // test list properties
    bool   isCurFileExists() const { return !m_Info.fileName.isEmpty(); }
    TRoot *rootItem() { return m_Root; }
    TNode *rootFolder() { return m_Root->rootFolder(); }
    TNode *rootView() { return m_Root->rootView(); }
    TNode *nodeByPath(QString path) { return m_Root->findByPath(path); }
    int    nextID() { return m_Info.nextID(); }

    // test list content
    void addNode(TNode* parent, TNode* item);

    // TestList commands
    bool cmdNewTestList();
    bool cmdLoadTestList(QString fileName);
    bool cmdAppendTestList(QString fileName);
    bool cmdImportFromFile(QString fileName, bool skipDuplicates = false, bool writeLog = false);
    bool cmdSaveTestList(QString fileName = QString());
    bool cmdExportHmlIntoText(QString fileName, bool commentDestFolder = false, bool commentLinks = false);
    // Folder commands
    TNode *cmdCreateFolder(QString path);
    bool cmdSetFolderVariable(TNode* folder, QString varName, int varValue, bool inheritPartly = false);
    bool cmdSetFolderAgent(TNode* folder, QString agentName, bool unlessInherited = false);
    bool cmdCopyFolder(TNode* folder, TNode* folder2, bool r = false);
    TNode *cmdCopyTest(TNode* destFolder, QString name, TNode *test, bool skipDuplicates = false);
    // Test commands
    bool cmdDisableTest(QString testName);
    bool cmdEnableTest(QString testName);
    bool cmdRefreshTest(QString testName);
    bool cmdResetTest(QString testName);
    bool cmdPauseTest(QString testName, int interval, QString comment);
    bool cmdResumeTest(QString testName);
    bool cmdSetTestParam(QString testName, QString paramName, int value);
    bool cmdReplaceTestParam(QString testName, QString paramName, int curValue, int newValue);
    bool cmdAckTestStatus(QString testName, QString StopAlerts, QString Comment);
    bool cmdResetAcknowledgements(QString testName);
    bool cmdResetRecurrencesTest(QString testName);
    bool cmdResetEventLogRefPoint(QString testName);
    bool cmdDisableTestByID(TNode* test);
    bool cmdEnableTestByID(TNode* test);
    bool cmdRefreshTestByID(TNode* test, QString forcelog);
    bool cmdRefreshIrregularTestByID(TNode* test, QString forcelog);
    bool cmdResetTestByID(TNode* test);
    bool cmdPauseTestByID(TNode* test, int inteval_minutes);
    bool cmdResumeTestByID(TNode* test, int inteval_minutes);
    bool cmdAckTestStatusbyID(int testId, bool stopAlerts, QString comment);
    bool cmdResetAcknowledgementsByID(int testId);
    bool cmdSetTestParamById(int testId, QString paramName, QString value);
    bool cmdReplaceTestParamById(int testId, QString paramName, QString curValue, QString newValue);
    // Other commands
    bool cmdCreateReport(QString reportProfileName, QString targetFileName);
    bool cmdStartProgram(QString cmdLine);
    bool cmdExecuteProgram(int timeToWait, QString cmdLine);

signals:
//    void HostMonitorStarted(); // 0 - HostMonitor started
//    void MonitoringStarted();  // 1 - Monitoring started
//    void MonitoringStoped();   // 2 - Monitoring stopped
//    void AlertsEnabled();      // 3 - Alerts enabled
//    void AlertsDisabled();     // 4 - Alerts disabled

//    void HostMonitorWillBeTerminated();   //  6 - HostMonitor will be terminated
//    void HostMonitorWillBeReloaded();     //  7 - HostMonitor will be reloaded
//    void HostMonitorSettingsReloaded();   //  8 - HostMonitor settings reloaded
//    void NewTestListCreated();            //  9 - New test list created
//    void TestListLoaded();                // 10 - Test list loaded
//    void NewSettingsApplied();            // 11 - New settings applied
//    void ImportFromTextFile();            // 12 - Import from text file
//    void MergedHmlFile();                 // 13 - Merged HML file
//    void HMScriptStarted();               // 14 - HM Script started
//    void HMScriptFinished();              // 15 - HM Script finished
//    void TestListFilePropertiesChanged(); // 16 - Test list file properties changed

//    void NewTestItem(); // 20 - New test item
//    void NewTestLink(); // 21 - New test link

// 22 - Test modified (single test modified)
// 23 - Test modified (group of tests were modified)
// 24 - Test parameter changed (parameter was changes by HM Script or Telnet)
// 25 - Test moved (test moved from one folder to another)
// 26 - Test deleted
// 27 - Test link deleted

// 28 - Test paused
// 29 - Test resumed
// 30 - Test scheduled to be paused
// 31 - Test pause repealed
// 32 - Test refreshed
// 33 - Test statistics resetted
// 34 - Test disabled
// 35 - Test enabled
// 36 - Test status acknowledged
// 37 - Status acknowledged and alerts for this test stopped
// 38 - Acknowledgement recalled
// 39 - Test quick log cleaned

// 50 - Entire folder refreshed
// 51 - Entire folder resetted
// 52 - Entire folder disabled
// 53 - Entire folder enabled

// 60 - Folder created
// 61 - Folder edited
// 62 - Folder renamed
// 63 - Folder deleted
// 64 - Folder moved
// 65 - Folders resorted
// 66 - Folder-specific agent changed
// 67 - Folder variables changed

// 70 - View created
// 71 - View edited
// 72 - View renamed
// 73 - View deleted
// 74 - View moved
// 75 - Views resorted

// 80 - Denomination

    void modelAboutToChange();
    void modelChanged();
    void folderAdded(TNode *folder);
    void folderAboutToDelete(TNode *folder);
    void folderDeleted(TNode *parentFolder, QString name);
    void viewAdded(TNode *view);
    void viewDeleted(QString name);
    void testAdded(TNode *test);
    void testUpdated(TNode *test);
    void testAboutToDelete(TNode *test);
    void testDeleted(TNode *folder, int idx);
    void linkAdded(TNode *link);
    void linkAboutToDelete(TNode *link);
    void linkDeleted(TNode *folder, TNode* test);
    void monitoringStarted(bool value);
    void monitoringPaused(int interval);
    void alertsEnabled(bool value);
    void alertsPaused(int interval);
    void readyRun(TNode* test);

public slots:
    void cmdAlertsEnable();
    void cmdAlertsDisable();
    void cmdAlertsPause(int interval);
    void cmdMonitoringStart();
    void cmdMonitoringStop();
    void cmdMonitoringPause(int interval);

};

} // namespace SDPO

#endif // HMLISTSERVICE_H
