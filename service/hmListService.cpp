#include "hmListService.h"
#include "io/ioTextFile.h"

#include <QDebug>

namespace SDPO {

/******************************************************************/

HMListService::HMListService(QObject *parent) :
    QObject(parent),
    m_Root(new TRoot()),
    m_GUID(QUuid::createUuid()),
    m_Modified(false),
    m_FileName(QString()),
    m_FileSize(0),
    m_StoreHistoricalData(true)
{
}

/******************************************************************/

HMListService::~HMListService()
{
    Utils::DestructorMsg(this);
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
        connect(item,SIGNAL(readyRun(TNode*)),m_Root,SIGNAL(readyRun(TNode*)));
        connect(item,SIGNAL(testDone(TNode*)),m_Root,SIGNAL(testUpdated(TNode*)));
        emit testAdded(item);
        break;
    case TNode::LINK :
        emit linkAdded(item);
        break;
    default: break;
    }
}

/******************************************************************/

bool HMListService::cmdNewTestList()
{
    emit modelAboutToChange();
    delete m_Root;

    m_Root = new TRoot();
    m_GUID = QUuid::createUuid();
    m_Modified = false;
    m_FileName.clear();
    m_FileSize = 0;
    m_StoreHistoricalData = true;

    emit modelChanged();
    return true;
}

/******************************************************************/

bool HMListService::cmdLoadTestList(QString fileName)
{
    m_FileName = fileName;
    qDebug() << "TODO: cmdLoadTestList" << fileName;
    return true;
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
        fileName = m_FileName;
    }
    if (fileName.isEmpty()) {
        return false;
    }
    qDebug() << "TODO: cmdSaveTestList" << fileName;
    return true;
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
            tmpNode = new TFolder(folderName);
            addNode(node,tmpNode);
        }
        node = tmpNode;
    }
    return node;
}

/******************************************************************/

} // namespace SDPO
