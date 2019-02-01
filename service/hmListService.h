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
    int     fileSize;
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
    explicit HMListService(QObject *parent = 0);
    ~HMListService();

    // getters and setters
    HMListInfo info() const { return m_Info; }
    void       setInfo(const HMListInfo &in) { m_Info = in; }
    QUuid   guid() const { return m_Info.guid; }
    void    setGuid(const QUuid guid) { m_Info.guid = guid; }
    bool    isModelModified() const { return m_Info.modified; }
    QString currentFileName() const { return m_Info.fileName; }
    void    setFileName(const QString &value) { m_Info.fileName = value; }
    int     fileSize() const { return m_Info.fileSize; }
    bool    isStoreHistoricalData() const { return m_Info.storeHistoricalData; }
    void    setStoreHistoricalData(const bool value) { m_Info.storeHistoricalData=value; }
    TNode  *currentFolder() { return m_CurFolder; }
    void    setCurrentFolder(TNode* folder) { m_CurFolder = folder; }

    // test list properties
    bool   isCurFileExists() const { return !m_Info.fileName.isEmpty(); }
    TRoot *rootItem() { return m_Root; }
    TNode *rootFolder() { return m_Root->rootFolder(); }
    TNode *rootView() { return m_Root->rootView(); }
    TNode *nodeByPath(QString path) { return m_Root->findByPath(path); }
    int    nextID() { return m_Info.nextID(); }

    // test list content
    void addNode(TNode* parent, TNode* item);

    // commands
    bool cmdNewTestList();
    bool cmdLoadTestList(QString fileName);                                                                  //! TODO
    bool cmdAppendTestList(QString fileName);                                                                //! TODO
    bool cmdImportFromFile(QString fileName, bool skipDuplicates = false, bool writeLog = false);
    bool cmdSaveTestList(QString fileName = QString());
    bool cmdExportHmlIntoText(QString fileName, bool commentDestFolder = false, bool commentLinks = false);
    TNode *cmdCreateFolder(QString path);
    bool cmdSetFolderVariable(TNode* folder, QString varName, int varValue, bool inheritPartly = false);     //! TODO
    bool cmdSetFolderAgent(TNode* folder, QString agentName, bool unlessInherited = false);                  //! TODO
    bool cmdCopyFolder(TNode* folder, TNode* folder2, bool r = false);                                       //! TODO
    TNode *cmdCopyTest(TNode* destFolder, QString name, TNode *test, bool skipDuplicates = false);
    bool cmdDisableTest(QString fileName);
    bool cmdEnableTest(QString fileName);
    bool cmdRefreshTest(QString fileName);
    bool cmdResetTest(QString fileName);
    bool cmdPauseTest(QString fileName, int interval, QString Comment);
    bool cmdResumeTest(QString fileName);
    bool cmdSetTestParam(QString fileName, QString ParameterName, int Value);
    bool cmdReplaceTestParam(QString fileName, QString ParameterName, int CurrValue, int NewValue);
    bool cmdAckTestStatus(QString fileName, QString StopAlerts, QString Comment);
    bool cmdResetAcknowledgements(QString fileName);
    bool cmdResetRecurrencesTest(QString fileName);
    bool cmdResetEventLogRefPoint(QString fileName);
    bool cmdDisableTestByID(TNode* fileName);
    bool cmdEnableTestByID(TNode* fileName);
    bool cmdRefreshTestByID(TNode* fileName, QString forcelog);
    bool cmdRefreshIrregularTestByID(TNode* fileName, QString forcelog);
    bool cmdResetTestByID(TNode* fileName);
    bool cmdPauseTestByID(TNode* fileName, int inteval_minutes);
    bool cmdResumeTestByID(TNode* fileName, int inteval_minutes);
    bool cmdAckTestStatusbyID(TNode* fileName, QString StopAlerts, QString Comment);
    bool cmdResetAcknowledgementsByID(TNode* fileName);
    bool cmdSetTestParamByID(TNode* fileName, QString ParameterName, int Value);
    bool cmdReplaceTestParamByID(TNode* fileName, QString ParameterName, int CurrValue, int NewValue);
    bool cmdSetUserVariable(TNode* VariableName, int VariableValue);
    bool cmdCreateReport(QString report_profile_name, QString target_file_name);
    bool cmdStartProgram(QString CommandLine);
    bool cmdExecuteProgram(int TimeToWait, QString CommandLine);

signals:
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
