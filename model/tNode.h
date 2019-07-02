#ifndef TNODE_H
#define TNODE_H

#include "PropertyHelper.h"
#include "global/gProfiles.h"
#include "global/tMethod.h"

#include <QVariant>
#include <QDateTime>

#define PATH_DELIMITER "/"

namespace SDPO {

class TLink;
class TTest;

static QString ROOT_FOLDER_NAME = QStringLiteral("Root");
static QString ROOT_VIEW_NAME = QStringLiteral("Views");

class TNode : public QObject
{
    Q_OBJECT

public: // Enums
    enum NodeType { ROOT, FOLDER, VIEW, LINK, TEST };
    Q_ENUM(NodeType)

    explicit TNode(const int id, const QString &name, const NodeType type, QObject *parent = nullptr);
    ~TNode();

signals:
    void readyRun(TNode*);
    void testDone(TNode*);

protected:    // properties
    int       m_ID;
    QString   m_Name;
    NodeType  m_Type;
    QString   m_Path;
    QString   m_Comment;
    QDateTime m_CreatedAt;
    QDateTime m_ModifiedAt;

public:       // properties
    int       getID() const { return m_ID; }
    void      setID(const int value) { m_ID = value; }
    QString   getName() const { return m_Name; }
    void      setName(const QString value) { m_Name = value; }
    NodeType  getType() const { return m_Type; }
    void      setType(const NodeType value) { m_Type = value; }
    QString   getPath() const { return m_Path; }
    QString   getComment() const { return m_Comment; }
    QString   getCommentLine(int line) const;
    void      setComment(const QString value) { m_Comment = value; }
    QDateTime getCreatedAt() const { return m_CreatedAt; }
    void      setCreatedAt(const QDateTime value) { m_CreatedAt = value; }
    QDateTime getModifiedAt() const { return m_ModifiedAt; }
    void      setModifiedAt(const QDateTime value) { m_ModifiedAt = value; }

protected: // node structure
    TNode *m_parentNode;
    QList<TNode*> m_childNodes; // Folders and Views
    QList<TNode*> m_childTests; // Tests and Links

public: // node structure
    void appendChild(TNode *child);
    void removeChild(TNode *child);
    void clearTests();
    void clearAll();
    QList<TNode*> folders() { return m_childNodes; }
    QList<TNode*> foldersRecursive();
    QList<TNode*> tests() { return m_childTests; }
    TNode *child(int idx, bool withTests = false);
    TNode *test(int idx);
    TNode *lastChild();
    TNode *findChild(QString nm);
    TNode *findChildRecursive(QString nm);
    TNode *findByID(int id);
    TNode *findTest(QString nm);
    TNode *testByID(int id);
    QList<TNode*> testsByStatus(SimpleStatusID id, bool recurcive = false);
    QList<TNode*> testsByMethod(TMethodID id, bool recurcive = false);
    int childCount(bool withTests = false) const;
    int foldersTotal() const;
    int viewsTotal() const;
    int testsCount() const;
    bool hasTests() const;
    bool isChildOf(TNode *node);
    TLink *findLinkByTest(TTest* test);
    int row(bool withTests = false) const;
    TNode *parentNode();
    TNode *getRoot();

    virtual QVariant property(QString name) const;
    virtual QVariant getGlobal(Macro::Variable globalVar) const;

protected: // interface settings
    // columns
    bool b_UseOwnColumnSettings;
    QColumnList m_columns;
    QSortPairList m_sort;
    // colors
    bool b_UseOwnColorSettings;
    QString m_ColorScheme;
    bool b_CheckingColorStatus;
    // reports
    bool b_UseOwnReportSettings;
    //! TODO implement ReportSettings

public: // interface settings
    bool isUseOwnColumnSettings() const { return b_UseOwnColumnSettings; }
    void setUseOwnColumnSettings(const bool value) { b_UseOwnColumnSettings = value; }
    QColumnList getColumns();
    void setColumns(QColumnList columns);
    QSortPairList getSort();
    void setSort(QSortPairList sort);
    bool isRootFolder();
    bool isUseOwnColorSettings() const { return b_UseOwnColorSettings; }
    void setUseOwnColorSettings(const bool value) { b_UseOwnColorSettings = value; }
    QString getColorScheme() const;
    void setColorScheme(const QString& value);
    bool isCheckingColorStatus() const { return b_CheckingColorStatus; }
    void setCheckingColorStatus(const bool value) { b_CheckingColorStatus = value; }
    bool isUseOwnReportSettings() const { return b_UseOwnReportSettings; }
    void setUseOwnReportSettings(const bool value) { b_UseOwnReportSettings = value; }
};

} // namespace SDPO

#endif // TNODE_H
