#include "hmScriptRunner.h"

#include <QCoreApplication>
#include <QFile>

namespace SDPO {

/*****************************************************************/

HMScriptRunner::HMScriptRunner(HMListService *hml, QString &fileName, QObject *parent) :
    QObject(parent),
    m_HML(hml),
    m_FileName(fileName)
{
    m_ResolveMacros     = true;
    m_CurrentFolder     = m_HML->rootFolder();
    m_IncludeSubfolders = true;
    m_UseLinks          = false;
    loadScript();
}

/*****************************************************************/

bool HMScriptRunner::run()
{
    if (!m_Errors.isEmpty()) return false;
    for(int i=0; i<m_Script.size();++i) { // we need line number
        QString cmd = m_Script.at(i).trimmed();
        if (cmd.isEmpty())       continue;
        if (cmd.startsWith(";")) continue;
        if (!runCmd(i,cmd)) return false;
    }
    return true;
}

/*****************************************************************/

bool HMScriptRunner::loadScript()
{
    m_Errors.clear();
    QFile stdFile(m_FileName);
    if (stdFile.exists()) {
        if (!stdFile.open(QFile::ReadOnly|QFile::Text)) {
            m_Errors.append(tr("[FATAL] Could not open HMScript File '%1'\n").arg(m_FileName));
        } else {
            QString script = stdFile.readAll();
            stdFile.close();
            m_Script = script.split("\n");
        }
    } else {
        m_Errors.append(tr("[FATAL] HMScript File '%1' does not exists\n").arg(m_FileName));
    }

    return m_Errors.isEmpty();
}

/*****************************************************************/

QStringList HMScriptRunner::parseCmd(const QString &cmd)
{
    //! TODO support macro variables here

    bool inside = cmd.startsWith("\""); //true if the first character is "
    QStringList tmpList = cmd.split("\"", QString::SkipEmptyParts); // Split by \" and make sure you don't have an empty string at the beginning
    QStringList result;
    foreach (const QString &s, tmpList) {
        if (inside) { // If 's' is inside quotes ...
            result.append(s); // ... get the whole string
        } else {      // If 's' is outside quotes ...
            result.append(s.split(" ", QString::SkipEmptyParts)); // ... get the splitted string
        }
        inside = !inside;
    }
    return result;
}

/*****************************************************************/

bool HMScriptRunner::checkParams(const int num, const QStringList &cmdList, const int maxParams)
{
    if (cmdList.isEmpty()) {
        m_Errors.append(tr("[ERROR] Line %1: Command is empty\n").arg(num));
        return false;
    }
    if (cmdList.size() > maxParams+1) {
        m_Errors.append(tr("[WARNING] Line %1: Wrong number of params '%2'\n").arg(num).arg(cmdList.size()-1));
    }
    return true;
}

/*****************************************************************/

bool HMScriptRunner::runCmd(const int num, const QString &cmd)
{
    if (cmd.startsWith(TL_NEW, Qt::CaseInsensitive)) {
        return runNewTestList(num, cmd);
    } else if (cmd.startsWith(TL_LOAD, Qt::CaseInsensitive)) {
        return runLoadTestList(num, cmd);
    } else if (cmd.startsWith(TL_APPEND, Qt::CaseInsensitive)) {
        return runAppendTestList(num, cmd);
    } else if (cmd.startsWith(TL_IMPORT, Qt::CaseInsensitive)) {
        return runImportFromFile(num, cmd);
    } else if (cmd.startsWith(TL_SAVE, Qt::CaseInsensitive)) {
        return runSaveTestList(num, cmd);
    } else if (cmd.startsWith(TL_EXPORT, Qt::CaseInsensitive)) {
        return runExportHmlIntoText(num, cmd);
    } else if (cmd.startsWith(RESOLVE_MACROS, Qt::CaseInsensitive)) {
        return runResolveMacros(num, cmd);
    } else if (cmd.startsWith(SET_CURRENT_FOLDER, Qt::CaseInsensitive)) {
        return runSetCurrentFolder(num, cmd);
    } else if (cmd.startsWith(INCLUDE_SUBFOLDERS, Qt::CaseInsensitive)) {
        return runIncludeSubfolders(num, cmd);
    } else if (cmd.startsWith(USE_LINKS, Qt::CaseInsensitive)) {
        return runUseLinks(num, cmd);
    } else if (cmd.startsWith(CREATE_FOLDER, Qt::CaseInsensitive)) {
        return runCreateFolder(num, cmd);
    } else if (cmd.startsWith(SET_FOLDER_VARIABLE, Qt::CaseInsensitive)) {
        return runSetFolderVariable(num, cmd);
    } else if (cmd.startsWith(SET_FOLDER_AGENT, Qt::CaseInsensitive)) {
        return runSetFolderAgent(num, cmd);
    } else if (cmd.startsWith(COPY_FOLDER, Qt::CaseInsensitive)) {
        return runCopyFolder(num, cmd);
    } else if (cmd.startsWith(COPY_TEST, Qt::CaseInsensitive)) {
        return runCopyTest(num, cmd);
    } else if (cmd.startsWith(COPY_TEST_BY_ID, Qt::CaseInsensitive)) {
        return runCopyTestByID(num, cmd);
    } else if (cmd.startsWith(COPY_ALL_TESTS, Qt::CaseInsensitive)) {
        return runCopyAllTests(num, cmd);
    } else if (cmd.startsWith(COPY_INTO_SELECTED_FOLDERS, Qt::CaseInsensitive)) {
        return runCopyIntoSelectedFolders(num, cmd);
    } else if (cmd.startsWith(REFRESH_ALL, Qt::CaseInsensitive)) {
        return runRefreshAll(num, cmd);
    } else if (cmd.startsWith(RESET_ALL, Qt::CaseInsensitive)) {
        return runResetAll(num, cmd);
    } else if (cmd.startsWith(DISABLE_ALL_TESTS, Qt::CaseInsensitive)) {
        return runDisableAllTests(num, cmd);
    } else if (cmd.startsWith(ENABLE_ALL_TESTS, Qt::CaseInsensitive)) {
        return runEnableAllTests(num, cmd);
    } else if (cmd.startsWith(DISABLE_TEST, Qt::CaseInsensitive)) {
        return runDisableTest(num, cmd);
    } else if (cmd.startsWith(ENABLE_TEST, Qt::CaseInsensitive)) {
        return runEnableTest(num, cmd);
    } else if (cmd.startsWith(REFRESH_TEST, Qt::CaseInsensitive)) {
        return runRefreshTest(num, cmd);
    } else if (cmd.startsWith(RESET_TEST, Qt::CaseInsensitive)) {
        return runResetTest(num, cmd);
    } else if (cmd.startsWith(PAUSE_TEST, Qt::CaseInsensitive)) {
        return runPauseTest(num, cmd);
    } else if (cmd.startsWith(RESUME_TEST, Qt::CaseInsensitive)) {
        return runResumeTest(num, cmd);
    } else if (cmd.startsWith(SET_TEST_PARAM, Qt::CaseInsensitive)) {
        return runSetTestParam(num, cmd);
    } else if (cmd.startsWith(REPLACE_TEST_PARAM, Qt::CaseInsensitive)) {
        return runReplaceTestParam(num, cmd);
    } else if (cmd.startsWith(ACK_TEST_STATUS, Qt::CaseInsensitive)) {
        return runAckTestStatus(num, cmd);
    } else if (cmd.startsWith(RESET_ACKNOWLEDGEMENTS, Qt::CaseInsensitive)) {
        return runResetAcknowledgements(num, cmd);
    } else if (cmd.startsWith(RESET_RECURRENCES_TEST, Qt::CaseInsensitive)) {
        return runResetRecurrencesTest(num, cmd);
    } else if (cmd.startsWith(RESET_RECURRENCES_ALL, Qt::CaseInsensitive)) {
        return runResetRecurrencesAll(num, cmd);
    } else if (cmd.startsWith(RESET_EVENT_LOG_REF_POINT, Qt::CaseInsensitive)) {
        return runResetEventLogRefPoint(num, cmd);
    } else if (cmd.startsWith(DISABLE_TEST_BY_ID, Qt::CaseInsensitive)) {
        return runDisableTestByID(num, cmd);
    } else if (cmd.startsWith(ENABLE_TEST_BY_ID, Qt::CaseInsensitive)) {
        return runEnableTestByID(num, cmd);
    } else if (cmd.startsWith(REFRESH_TEST_BY_ID, Qt::CaseInsensitive)) {
        return runRefreshTestByID(num, cmd);
    } else if (cmd.startsWith(REFRESH_IRREGULAR_TEST_BY_ID, Qt::CaseInsensitive)) {
        return runRefreshIrregularTestByID(num, cmd);
    } else if (cmd.startsWith(RESET_TEST_BY_ID, Qt::CaseInsensitive)) {
        return runResetTestByID(num, cmd);
    } else if (cmd.startsWith(PAUSE_TEST_BY_ID, Qt::CaseInsensitive)) {
        return runPauseTestByID(num, cmd);
    } else if (cmd.startsWith(RESUME_TEST_BY_ID, Qt::CaseInsensitive)) {
        return runResumeTestByID(num, cmd);
    } else if (cmd.startsWith(ACK_TEST_STATUS_BY_ID, Qt::CaseInsensitive)) {
        return runAckTestStatusbyID(num, cmd);
    } else if (cmd.startsWith(RESET_ACKNOWLEDGEMENTS_BY_ID, Qt::CaseInsensitive)) {
        return runResetAcknowledgementsByID(num, cmd);
    } else if (cmd.startsWith(SET_TEST_PARAM_BY_ID, Qt::CaseInsensitive)) {
        return runSetTestParamByID(num, cmd);
    } else if (cmd.startsWith(REPLACE_TEST_PARAM_BY_ID, Qt::CaseInsensitive)) {
        return runReplaceTestParamByID(num, cmd);
    } else if (cmd.startsWith(SET_USER_VARIABLE, Qt::CaseInsensitive)) {
        return runSetUserVariable(num, cmd);
    } else if (cmd.startsWith(SAVE_USER_VARIABLES, Qt::CaseInsensitive)) {
        return runSaveUserVariables(num, cmd);
    } else if (cmd.startsWith(LOAD_USER_VARIABLES, Qt::CaseInsensitive)) {
        return runLoadUserVariables(num, cmd);
    } else if (cmd.startsWith(FLUSH_COMMON_LOG, Qt::CaseInsensitive)) {
        return runFlushCommonLog(num, cmd);
    } else if (cmd.startsWith(FLUSH_PRIVATE_LOG, Qt::CaseInsensitive)) {
        return runFlushPrivateLogs(num, cmd);
    } else if (cmd.startsWith(CREATE_REPORT, Qt::CaseInsensitive)) {
        return runCreateReport(num, cmd);
    } else if (cmd.startsWith(START_PROGRAM, Qt::CaseInsensitive)) {
        return runStartProgram(num, cmd);
    } else if (cmd.startsWith(EXECUTE_PROGRAM, Qt::CaseInsensitive)) {
        return runExecuteProgram(num, cmd);
    } else if (cmd.startsWith(ENABLE_ALERTS, Qt::CaseInsensitive)) {
        return runEnableAlerts(num, cmd);
    } else if (cmd.startsWith(DISABLE_ALERTS, Qt::CaseInsensitive)) {
        return runDisableAlerts(num, cmd);
    } else if (cmd.startsWith(PAUSE_ALERTS, Qt::CaseInsensitive)) {
        return runPauseAlerts(num, cmd);
    } else if (cmd.startsWith(PAUSE_MONITOR, Qt::CaseInsensitive)) {
        return runPauseMonitor(num, cmd);
    } else if (cmd.startsWith(STOP_MONITOR, Qt::CaseInsensitive)) {
        return runStopMonitor(num, cmd);
    } else if (cmd.startsWith(START_MONITOR, Qt::CaseInsensitive)) {
        return runStartMonitor(num, cmd);
    } else if (cmd.startsWith(QUIT_MONITOR, Qt::CaseInsensitive)) {
        return runQuitMonitor(num, cmd);
    } else {
        m_Errors.append(tr("[ERROR] Line %1: Unkown command '%2'\n").arg(num).arg(cmd));
    }
    return false;
}

/*****************************************************************
 * Creates new empty TestList.
 * Params: [DiscardChanges]
 * Use optional DiscardChanges parameter to create new test list without saving current list of tests
 *****************************************************************/
bool HMScriptRunner::runNewTestList(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }

