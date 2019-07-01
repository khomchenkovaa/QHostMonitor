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
    m_CurFolder = nullptr;
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
    //! TODO implement method cmdAppendTestList
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
    //! TODO implement method cmdSetFolderVariable
    qDebug() << "TODO: cmdSetFolderVariable" << folder->getName() << varName << varValue << inheritPartly;
    return true;
}

/******************************************************************/

bool HMListService::cmdSetFolderAgent(TNode *folder, QString agentName, bool unlessInherited)
{
    //! TODO implement method cmdSetFolderAgent
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
    //! TODO implement method cmdCopyFolder
    qDebug() << "TODO: cmdCopyFolder" << folder->getName() << folder2->getName() << r;
    return true;
}

/******************************************************************/

TNode *HMListService::cmdCopyTest(TNode *destFolder, QString name, TNode *test, bool skipDuplicates)
{
    if (destFolder->findTest(name)) {
        if (skipDuplicates) return nullptr;
        name = name.append("-copy");
        return cmdCopyTest(destFolder, name, test, skipDuplicates);
    }
    TTest *srcTest = qobject_cast<TTest*>(test);
    TTest *newTest = srcTest->clone(nextID(), name);
    addNode(destFolder, newTest);
    return newTest;
}

/******************************************************************/

bool HMListService::cmdDisableTest(QString testName)
{
    //! TODO implemet method cmdDisableTest
    qDebug() << "TODO: cmdDisableTest" << testName;
    return true;
}

/******************************************************************/

bool HMListService::cmdEnableTest(QString testName)
{
    //! TODO implemet method cmdEnableTest
    qDebug() << "TODO: cmdEnableTest" << testName;
    return true;
}

/******************************************************************/

bool HMListService::cmdRefreshTest(QString testName)
{
    //! TODO implemet method cmdRefreshTest
    qDebug() << "TODO: cmdRefreshTest" << testName;
    return true;
}

/******************************************************************/

bool HMListService::cmdResetTest(QString testName)
{
    //! TODO implemet method cmdResetTest
    qDebug() << "TODO: cmdResetTest" << testName;
    return true;
}

/******************************************************************/

bool HMListService::cmdPauseTest(QString testName, int interval, QString comment)
{
    //! TODO implemet method cmdPauseTest
    qDebug() << "TODO: cmdPauseTest" << testName << interval << comment;
    return true;
}

/******************************************************************/

bool HMListService::cmdResumeTest(QString testName)
{
    //! TODO implemet method cmdResumeTest
    qDebug() << "TODO: cmdResumeTest" << testName;
    return true;
}

/******************************************************************/

bool HMListService::cmdSetTestParam(QString testName, QString paramName, int value)
{
    //! TODO implemet method cmdSetTestParam
    qDebug() << "TODO: cmdSetTestParam" << testName << paramName << value;
    return true;
}

/******************************************************************/

bool HMListService::cmdReplaceTestParam(QString testName, QString paramName, int curValue, int newValue)
{
    //! TODO implemet method cmdReplaceTestParam
    qDebug() << "TODO: cmdReplaceTestParam" << testName << paramName << curValue << newValue;
    return true;
}

/******************************************************************/

bool HMListService::cmdAckTestStatus(QString fileName, QString StopAlerts, QString Comment)
{
    //! TODO implemet method cmdAckTestStatus
    qDebug() << "TODO: cmdAckTestStatus" << fileName << StopAlerts << Comment;
    return true;
}

/******************************************************************/

