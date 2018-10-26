#ifndef IOHMLIST_H
#define IOHMLIST_H

#include "tEnums.h"
#include "method/sdpoTestMethodConverters.h"

#include <QPair>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>

#define DT_FORMAT "yyyy.MM.dd HH:mm:ss"

// main sections
#define SCT_HEAD       "head"
#define SCT_ROOT       "root"
#define SCT_RVIEW      "rview"
#define SCT_FOLDERS    "folders"
#define SCT_VIEWS      "views"
#define SCT_TESTS      "tests"
#define SCT_HISTORY    "history"
#define PRM_CUR_FOLDER "CurrentFolder"

// head
#define PRM_GUID          "GUID"
#define PRM_CNT           "count"
#define PRM_STORE_HISTORY "StoreHistory"

// folders and views sections
#define FVS_COLUMNS  "columns"
#define FVS_COLORS   "colors"
#define FVS_REPORTS  "reports"
#define FVS_STAT     "statistics"
#define FVS_REGIONAL "regional"
#define FVS_VARS     "variables"
#define FVS_SPECIALS "specials"
#define FVS_CRITERIA "criteria"

// columns
#define GRP_FIELDS  "fields"
#define GRP_SORT    "sortBy"
#define PRM_MACRO   "macro"
#define PRM_CHECK   "check"
#define PRM_COLUMN  "column"
#define PRM_ASC     "asc"

// colors
#define PRM_SCHEME  "scheme"

// regional
#define PRM_GUI        "gui"
#define PRM_SCHEDULERS "schedulers"
#define PRM_TIMEZONE   "timezone"

// specials
#define PRM_AFFECT_TRAY_ICON "TestStatusesNotAffectTrayIcon"
#define PRM_NON_SIMUL_EXEC   "NonSimultaneouslyTestExecution"

// view criteria


namespace SDPO {

class HMListService;
class TNode;
class TFolder;
class TView;

class IOHMList : public QObject
{
    Q_OBJECT

    HMListService *m_HML;

    QString m_fileName;

public:
    explicit IOHMList(HMListService *hml, QString fileName, QObject *parent = 0);
    ~IOHMList();

    bool load();
    bool save();

signals:
    void notifyStatusMessage(QString msg);

private:
    QPair<QJsonDocument, QJsonParseError> getJsonDocument(const QString &raw_json);
    QString    readJsonFile();
    bool       writeJsonToFile(QFile &outFile, const QString &outJson);
    void       sendErrorMessage(const QString &msg);

    QJsonDocument createJsonDocument();
    bool       parseJsonDocument(QJsonDocument jsonDocument);

    QJsonValue createHeadSection();
    void       parseHeadSection(QJsonValue jsonValue);

    QJsonValue createRootFolderSection();
    void       parseRootFolderSection(QJsonValue jsonValue);

    QJsonValue createRootViewSection();
    void       parseRootViewSection(QJsonValue jsonValue);

    QJsonValue createFoldersSection();
    void       parseFoldersSection(QJsonValue jsonValue);

    QJsonValue createViewsSection();
    void       parseViewsSection(QJsonValue jsonValue);

    QJsonValue createTestsSection(const bool storeStatistics, const bool storeIterations);
    void       parseTestsSection(QJsonValue jsonValue);

    QJsonValue createHistorySection();
    void       parseHistorySection(QJsonValue jsonValue);

    QJsonValue createColumnsSettings(TNode* node);
    void       parseColumnSettings(QJsonValue jsonValue, TNode* node);

    QJsonValue createColorSettings(TNode* node);
    void       parseColorSettings(QJsonValue jsonValue, TNode* node);

    QJsonValue createReportSettings(TNode* node);
    void       parseReportSettings(QJsonValue jsonValue, TNode* node);

    QJsonValue createStatSettings(TFolder *node);
    void       parseStatSettings(QJsonValue jsonValue, SDPO::TFolder *node);

    QJsonValue createRegionalSettings(TFolder *node);
    void       parseRegionalSettings(QJsonValue jsonValue, SDPO::TFolder *node);

    QJsonValue createVarsSettings(TFolder *node);
    void       parseVarsSettings(QJsonValue jsonValue, SDPO::TFolder *node);

    QJsonValue createSpecialsSettings(TFolder *node);
    void       parseSpecialsSettings(QJsonValue jsonValue, SDPO::TFolder *node);

    QJsonValue createViewCriteriaSettings(TView* view);
    void       parseViewCriteriaSettings(QJsonValue jsonValue, TView* view);
};

} // namespace SDPO

#endif // IOHMLIST_H