    bool discardChanged = cmdList.contains("DiscardChanges");

    if (!discardChanged && m_HML->isModelModified()) {
        m_Errors.append(tr("[ERROR] Line %1: Test List is changed. Save it first\n").arg(num));
        return false;
    }

    return m_HML->cmdNewTestList();
}

/*****************************************************************
 * Loads an existing TestList
 * Params: <FileName.HML>
 *****************************************************************/
bool HMScriptRunner::runLoadTestList(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    cmdList.removeFirst(); // remove command

    if (cmdList.isEmpty()) {
        m_Errors.append(tr("[ERROR] Line %1: Command '%2' has no filename\n").arg(num).arg(cmdLine));
        return false;
    }
    QString fileName = cmdList.takeFirst();

    if (!fileName.startsWith("/")) {
        int idx = m_FileName.lastIndexOf("/");
        fileName = m_FileName.mid(0,idx+1) + fileName;
    }

    return m_HML->cmdLoadTestList(fileName);
}

/*****************************************************************
 * Appends data to the current TestList from a specified HML file
 * Params: <FileName.HML>
 *****************************************************************/
bool HMScriptRunner::runAppendTestList(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    cmdList.removeFirst(); // remove command

    if (cmdList.isEmpty()) {
        m_Errors.append(tr("[ERROR] Line %1: Command '%2' has no filename\n").arg(num).arg(cmdLine));
        return false;
    }
    QString fileName = cmdList.takeFirst();

    if (!fileName.startsWith("/")) {
        int idx = m_FileName.lastIndexOf("/");
        fileName = m_FileName.mid(0,idx+1) + fileName;
    }

    return m_HML->cmdAppendTestList(fileName);
}

