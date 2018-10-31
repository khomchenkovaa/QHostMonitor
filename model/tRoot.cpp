#include "tRoot.h"
#include "utils.h"

namespace SDPO {

/******************************************************************/

TRoot::TRoot(QObject *parent) :
    TNode(0, QString(),TNode::ROOT, parent)
{
    setup();
}

/******************************************************************/

TRoot::~TRoot()
{
    Utils::DestructorMsg(this);
    m_rootFolder->deleteLater();
    m_rootView->deleteLater();
}

/******************************************************************/

TNode *TRoot::findByPath(QString path)
{
    QStringList pathList = path.split(PATH_DELIMITER);
    TNode *node = this;
    foreach(QString str, pathList) {
        if (str == "") continue;
        node = node->findChild(str);
        if (!node) break;
    }
    return node;
}

/******************************************************************/

void TRoot::removeNode(TNode *item)
{
    if (item->getType() == TNode::ROOT) return;
    TNode* parent = item->parentNode();
    if (parent->getType() == TNode::ROOT) return;

    switch (item->getType()) {
    case TNode::FOLDER :
        if (item->testsCount() > 0) {
            while (item->testsCount() > 0) {
                removeNode(item->tests().at(item->testsCount()-1));
            }
        }
        //! TODO removeViews(item);
        while (item->childCount() > 0) {
            removeNode(item->lastChild());
        }
        break;
    case TNode::VIEW :
        break;
    case TNode::TEST :
        return removeTest(qobject_cast<TTest*>(item));
    case TNode::LINK :
        return removeLink(qobject_cast<TLink*>(item));
    default: break;
    }
    parent->removeChild(item);
}

/******************************************************************/

void TRoot::removeLink(QString path, TTest *test)
{
    TNode* parent = findByPath(path);
    TLink* link = parent->findLinkByTest(test);
    removeLink(link);
}

/******************************************************************/

void TRoot::removeLink(TNode *parent, TTest *test)
{
    TLink* link = parent->findLinkByTest(test);
    removeLink(link);
}

/******************************************************************/

void TRoot::removeLink(TLink *link)
{
    TNode* parent = link->parentNode();
    link->getTest()->removeLink(parent);
    emit delLink(link);
    parent->removeChild(link);
}

/******************************************************************/

void TRoot::removeTest(TTest *test)
{
    TNode* parent = test->parentNode();
    if (test->linkCount() == 0) {
        disconnect(test,SIGNAL(testDone(TNode*)),this,SIGNAL(testUpdated(TNode*)));
        disconnect(test,SIGNAL(readyRun(TNode*)),this,SIGNAL(readyRun(TNode*)));
        emit delTest(test);
        parent->removeChild(test);
    } else {
        TNode *newParent = test->links().at(0);
        removeLink(newParent, test);
        moveTest(newParent, test);
    }
}

/******************************************************************/

void TRoot::removeTestWithLinks(TTest *test)
{
    TNode* parent = test->parentNode();
    while (test->linkCount() > 0) {
        removeLink(test->links().at(test->linkCount()-1), test);
    }
    emit delTest(test);
    parent->removeChild(test);
}

/******************************************************************/

void TRoot::moveTest(TNode *newParent, TTest *test)
{
    emit cutTest(qobject_cast<TNode*>(test));
    test->parentNode()->tests().removeOne(test);
    newParent->tests().append(test);
    emit pasteTest(qobject_cast<TNode*>(test));
}

/******************************************************************/

void TRoot::removeViews(TNode *node)
{
    if (node->getType() != TNode::FOLDER) return;
    TFolder *folder = qobject_cast<TFolder*>(node);
    QList<TView*> toDelete;
    foreach(TNode *item, rootView()->folders()) {
        if (item->getType() != TNode::VIEW) continue;
        TView *view = qobject_cast<TView*>(item);
        if (view->getSourceFolder() == folder || view->getSourceFolder()->isChildOf(node)) {
            toDelete.append(view);
        }
    }
    foreach(TView *item, toDelete) {
        removeNode(item);
    }
}

/******************************************************************/

void TRoot::setup()
{
    // Folders
    m_rootFolder = new TFolder(1,QString(ROOT_FOLDER_NAME));
    appendChild(m_rootFolder);
    m_rootFolder->setUseOwnRegionalSettings(true);
    m_rootFolder->setTimeZoneIanaId("UTC");
    // Views
    m_rootView = new TFolder(2,QString(ROOT_VIEW_NAME));
    appendChild(m_rootView);
}

/******************************************************************/

} // namespace SDPO
