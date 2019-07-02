#ifndef TROOT_H
#define TROOT_H

#include "tFolder.h"
#include "tView.h"
#include "tLink.h"
#include "tTest.h"

namespace SDPO {

class TRoot : public TNode
{
    Q_OBJECT

    TFolder *m_rootFolder;
    TFolder *m_rootView;

public:
    explicit TRoot(QObject *parent = nullptr);
    ~TRoot();

    // test list properties
    TNode *rootFolder() { return findChild(ROOT_FOLDER_NAME); }
    TNode *rootView() { return findChild(ROOT_VIEW_NAME); }
    TNode *findByPath(QString path);
    int foldersCnt() { return m_rootFolder->foldersTotal(); }
    int viewsCnt() { return m_rootView->viewsTotal(); }
    int testsCnt() { return m_rootFolder->testsTotal(); }
    int totalCnt() { return foldersCnt() + viewsCnt() + testsCnt(); }

signals:
    void newView(QString name);
    void newTest(TNode *test);
    void newLink(TNode *link);
    void delView(TNode *view);
    void delTest(TNode *test); //! TODO delTest signal usage
    void delLink(TNode *link); //! TODO delLink signal usage
    void cutTest(TNode *test);
    void pasteTest(TNode *test);

public slots:
    void removeNode(TNode* item);
    void removeLink(QString path, TTest* test);
    void removeLink(TNode *parent, TTest* test);
    void removeLink(TLink *link);
    void removeTest(TTest *test);
    void removeTestWithLinks(TTest *test);
    void moveTest(TNode *newParent, TTest* test);
    void removeViews(TNode *node);

private:
    void setup();

};

} // namespace SDPO

#endif // TROOT_H