/*****************************************************************
 * Imports tests from specialText file.
 * Params: <FileName> [SkipDuplicates] [WriteLog]
 * SkipDuplicates - optional parameter, HostMonitor will skip test when test with the same name already present in the TestList.
 * WriteLog - optional parameter, HostMonitor will record to the system logfile information about all errors and warnings during the import process.
 *****************************************************************/
bool HMScriptRunner::runImportFromFile(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 3)) {
        return false;
    }
    cmdList.removeFirst(); // remove command

    if (cmdList.isEmpty()) {
        m_Errors.append(tr("[ERROR] Line %1: Command '%2' has no filename\n").arg(num).arg(cmdLine));
        return false;
    }
    QString fileName = cmdList.takeFirst();
    if (!fileName.startsWith("/")) {
        int idx = m_FileName.lastIndexOf("/");
        fileName = m_FileName.mid(0,idx+1) + fileName;
    }

    bool skipDuplicates = cmdList.contains("SkipDuplicates");
    bool writeLog = cmdList.contains("WriteLog");

    return m_HML->cmdImportFromFile(fileName, skipDuplicates, writeLog);
}

/*****************************************************************
 * Saves the current list using its current or new file name.
 * Params: [<FileName>]
 * Parameter is optional when current list was loaded from the file (in this case HostMonitor knows the name of the file).
 * You must specify a name of the file when you have created a new list.
 *****************************************************************/
