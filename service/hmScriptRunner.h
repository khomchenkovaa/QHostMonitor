#ifndef HMSCRIPTRUNNER_H
#define HMSCRIPTRUNNER_H

#include "hmListService.h"

#include <QStringList>

namespace SDPO {

// TestList operations
static QString TL_NEW    = QStringLiteral("NewTestList");
static QString TL_LOAD   = QStringLiteral("LoadTestList");
static QString TL_APPEND = QStringLiteral("AppendTestList");
static QString TL_IMPORT = QStringLiteral("ImportFromFile");
static QString TL_SAVE   = QStringLiteral("SaveTestList");
static QString TL_EXPORT = QStringLiteral("ExportHMLintoText");
// Folder Selection
static QString RESOLVE_MACROS     = QStringLiteral("ResolveMacros");
static QString SET_CURRENT_FOLDER = QStringLiteral("SetCurrentFolder");
static QString INCLUDE_SUBFOLDERS = QStringLiteral("IncludeSubfolders");
static QString USE_LINKS          = QStringLiteral("UseLinks");
// Folder Modification
static QString CREATE_FOLDER              = QStringLiteral("CreateFolder");
static QString SET_FOLDER_VARIABLE        = QStringLiteral("SetFolderVariable");
static QString SET_FOLDER_AGENT           = QStringLiteral("SetFolderAgent");
static QString COPY_FOLDER                = QStringLiteral("CopyFolder");
static QString COPY_TEST                  = QStringLiteral("CopyTest");
static QString COPY_TEST_BY_ID            = QStringLiteral("CopyTestByID");
static QString COPY_ALL_TESTS             = QStringLiteral("CopyAllTests");
static QString COPY_INTO_SELECTED_FOLDERS = QStringLiteral("CopyIntoSelectedFolders");
// Manipulation with tests
static QString REFRESH_ALL                  = QStringLiteral("RefreshAll");
static QString RESET_ALL                    = QStringLiteral("ResetAll");
static QString DISABLE_ALL_TESTS            = QStringLiteral("DisableAllTests");
static QString ENABLE_ALL_TESTS             = QStringLiteral("EnableAllTests");
static QString DISABLE_TEST                 = QStringLiteral("DisableTest");
static QString ENABLE_TEST                  = QStringLiteral("EnableTest");
static QString REFRESH_TEST                 = QStringLiteral("RefreshTest");
static QString RESET_TEST                   = QStringLiteral("ResetTest");
static QString PAUSE_TEST                   = QStringLiteral("PauseTest");
static QString RESUME_TEST                  = QStringLiteral("ResumeTest");
static QString SET_TEST_PARAM               = QStringLiteral("SetTestParam");
static QString REPLACE_TEST_PARAM           = QStringLiteral("ReplaceTestParam");
static QString ACK_TEST_STATUS              = QStringLiteral("AckTestStatus");
static QString RESET_ACKNOWLEDGEMENTS       = QStringLiteral("ResetAcknowledgements");
static QString RESET_RECURRENCES_TEST       = QStringLiteral("ResetRecurrencesTest");
static QString RESET_RECURRENCES_ALL        = QStringLiteral("ResetRecurrencesAll");
static QString RESET_EVENT_LOG_REF_POINT    = QStringLiteral("ResetEventLogRefPoint");
static QString DISABLE_TEST_BY_ID           = QStringLiteral("DisableTestByID");
static QString ENABLE_TEST_BY_ID            = QStringLiteral("EnableTestByID");
static QString REFRESH_TEST_BY_ID           = QStringLiteral("RefreshTestByID");
static QString REFRESH_IRREGULAR_TEST_BY_ID = QStringLiteral("RefreshIrregularTestByID");
static QString RESET_TEST_BY_ID             = QStringLiteral("ResetTestByID");
static QString PAUSE_TEST_BY_ID             = QStringLiteral("PauseTestByID");
static QString RESUME_TEST_BY_ID            = QStringLiteral("ResumeTestByID");
static QString ACK_TEST_STATUS_BY_ID        = QStringLiteral("AckTestStatusbyID");
static QString RESET_ACKNOWLEDGEMENTS_BY_ID = QStringLiteral("ResetAcknowledgementsByID");
static QString SET_TEST_PARAM_BY_ID         = QStringLiteral("SetTestParamByID");
static QString REPLACE_TEST_PARAM_BY_ID     = QStringLiteral("ReplaceTestParamByID");
// Global Variable Commands
static QString SET_USER_VARIABLE            = QStringLiteral("SetUserVariable");
static QString SAVE_USER_VARIABLES          = QStringLiteral("SaveUserVariables");
static QString LOAD_USER_VARIABLES          = QStringLiteral("LoadUserVariables");
// Other
static QString FLUSH_COMMON_LOG             = QStringLiteral("FlushCommonLog");
static QString FLUSH_PRIVATE_LOG            = QStringLiteral("FlushPrivateLogs");
static QString CREATE_REPORT                = QStringLiteral("CreateReport");
static QString START_PROGRAM                = QStringLiteral("StartProgram");
static QString EXECUTE_PROGRAM              = QStringLiteral("ExecuteProgram");
static QString ENABLE_ALERTS                = QStringLiteral("EnableAlerts");
static QString DISABLE_ALERTS               = QStringLiteral("DisableAlerts");
static QString PAUSE_ALERTS                 = QStringLiteral("PauseAlerts");
static QString PAUSE_MONITOR                = QStringLiteral("PauseMonitor");
static QString STOP_MONITOR                 = QStringLiteral("StopMonitor");
static QString START_MONITOR                = QStringLiteral("StartMonitor");
static QString QUIT_MONITOR                 = QStringLiteral("QuitMonitor");

static QString YES = QStringLiteral("Yes");
static QString NO  = QStringLiteral("No");

class HMScriptRunner : public QObject
{
    Q_OBJECT

