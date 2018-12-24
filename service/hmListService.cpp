#include "hmListService.h"
#include "io/ioTextFile.h"
#include "io/ioHMList.h"

#include <QDebug>

namespace SDPO {

/******************************************************************/

HMListService::HMListService(QObject *parent) :
    QObject(parent),
    m_Root(new TRoot()),
    m_CurFolder(m_Root->rootFolder())
{
}

/******************************************************************/

HMListService::~HMListService()
{
    Utils::DestructorMsg(this);
    m_CurFolder = 0;
    m_Root->deleteLater();
}

/******************************************************************/

void HMListService::addNode(TNode *parent, TNode *item)
{
    if (item->getType() == TNode::ROOT) return;
    parent->appendChild(item);
    switch (item->getType()) {
    case TNode::FOLDER :
        emit folderAdded(item);
        break;
    case TNode::VIEW : {
        //! TODO fill view
            TView *view = qobject_cast<TView*>(item);
            connect(this, SIGNAL(testUpdated(TNode*)), view, SLOT(updateByCriteria(TNode*)));
        }
        emit viewAdded(item);
        break;
    case TNode::TEST :
        //! TODO update views
        connect(item,SIGNAL(readyRun(TNode*)),this,SIGNAL(readyRun(TNode*)));
        connect(item,SIGNAL(testDone(TNode*)),this,SIGNAL(testUpdated(TNode*)));
        emit testAdded(item);
        break;
    case TNode::LINK :
        emit linkAdded(item);
        break;
    default: break;
    }
    m_Info.modified = true;
}

/******************************************************************/

bool HMListService::cmdNewTestList()
{
    emit modelAboutToChange();
    delete m_Root;

    m_Root = new TRoot();
    m_CurFolder = m_Root->rootFolder();
    m_Info.clear();

    emit modelChanged();
    return true;
}

/******************************************************************/

bool HMListService::cmdLoadTestList(QString fileName)
{
    IOHMList loader(this,fileName);
    emit modelAboutToChange();

    delete m_Root;
    m_Root = new TRoot();

    bool result = loader.load();\
    if (result) {
        m_Info.fileName = fileName;
        m_Info.fileSize = QFile(fileName).size();
    }
    m_Info.modified = false;

    emit modelChanged();

    return result;
}

/******************************************************************/

bool HMListService::cmdAppendTestList(QString fileName)
{
    qDebug() << "TODO: cmdAppendTestList" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdImportFromFile(QString fileName, bool skipDuplicates, bool writeLog)
{
    Q_UNUSED(skipDuplicates)
    Q_UNUSED(writeLog)

    emit modelAboutToChange();

    IOTextFile importer(this, fileName);
    importer.importTextFile();

    emit modelChanged();
    return true;
}

/******************************************************************/

bool HMListService::cmdSaveTestList(QString fileName)
{
    if (fileName.isEmpty()) {
        fileName = m_Info.fileName;
    }
    if (fileName.isEmpty()) {
        return false;
    }
    IOHMList saver(this, fileName);
    bool result = saver.save();
    if (result) {
        m_Info.fileName = fileName;
        m_Info.fileSize = QFile(fileName).size();
        m_Info.modified = false;
    }

    return result;
}

/******************************************************************/

bool HMListService::cmdExportHmlIntoText(QString fileName, bool commentDestFolder, bool commentLinks)
{
    emit modelAboutToChange();

    IOTextFile exporter(this, fileName);
    exporter.exportTextFile(!commentDestFolder, !commentLinks, true);

    emit modelChanged();
    return true;
}

/******************************************************************/

TNode *HMListService::cmdCreateFolder(QString path)
{
    TNode *node = m_Root->rootFolder();
    bool rootSkiped = false;
    QStringList pathList = path.split("/");
    foreach (const QString &folderName, pathList) {
        if (folderName.isEmpty()) continue; // may be last
        if (!rootSkiped &&
                node == m_Root->rootFolder() &&
                folderName.compare("Root",Qt::CaseInsensitive) == 0 )  { // No Root names
            rootSkiped = true;
            continue;
        }
        TNode *tmpNode = node->findChild(folderName);
        if (!tmpNode) {
            tmpNode = new TFolder(nextID(),folderName);
            addNode(node,tmpNode);
        }
        node = tmpNode;
    }
    return node;
}

/******************************************************************/

bool HMListService::cmdSetFolderVariable(TNode *folder, QString varName, int varValue, bool inheritPartly)
{
    qDebug() << "TODO: cmdSetFolderVariable" << folder->getName() << varName << varValue << inheritPartly;
    return true;
}

/******************************************************************/

bool HMListService::cmdSetFolderAgent(TNode *folder, QString agentName, bool unlessInherited)
{
    qDebug() << "TODO: cmdSetFolderAgent" << folder->getName() << agentName << unlessInherited;
    return true;
}

/******************************************************************/

void HMListService::cmdAlertsEnable()
{
    emit alertsEnabled(true);
}

/******************************************************************/

void HMListService::cmdAlertsDisable()
{
    emit alertsEnabled(false);
}

/******************************************************************/

void HMListService::cmdAlertsPause(int interval)
{
    emit alertsPaused(interval);
}

/******************************************************************/

void HMListService::cmdMonitoringStart()
{
    emit monitoringStarted(true);
}

/******************************************************************/

void HMListService::cmdMonitoringStop()
{
    emit monitoringStarted(false);
}

/******************************************************************/

void HMListService::cmdMonitoringPause(int interval)
{
    emit monitoringPaused(interval);
}

/******************************************************************/
bool HMListService::cmdCopyFolder(TNode *folder, TNode* folder2, bool r)
{
    qDebug() << "TODO: cmdCopyFolder" << folder->getName() << folder2->getName() << r;
    return true;
}

/******************************************************************/

bool HMListService::cmdCopyTest(TNode *folder, QString fileName)
{
    qDebug() << "TODO: cmdCopyTest" << folder->getName() << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdCopyTestByID(TNode *folder, TNode *testid)
{
    qDebug() << "TODO: cmdCopyTestByID" << folder->getName() << testid;
    return true;
}

/******************************************************************/

bool HMListService::cmdCopyAllTests(TNode *folder, bool r, bool skipduplicates)
{
    qDebug() << "TODO: cmdCopyAllTests" << folder->getName() << r << skipduplicates;
    return true;
}

/******************************************************************/

bool HMListService::cmdCopyIntoSelectedFolders(TNode *folder, QString fileName, bool skipduplicates)
{
    qDebug() << "TODO: cmdCopyIntoSelectedFolders" << folder->getName() << fileName << skipduplicates;
    return true;
}

/******************************************************************/

bool HMListService::cmdDisableTest(QString fileName)
{
    qDebug() << "TODO: cmdDisableTest" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdEnableTest(QString fileName)
{
    qDebug() << "TODO: cmdDisableTest" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdRefreshTest(QString fileName)
{
    qDebug() << "TODO: cmdDisableTest" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdResetTest(QString fileName)
{
    qDebug() << "TODO: cmdDisableTest" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdPauseTest(QString fileName, int interval, QString Comment)
{
    qDebug() << "TODO: cmdPauseTest" << fileName << interval << Comment;
    return true;
}

/******************************************************************/

bool HMListService::cmdResumeTest(QString fileName)
{
    qDebug() << "TODO: cmdResumeTest" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdSetTestParam(QString fileName, QString ParameterName, int Value)
{
    qDebug() << "TODO: cmdSetTestParam" << fileName << ParameterName << Value;
    return true;
}

/******************************************************************/

bool HMListService::cmdReplaceTestParam(QString fileName, QString ParameterName, int CurrValue, int NewValue)
{
    qDebug() << "TODO: cmdReplaceTestParam" << fileName << ParameterName << CurrValue << NewValue;
    return true;
}

/******************************************************************/

bool HMListService::cmdAckTestStatus(QString fileName, QString StopAlerts, QString Comment)
{
    qDebug() << "TODO: cmdAckTestStatus" << fileName << StopAlerts << Comment;
    return true;
}

/******************************************************************/

bool HMListService::cmdResetAcknowledgements(QString fileName)
{
    qDebug() << "TODO: cmdResetAcknowledgements" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdResetRecurrencesTest(QString fileName)
{
    qDebug() << "TODO: cmdResetRecurrencesTest" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdResetEventLogRefPoint(QString fileName)
{
    qDebug() << "TODO: cmdResetEventLogRefPoint" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdDisableTestByID(TNode* fileName)
{
    qDebug() << "TODO: cmdDisableTestByID" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdEnableTestByID(TNode* fileName)
{
    qDebug() << "TODO: cmdEnableTestByID" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdRefreshTestByID(TNode* fileName, QString forcelog)
{
    qDebug() << "TODO: cmdResfreshTestByID" << fileName << forcelog;
    return true;
}

/******************************************************************/

bool HMListService::cmdRefreshIrregularTestByID(TNode* fileName, QString forcelog)
{
    qDebug() << "TODO: cmdResfreshIrregularTestByID" << fileName << forcelog;
    return true;
}

/******************************************************************/

bool HMListService::cmdResetTestByID(TNode* fileName)
{
    qDebug() << "TODO: cmdResetTestByID" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdPauseTestByID(TNode* fileName, int inteval_minutes)
{
    qDebug() << "TODO: cmdPauseTestByID" << fileName << inteval_minutes;
    return true;
}

/******************************************************************/

bool HMListService::cmdResumeTestByID(TNode* fileName, int inteval_minutes)
{
    qDebug() << "TODO: cmdResumeTestByID" << fileName << inteval_minutes;
    return true;
}

/******************************************************************/

bool HMListService::cmdAckTestStatusbyID(TNode* fileName, QString StopAlerts, QString Comment)
{
    qDebug() << "TODO: cmdAckTestStatusbyID" << fileName << StopAlerts << Comment;
    return true;
}

/******************************************************************/

bool HMListService::cmdResetAcknowledgementsByID(TNode* fileName)
{
    qDebug() << "TODO: cmdResetAcknowledgementsByID" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdSetTestParamByID(TNode* fileName, QString ParameterName, int Value)
{
    qDebug() << "TODO: cmdSetTestParamByID" << fileName << ParameterName << Value;
    return true;
}

/******************************************************************/

bool HMListService::cmdReplaceTestParamByID(TNode* fileName, QString ParameterName, int CurrValue, int NewValue)
{
    qDebug() << "TODO: cmdReplaceTestParamByID" << fileName << ParameterName << CurrValue << NewValue;
    return true;
}

/******************************************************************/

bool HMListService::cmdSetUserVariable(TNode* VariableName, int VariableValue)
{
    qDebug() << "TODO: cmdSetUserVariable" << VariableName << VariableValue;
    return true;
}

/******************************************************************/

bool HMListService::cmdCreateReport(QString report_profile_name, QString target_file_name)
{
    qDebug() << "TODO: cmdCreateReport" << report_profile_name << target_file_name;
    return true;
}

/******************************************************************/

bool HMListService::cmdStartProgram(QString CommandLine)
{
    qDebug() << "TODO: cmdStartProgram" << CommandLine;
    return true;
}

/******************************************************************/

bool HMListService::cmdExecuteProgram(int TimeToWait, QString CommandLine)
{
    qDebug() << "TODO: cmdExecuteProgram" << TimeToWait << CommandLine;
    return true;
}

/******************************************************************/

} // namespace SDPO