bool HMScriptRunner::runSaveTestList(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    cmdList.removeFirst(); // remove command

    QString fileName;

    if (!cmdList.isEmpty()) {
        fileName = cmdList.takeFirst();
        if (!fileName.startsWith("/")) {
            int idx = m_FileName.lastIndexOf("/");
            fileName = m_FileName.mid(0,idx+1) + fileName;
        }
    }

    return m_HML->cmdSaveTestList(fileName);
}

/*****************************************************************
 * This command tells HostMonitor to export test settings into specified text file.
 * Params: <FileName> [-SF] [-SL]
 * Optional parameters:
 * -SF - comment destination folders;
 * -SL - comment test links
 *****************************************************************/
bool HMScriptRunner::runExportHmlIntoText(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 3)) {
        return false;
    }
    cmdList.removeFirst(); // remove command

    if (cmdList.isEmpty()) {
        m_Errors.append(tr("[ERROR] Line %1: Command '%2' has no filename\n").arg(num).arg(cmdLine));
        return false;
    }
    QString fileName = cmdList.takeFirst();

    if (!fileName.startsWith("/")) {
        int idx = m_FileName.lastIndexOf("/");
        fileName = m_FileName.mid(0,idx+1) + fileName;
    }

    bool commentDestFolder = cmdList.contains("-SF");
    bool commentLinks = cmdList.contains("-SL");

    return m_HML->cmdExportHmlIntoText(fileName, commentDestFolder, commentLinks);
}

/*****************************************************************
 * Normally HostMonitor resolves macro variables specified in the script.
 * However you may turn this option off at any time (and later turn it on again if you need).
 * Command has effect for the following commands within the script (commands located below ResolveMacros line).
 * For example this can be useful when you need to assign some macros for comment pattern.
 * Params: yes|no
 *****************************************************************/
bool HMScriptRunner::runResolveMacros(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    cmdList.removeFirst(); // remove command

    if (cmdList.isEmpty()) {
        m_Errors.append(tr("[WARNING] Line %1: Command '%2' has no parameter (yes|no)\n").arg(num).arg(cmdLine));
        return false;
    } else if (cmdList.first().compare(YES,Qt::CaseInsensitive) == 0) {
        m_ResolveMacros = true;
    } else if (cmdList.first().compare(NO,Qt::CaseInsensitive) == 0) {
        m_ResolveMacros = false;
    } else {
        m_Errors.append(tr("[WARNING] Line %1: Unknown parameter '%2'\n").arg(num).arg(cmdList.first()));
        return false;
    }
    return true;
}

/*****************************************************************
 * Sets current folder, the following commands from this section (manipulation with tests) will work within specified folder.
 * By default, HostMonitor uses the top folder including all subfolders (in other words, works will entire TestList).
 * Params: <name of folder>|<full path>
 *****************************************************************/
bool HMScriptRunner::runSetCurrentFolder(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    cmdList.removeFirst(); // remove command

    if (cmdList.isEmpty()) {
        m_Errors.append(tr("[WARNING] Line %1: Command '%2' has no parameter\n").arg(num).arg(cmdLine));
        return false;
    }
    QString folder = cmdList.takeFirst();

    TRoot *root = m_HML->rootItem();
    TNode *found = 0;
    if (folder.contains("/")) { // find by path
        found = root->findByPath(folder);
    } else { // find by name
        found = root->findChildRecursive(folder);
    }

    if (found && found->getType() == TNode::FOLDER) {
        m_CurrentFolder = found;
    } else {
        m_Errors.append(tr("[WARNING] Line %1: folder '%2' not found\n").arg(num).arg(folder));
    }
    return true;
}

/*****************************************************************
 * Defines either to perform operations for the current folder only or to use the folder and all descendant subfolders.
 * By default, HostMonitor works with the specified folder and all descendant subfolders.
 * Params: yes|no
 *****************************************************************/