bool HMListService::cmdResetAcknowledgements(QString fileName)
{
    //! TODO implemet method cmdResetAcknowledgements
    qDebug() << "TODO: cmdResetAcknowledgements" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdResetRecurrencesTest(QString fileName)
{
    //! TODO implemet method cmdResetRecurrencesTest
    qDebug() << "TODO: cmdResetRecurrencesTest" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdResetEventLogRefPoint(QString fileName)
{
    //! TODO implemet method cmdResetEventLogRefPoint
    qDebug() << "TODO: cmdResetEventLogRefPoint" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdDisableTestByID(TNode* fileName)
{
    //! TODO implemet method cmdDisableTestByID
    qDebug() << "TODO: cmdDisableTestByID" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdEnableTestByID(TNode* fileName)
{
    //! TODO implemet method cmdEnableTestByID
    qDebug() << "TODO: cmdEnableTestByID" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdRefreshTestByID(TNode* fileName, QString forcelog)
{
    //! TODO implemet method cmdRefreshTestByID
    qDebug() << "TODO: cmdResfreshTestByID" << fileName << forcelog;
    return true;
}

/******************************************************************/

bool HMListService::cmdRefreshIrregularTestByID(TNode* fileName, QString forcelog)
{
    //! TODO implemet method cmdRefreshIrregularTestByID
    qDebug() << "TODO: cmdResfreshIrregularTestByID" << fileName << forcelog;
    return true;
}

/******************************************************************/

bool HMListService::cmdResetTestByID(TNode* fileName)
{
    //! TODO implemet method cmdResetTestByID
    qDebug() << "TODO: cmdResetTestByID" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdPauseTestByID(TNode* fileName, int inteval_minutes)
{
    //! TODO implemet method cmdPauseTestByID
    qDebug() << "TODO: cmdPauseTestByID" << fileName << inteval_minutes;
    return true;
}

/******************************************************************/

bool HMListService::cmdResumeTestByID(TNode* fileName, int inteval_minutes)
{
    //! TODO implemet method cmdResumeTestByID
    qDebug() << "TODO: cmdResumeTestByID" << fileName << inteval_minutes;
    return true;
}

/******************************************************************/

bool HMListService::cmdAckTestStatusbyID(TNode* fileName, QString StopAlerts, QString Comment)
{
    //! TODO implemet method cmdAckTestStatusbyID
    qDebug() << "TODO: cmdAckTestStatusbyID" << fileName << StopAlerts << Comment;
    return true;
}

/******************************************************************/

bool HMListService::cmdResetAcknowledgementsByID(TNode* fileName)
{
    //! TODO implemet method cmdResetAcknowledgementsByID
    qDebug() << "TODO: cmdResetAcknowledgementsByID" << fileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdSetTestParamByID(TNode* fileName, QString ParameterName, int Value)
{
    //! TODO implemet method cmdSetTestParamByID
    qDebug() << "TODO: cmdSetTestParamByID" << fileName << ParameterName << Value;
    return true;
}

/******************************************************************/

bool HMListService::cmdReplaceTestParamByID(TNode* fileName, QString ParameterName, int CurrValue, int NewValue)
{
    //! TODO implemet method cmdReplaceTestParamByID
    qDebug() << "TODO: cmdReplaceTestParamByID" << fileName << ParameterName << CurrValue << NewValue;
    return true;
}

/******************************************************************/

bool HMListService::cmdSetUserVariable(QString varName, QString varValue)
{
    //! TODO implemet method cmdSetUserVariable
    qDebug() << "TODO: cmdSetUserVariable" << varName << varValue;
    return true;
}

/******************************************************************/

bool HMListService::cmdCreateReport(QString reportProfileName, QString targetFileName)
{
    //! TODO implemet method cmdCreateReport
    qDebug() << "TODO: cmdCreateReport" << reportProfileName << targetFileName;
    return true;
}

/******************************************************************/

bool HMListService::cmdStartProgram(QString cmdLine)
{
    //! TODO implemet method cmdStartProgram
    qDebug() << "TODO: cmdStartProgram" << cmdLine;
    return true;
}

/******************************************************************/

bool HMListService::cmdExecuteProgram(int timeToWait, QString cmdLine)
{
    //! TODO implemet method cmdExecuteProgram
    qDebug() << "TODO: cmdExecuteProgram" << timeToWait << cmdLine;
    return true;
}

/******************************************************************/

} // namespace SDPO