    HMListService *m_HML;
    QString        m_Path;
    QStringList    m_Errors;
    QStringList    m_Script;
    // options
    bool           m_ResolveMacros;
    TNode         *m_CurrentFolder;
    bool           m_IncludeSubfolders;
    bool           m_UseLinks;

public:
    explicit HMScriptRunner(HMListService *hml, QObject *parent = nullptr);

    bool run();
    bool loadScript(const QString &fileName);
    void setScript(const QString &script);
    bool runCmd(const QString &cmd, const int num = 0);
    QStringList scriptErrors() { return m_Errors; }
    void clearErrors() { m_Errors.clear(); }
signals:

public slots:

private:
    QStringList parseCmd(const QString &cmd);
    bool checkParams(const int num, const QStringList &cmdList, const int maxParams);

// TestList operations
    bool runNewTestList(const int num, const QString &cmdLine);
    bool runLoadTestList(const int num, const QString &cmdLine);
    bool runAppendTestList(const int num, const QString &cmdLine);
    bool runImportFromFile(const int num, const QString &cmdLine);
    bool runSaveTestList(const int num, const QString &cmdLine);
    bool runExportHmlIntoText(const int num, const QString &cmdLine);
// Folder Selection
    bool runResolveMacros(const int num, const QString &cmdLine);
    bool runSetCurrentFolder(const int num, const QString &cmdLine);
    bool runIncludeSubfolders(const int num, const QString &cmdLine);
    bool runUseLinks(const int num, const QString &cmdLine);
// Folder Modification
    bool runCreateFolder(const int num, const QString &cmdLine);
    bool runSetFolderVariable(const int num, const QString &cmdLine);
    bool runSetFolderAgent(const int num, const QString &cmdLine);
    bool runCopyFolder(const int num, const QString &cmdLine);
    bool runCopyTest(const int num, const QString &cmdLine);
    bool runCopyTestByID(const int num, const QString &cmdLine);
    bool runCopyAllTests(const int num, const QString &cmdLine);
    bool runCopyIntoSelectedFolders(const int num, const QString &cmdLine);
// Manipulation with tests
    bool runRefreshAll(const int num, const QString &cmdLine);
    bool runResetAll(const int num, const QString &cmdLine);
    bool runDisableAllTests(const int num, const QString &cmdLine);
    bool runEnableAllTests(const int num, const QString &cmdLine);
    bool runDisableTest(const int num, const QString &cmdLine);
    bool runEnableTest(const int num, const QString &cmdLine);
    bool runRefreshTest(const int num, const QString &cmdLine);
    bool runResetTest(const int num, const QString &cmdLine);
    bool runPauseTest(const int num, const QString &cmdLine);
    bool runResumeTest(const int num, const QString &cmdLine);
    bool runSetTestParam(const int num, const QString &cmdLine);
    bool runReplaceTestParam(const int num, const QString &cmdLine);
    bool runAckTestStatus(const int num, const QString &cmdLine);
    bool runResetAcknowledgements(const int num, const QString &cmdLine);
    bool runResetRecurrencesTest(const int num, const QString &cmdLine);
    bool runResetRecurrencesAll(const int num, const QString &cmdLine);
    bool runResetEventLogRefPoint(const int num, const QString &cmdLine);
    bool runDisableTestByID(const int num, const QString &cmdLine);
    bool runEnableTestByID(const int num, const QString &cmdLine);
    bool runRefreshTestByID(const int num, const QString &cmdLine);
    bool runRefreshIrregularTestByID(const int num, const QString &cmdLine);
    bool runResetTestByID(const int num, const QString &cmdLine);
    bool runPauseTestByID(const int num, const QString &cmdLine);
    bool runResumeTestByID(const int num, const QString &cmdLine);
    bool runAckTestStatusbyID(const int num, const QString &cmdLine);
    bool runResetAcknowledgementsByID(const int num, const QString &cmdLine);
    bool runSetTestParamByID(const int num, const QString &cmdLine);
    bool runReplaceTestParamByID(const int num, const QString &cmdLine);
// Global Variable Commands
    bool runSetUserVariable(const int num, const QString &cmdLine);
    bool runSaveUserVariables(const int num, const QString &cmdLine);
    bool runLoadUserVariables(const int num, const QString &cmdLine);
// Other
    bool runFlushCommonLog(const int num, const QString &cmdLine);
    bool runFlushPrivateLogs(const int num, const QString &cmdLine);
    bool runCreateReport(const int num, const QString &cmdLine);
    bool runStartProgram(const int num, const QString &cmdLine);
    bool runExecuteProgram(const int num, const QString &cmdLine);
    bool runEnableAlerts(const int num, const QString &cmdLine);
    bool runDisableAlerts(const int num, const QString &cmdLine);
    bool runPauseAlerts(const int num, const QString &cmdLine);
    bool runPauseMonitor(const int num, const QString &cmdLine);
    bool runStopMonitor(const int num, const QString &cmdLine);
    bool runStartMonitor(const int num, const QString &cmdLine);
    bool runQuitMonitor(const int num, const QString &cmdLine);

};

} // namespace SDPO

#endif // HMSCRIPTRUNNER_H