bool HMScriptRunner::runIncludeSubfolders(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    cmdList.removeFirst(); // remove command

    if (cmdList.isEmpty()) {
        m_Errors.append(tr("[WARNING] Line %1: Command '%2' has no parameter (yes|no)\n").arg(num).arg(cmdLine));
        return false;
    } else if (cmdList.first().compare(YES,Qt::CaseInsensitive) == 0) {
        m_IncludeSubfolders = true;
    } else if (cmdList.first().compare(NO,Qt::CaseInsensitive) == 0) {
        m_IncludeSubfolders = false;
    } else {
        m_Errors.append(tr("[WARNING] Line %1: Unknown parameter '%2'\n").arg(num).arg(cmdList.first()));
        return false;
    }
    return true;
}

/*****************************************************************
 * Tells HostMonitor to perform (or does not perform) operations with test items that represented in the folder as links
 * Params: yes|no
 *****************************************************************/
bool HMScriptRunner::runUseLinks(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    cmdList.removeFirst(); // remove command

    if (cmdList.isEmpty()) {
        m_Errors.append(tr("[WARNING] Line %1: Command '%2' has no parameter (yes|no)\n").arg(num).arg(cmdLine));
        return false;
    } else if (cmdList.first().compare(YES,Qt::CaseInsensitive) == 0) {
        m_UseLinks = true;
    } else if (cmdList.first().compare(NO,Qt::CaseInsensitive) == 0) {
        m_UseLinks = false;
    } else {
        m_Errors.append(tr("[WARNING] Line %1: Unknown parameter '%2'\n").arg(num).arg(cmdList.first()));
        return false;
    }
    return true;
}

/*****************************************************************
 * Creates new folder(s).
 * Params: <full path to the folder>
 * The value of this parameter should specify the full path to the folder that you want to create.
 * E.g. CreateFolder Root\USA Branch\Support\part2\ will successively create 3 folders
 * - "USA Branch" folder in the "Root" folder,
 * - "Support" folder in "USA Branch" subfolder,
 * - "part2" folder in "Support" subfolder.
 * If some (or all) of specified folders already exist, HostMonitor will not create second copy of them.
 *****************************************************************/
bool HMScriptRunner::runCreateFolder(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    cmdList.removeFirst(); // remove command

    if (!cmdList.count()) {
        m_Errors.append(tr("[ERROR] Line %1: Command '%2' has no path\n").arg(num).arg(cmdLine));
        return false;
    }
    QString path = cmdList.takeFirst();
    path = path.replace("\\","/");
    m_HML->cmdCreateFolder(path);
    return true;
}

/*****************************************************************
 * Sets or modifies folder variable for current folder.
 * Params: <variable_name>
 *         <variable_value>
 *         [-inheritpartly]
 * If currently folder settings set to "inherit all variables from parent folder", this command will set "Use folder variables only" mode.
 * Unless you specify optional -inheritpartly parameter; in such case HostMonitor will set "Use inherited variables; folder variables may override inherited variables" option.
 * Note: if you are using folder-level variables as parameters of some test items, this command will modify test settings automatically.
 *****************************************************************/

bool HMScriptRunner::runSetFolderVariable(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 3)) {
        return false;
    }
    cmdList.removeFirst(); // remove command

    if (!cmdList.count()) {
        m_Errors.append(tr("[ERROR] Line %1: Command '%2' has no variable name\n").arg(num).arg(cmdLine));
        return false;
    }
    QString varName = cmdList.takeFirst();

    if (!cmdList.count()) {
        m_Errors.append(tr("[ERROR] Line %1: Command '%2' has no variable value\n").arg(num).arg(cmdLine));
        return false;
    }
    QString varValue = cmdList.takeFirst();

    bool inheritPartly = cmdList.contains("-inheritpartly");
    m_HML->cmdSetFolderVariable(m_CurrentFolder, varName, varValue, inheritPartly);
    return true;
}

/*****************************************************************
 * Sets Remote Monitoring Agent for specific folder.
 * Params: <fullpath>|<folderID>
 *         <agentname>
 *         [UnlessInherited]
 * You may specify folder using full path or using folder ID; specify agent using its name.
 * Optional "UnlessInherited" parameter tells HostMonitor to check agent used by parent folder and set (when possible)
 * "Inherit agent from parent" option instead of changing folder-specific agent.
 * If "UnlessInherited" is not specified then HostMonitor will set specified agent regardless of parent agent.
 *****************************************************************/

