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
    case TNode::VIEW :
        //! TODO fill view
        emit viewAdded(item);
        break;
    case TNode::TEST :
        //! TODO update views
        connect(item,SIGNAL(readyRun(TNode*)),this,SIGNAL(readyRun(TNode*)));
        connect(item,SIGNAL(testDone(TNode*)),m_Root,SIGNAL(testUpdated(TNode*)));
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

bool HMListService::cmdSetFolderVariable(TNode *folder, QString varName, QString varValue, bool inheritPartly)
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
    Q_UNUSED(interval);
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
    Q_UNUSED(interval);
}

/******************************************************************/

} // namespace SDPO
