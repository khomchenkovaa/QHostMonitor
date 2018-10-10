#ifndef HMLISTSERVICE_H
#define HMLISTSERVICE_H

#include <QObject>
#include <QUuid>

#include "tRoot.h"

namespace SDPO {

class HMListService : public QObject
{
    Q_OBJECT

    TRoot*  m_Root;
    QUuid   m_GUID;
    bool    m_Modified;
    QString m_FileName;
    int     m_FileSize;
    bool    m_StoreHistoricalData;

public:
    explicit HMListService(QObject *parent = 0);
    ~HMListService();

    // getters and setters
    QUuid guid() const { return m_GUID; }
    bool isModelModified() const { return m_Modified; }
    QString currentFileName() const { return m_FileName; }
    void setFileName(const QString &value) { m_FileName = value; }
    int fileSize() const { return m_FileSize; }
    bool isStoreHistoricalData() const { return m_StoreHistoricalData; }
    void setStoreHistoricalData(const bool value) { m_StoreHistoricalData=value; }

    // test list properties
    bool isCurFileExists() const { return !m_FileName.isEmpty(); }
    TRoot *rootItem() { return m_Root; }
    TNode *rootFolder() { return m_Root->rootFolder(); }
    TNode *rootView() { return m_Root->rootView(); }
    TNode *nodeByPath(QString path) { return m_Root->findByPath(path); }

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
    bool cmdSetFolderVariable(TNode* folder, QString varName, QString varValue, bool inheritPartly = false); //! TODO
    bool cmdSetFolderAgent(TNode* folder, QString agentName, bool unlessInherited = false);                  //! TODO

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
    void alertsEnabled(bool value);

public slots:
    void cmdAlertsEnable();
    void cmdAlertsDisable();
    void cmdMonitoringStart();
    void cmdMonitoringStop();

};

} // namespace SDPO

#endif // HMLISTSERVICE_H