bool HMScriptRunner::runSetFolderAgent(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 3)) {
        return false;
    }
    cmdList.removeFirst(); // remove command

    if (cmdList.isEmpty()) {
        m_Errors.append(tr("[WARNING] Line %1: Command '%2' has no folder\n").arg(num).arg(cmdLine));
        return false;
    }
    QString folder = cmdList.takeFirst();
    TNode *found = 0;
    if (folder.contains("/")) { // find by path
        found = m_HML->rootItem()->findByPath(folder);
    } else { // find by id
        found = m_HML->rootFolder()->findByID(folder.toInt());
    }
    if (!found || found->getType() != TNode::FOLDER) {
        m_Errors.append(tr("[WARNING] Line %1: folder '%2' not found\n").arg(num).arg(folder));
        return false;
    }

    if (!cmdList.count()) {
        m_Errors.append(tr("[ERROR] Line %1: Command '%2' has no agent name\n").arg(num).arg(cmdLine));
        return false;
    }
    QString agentName = cmdList.takeFirst();

    bool unlessInherited = cmdList.contains("UnlessInherited");

    m_HML->cmdSetFolderAgent(found, agentName, unlessInherited);
    return true;
}

/*****************************************************************
 * Optional parameter "-r" tells HostMonitor to copy folder with its subfolders.
 * Params: [-r]
 *         <srcname>|<id>|<fullpath>
 *         <newname>|<newfullpath>
 * Source folder can be specified by name (if this folder located within current parent folder - folder selected by
 * SetCurrentFolder command); folder ID or full path to the folder.
 * Target folder can be specified by name or full path.
 *****************************************************************/

bool HMScriptRunner::runCopyFolder(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 3)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Copies specific test or group of tests (e.g. all Ping tests) into specified folder.
 * Params: <testname>|<groupname>
 *         <destfullpath>|<folderid>
 * Destination folder can be specified by full path or folder ID
 *****************************************************************/

bool HMScriptRunner::runCopyTest(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 2)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Copies single test specified by ID into target folder specified by full path or folder ID
 * Params: <testid>
 *         <destfullpath>|<folderid>
 *****************************************************************/

bool HMScriptRunner::runCopyTestByID(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 2)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Copies all test items from current folder (and optionally subfolders) into target folder
 * Params: [-r]
 *         [-skipduplicates]
 *         <destfullpath>|<folderid>
 *****************************************************************/

bool HMScriptRunner::runCopyAllTests(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 3)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * This command allows you to copy specified test item into set of folders.
 * You may select destination folders using logical expressions based on folder name or folder-level variables.
 * Params: <testname>|<TestID>
 *         Below <fullpath>|<TopFolderID> When <expression>
 *         [-skipduplicates]
 * First parameter (<test name> or <testID>) specifies what exactly test item should be copied.
 * "Below <fullpath>" or "Below <TopFolderID>" parameter specifies target folders branch that should be used for operation.
 * Then HostMonitor checks each folder and subfolder within specified branch, resolves folder-related macro variables,
 * evaluates specified logical expression (When <expression> parameter) and copies the test item into folder when <expression> is true.
 * For example, if you use "%folder%"=="Memory tests" expression, HostMonitor will copy test into each folder that named "Memory tests".
 * If you use expression like "Important" in "%FolderComment%", HostMonitor will copy test into each folder that has word "Important" within folder comments.
 * If you use expression "%fvar_testtype%" == "memory", HostMonitor will copy test into each folder that has %fvar_testtype% variable set to "memory" string.
 * Last optional parameter (-skipduplicates) tells HostMonitor to skip operation for the folder when target folder already has test with the same name.
 * Note: as usually HostMonitor will resolve folder-related variables that can be used as test parameters. This way single command can create set of tests for various servers.
 *****************************************************************/

bool HMScriptRunner::runCopyIntoSelectedFolders(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 3)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Checks the status of all tests in the folder (except disabled hosts) immediately,
 * do not wait for the elapse test interval for each test
 *****************************************************************/
bool HMScriptRunner::runRefreshAll(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Resets statistics for all tests within the folder
 *****************************************************************/
bool HMScriptRunner::runResetAll(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Disables all tests in the folder
 *****************************************************************/
bool HMScriptRunner::runDisableAllTests(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Enables all tests in the folder
 *****************************************************************/
bool HMScriptRunner::runEnableAllTests(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Disables the specified test
 * Params: <TestName>
 *****************************************************************/
bool HMScriptRunner::runDisableTest(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Enables the specified test
 * Params: <TestName>
 *****************************************************************/
bool HMScriptRunner::runEnableTest(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Checks the status of the specified test immediately
 * Params: <TestName>
 *****************************************************************/
bool HMScriptRunner::runRefreshTest(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Resets statistics for specified test or group of tests
 * Params: <TestName>
 *****************************************************************/
bool HMScriptRunner::runResetTest(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Pauses specified test or group of tests (time interval should be specified in minutes, up to 1440 min).
 * Params: <TestName>
 *         <interval>
 *         [<comment>]
 *****************************************************************/
bool HMScriptRunner::runPauseTest(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 3)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Resumes paused test or group of tests
 * Params: <TestName>
 *****************************************************************/
bool HMScriptRunner::runResumeTest(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Params: <TestName>
 *         <ParameterName>
 *         <Value>
 *****************************************************************/
bool HMScriptRunner::runSetTestParam(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 3)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Replaces a value of a given parameter for the specified test or group of tests. Unlike "SetTestParam" command, this one has a selective approach.
 * It changes the value of a parameter only for the tests that have a current value equal to the <Curr. value> argument of the command.
 * List of parameters equivalent to parameters of SetTestParam command.
 * Params: <TestName>
 *         <ParameterName>
 *         <Curr. value>
 *         <New value>
 *****************************************************************/
bool HMScriptRunner::runReplaceTestParam(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 4)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Acknowledges failed test item(s)
 * Params: <TestName>
 *         [StopAlerts]
 *         [<Comment>]
 *****************************************************************/
bool HMScriptRunner::runAckTestStatus(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 3)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Params: <TestName>
 *****************************************************************/
bool HMScriptRunner::runResetAcknowledgements(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Resets Recurrences counter to 0 for specified test.
 * Params: <TestName>
 * Note: after Recurrences counter is set to 0, HostMonitor will interpret ANY status assigned by next check as "new" status.
 * E.g. if 1st check after you have used ResetRecurrencesTest command returns "Ok" status,
 * HostMonitor will consider that previous status of the test was not "Ok" (either "Bad" or "Unknown").
 * This allows you to forcedly start actions that already were executed (e.g. for testing purpose).
 *****************************************************************/
bool HMScriptRunner::runResetRecurrencesTest(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Sets Recurrences counter to 0 for all tests in the folder.
 *****************************************************************/
bool HMScriptRunner::runResetRecurrencesAll(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * This command resets internal counters of the NT Event Log test so that the next time when the test is performed
 * HostMonitor ignores all events that have happened before execution of this command.
 * Please note: clocks on local and remote systems must be synchronized if you check event log on the latter, in order for this command to work correctly.
 * Params: <TestName>
 *****************************************************************/
bool HMScriptRunner::runResetEventLogRefPoint(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Disables test item specified by unique ID
 * Params: <TestID>
 *****************************************************************/
bool HMScriptRunner::runDisableTestByID(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Enables test item specified by unique ID
 * Params: <TestID>
 *****************************************************************/
bool HMScriptRunner::runEnableTestByID(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
        return false;
    }
    m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
    return true;
}

/*****************************************************************
 * Checks the status of the specified test immediately.
 * Params: <TestID>
 *         [forcelog]
 * Optional parameter "forcelog" tells HostMonitor to record test result into log file(s) regardless of logging mode and test
 * result (effects just 1 test probe caused by "Refresh" command).
 * In other words test result will be recorded even if you are using Brief logging mode and test status did not change.
 *****************************************************************/
bool HMScriptRunner::runRefreshTestByID(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 2)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}
/*****************************************************************
 * Command works similar to RefreshTestByID command - it tells HostMonitor to perform test probe immediately.
 * In contrast to RefreshTestByID command, it can force execution even for test items that were configured with Irregular schedule
 * Params: <TestID>
 *         [forcelog]
 *****************************************************************/
bool HMScriptRunner::runRefreshIrregularTestByID(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 2)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}
/*****************************************************************
 * Resets statistics test item specified by unique ID
 * Params: <TestID>
 *****************************************************************/
bool HMScriptRunner::runResetTestByID(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Pauses test item specified by unique ID (up to 1440 min)
 * Params: <TestID>
 *         <interval_minutes> [<Comment>]
 *****************************************************************/
bool HMScriptRunner::runPauseTestByID(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 2)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Resumes paused test item
 * Params: <TestID>
 *         <interval_minutes> [<Comment>]
 *****************************************************************/
bool HMScriptRunner::runResumeTestByID(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 2)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Acknowledges failed test item(s)
 * Params: <TestID>
 *         [StopAlerts]
 *         [<Comment>]
 *****************************************************************/
bool HMScriptRunner::runAckTestStatusbyID(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 3)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * This command tells HostMonitor to clear "acknowledged" flag for specified test item(s)
 * Params: <TestID>
 *****************************************************************/
bool HMScriptRunner::runResetAcknowledgementsByID(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Similar to SetTestParam command, you just need to specify unique ID of the test instead of test name
 * Params: <TestID>
 *         <ParameterName>
 *         <Value>
 *****************************************************************/
bool HMScriptRunner::runSetTestParamByID(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 3)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Similar to ReplaceTestParam command, you just need to specify unique ID of the test instead of test name
 * Params: <TestID>
 *         <ParameterName>
 *         <Curr. value>
 *         <New value>
 *****************************************************************/
bool HMScriptRunner::runReplaceTestParamByID(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 4)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Sets the value of a variable (if such variable does not exist, creates a new variable)
 * Params: <VariableName>
 *         <VariableValue>
 *****************************************************************/
bool HMScriptRunner::runSetUserVariable(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 2)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Saves changes
 *****************************************************************/
bool HMScriptRunner::runSaveUserVariables(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Loads previously saved variables
 *****************************************************************/
bool HMScriptRunner::runLoadUserVariables(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Tells HostMonitor to record into common log current test statuses of all test items except items that do not use common log
 * and items that already have recorded (today!) their status into common log
 *****************************************************************/
bool HMScriptRunner::runFlushCommonLog(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Similar to FlushCommonLog but performs the same operation for all test items that uses private log(s)
 * These 2 commands can be useful for Log Analyzer in case when you are using Brief logging mode and for some reasons you do not want to use Midnight logging mode
 * (e.g. you want to "flush" log records at noon instead of midnight or you want to "flush" log records for some specific private logs
 * or you want to "flush" log records twice a day)
 *****************************************************************/
bool HMScriptRunner::runFlushPrivateLogs(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Generate the report to the specified file using specified report profile
 * Params: "report profile name"
 *          <target file name>
 *****************************************************************/
bool HMScriptRunner::runCreateReport(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 2)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Starts external program and continue to execute the script (do not wait until external program will terminate)
 * Params: <CommandLine>
 *****************************************************************/
bool HMScriptRunner::runStartProgram(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Executes external program, waits until external program is terminated, and continues to execute the script.
 * If parameter <TimeToWait> is not equal to 0, HostMonitor will "kill" the external application when the application is not finished within the given timeout
 * (time defined in milliseconds). Be careful with this command, HostMonitor stops monitoring when executes external program by this command.
 * Params: <TimeToWait>
 *         <CommandLine>
 *****************************************************************/
bool HMScriptRunner::runExecuteProgram(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 2)) {
         return false;
     }
     m_Errors.append(tr("[WARNING] Line %1: Command '%2' is not implemented").arg(num).arg(cmdLine));
     return true;
}

/*****************************************************************
 * Enable alerts
 *****************************************************************/
bool HMScriptRunner::runEnableAlerts(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
         return false;
     }
     m_HML->cmdAlertsEnable();
     return true;
}

/*****************************************************************
 * Disable all alerts (except "scheduled" actions).
 * Note: if alerts are disabled then script can be launched manually (menu File->Execute script).
 * Also you may setup built-in Scheduler to execute actions even when alerts are disabled.
 *****************************************************************/
bool HMScriptRunner::runDisableAlerts(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
         return false;
     }
     m_HML->cmdAlertsDisable();
     return true;
}

/*****************************************************************
 * Pause alerts for interval specified in minutes. In other words, all action profiles
 * that usually were triggered by the change of test(s) status will not be executed within N minutes.
 * All scheduled actions (those that are executed by built-in Scheduler) will continue to execute anyway.
 * Params: <interval>
 *****************************************************************/
bool HMScriptRunner::runPauseAlerts(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
         return false;
    }

    cmdList.removeFirst(); // remove command

    if (!cmdList.count()) {
        m_Errors.append(tr("[ERROR] Line %1: Command '%2' has no interval\n").arg(num).arg(cmdLine));
        return false;
    }
    bool ok;
    int interval = cmdList.first().toInt(&ok);
    if (!ok) {
        m_Errors.append(tr("[ERROR] Line %1: In Command '%2' interval is not a number in minutes\n").arg(num).arg(cmdLine));
        return false;
    }

     m_HML->cmdAlertsPause(interval);
     return true;
}

/*****************************************************************
 * Pause monitoring for specified time (time should be specified in minutes)
 * Params: <interval>
 *****************************************************************/
bool HMScriptRunner::runPauseMonitor(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 1)) {
         return false;
    }
    cmdList.removeFirst(); // remove command

    if (!cmdList.count()) {
        m_Errors.append(tr("[ERROR] Line %1: Command '%2' has no interval\n").arg(num).arg(cmdLine));
        return false;
    }
    bool ok;
    int interval = cmdList.first().toInt(&ok);
    if (!ok) {
        m_Errors.append(tr("[ERROR] Line %1: In Command '%2' interval is not a number in minutes\n").arg(num).arg(cmdLine));
        return false;
    }

    m_HML->cmdMonitoringPause(interval);
    return true;
}

/*****************************************************************
 * Stop monitoring
 *****************************************************************/
bool HMScriptRunner::runStopMonitor(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
         return false;
     }
    m_HML->cmdMonitoringStop();
    return true;
}

/*****************************************************************
 * Start monitoring
 *****************************************************************/
bool HMScriptRunner::runStartMonitor(const int num, const QString &cmdLine)
{
    QStringList cmdList = parseCmd(cmdLine);
    if (!checkParams(num, cmdList, 0)) {
         return false;
    }
    m_HML->cmdMonitoringStart();
    return true;
}

/*****************************************************************
 * Quit HostMonitor
 *****************************************************************/
bool HMScriptRunner::runQuitMonitor(const int num, const QString &cmdLine)
{
    Q_UNUSED(num)
    Q_UNUSED(cmdLine)
    QCoreApplication::quit();
    return true;
}

/*****************************************************************/

} // namespace SDPO
