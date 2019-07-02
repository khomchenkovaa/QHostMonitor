#include "ioHMList.h"

#include "utils.h"
#include "hmListService.h"
#include "gData.h"
#include "global/gProfiles.h"
#include "gSettings.h"
#include "ioHelper.h"

#include <QDebug>

namespace SDPO {

/******************************************************************/

IOHMList::IOHMList(HMListService *hml, QString fileName, QObject *parent) :
    QObject(parent),
    m_HML(hml),
    m_fileName(fileName)
{
}

/******************************************************************/

IOHMList::~IOHMList()
{
    Utils::DestructorMsg(this);
}

/******************************************************************/

bool IOHMList::load()
{
    QString rawJson = readJsonFile();
    if (rawJson.isEmpty()) return false;

    QPair<QJsonDocument, QJsonParseError> jsonResult = getJsonDocument(rawJson);
    QJsonParseError jsonError = jsonResult.second;
    if (jsonError.error != QJsonParseError::NoError) {
        QString msg = tr("Error parsing HML file at %1: %2").arg(jsonError.offset).arg(jsonError.errorString());
        sendErrorMessage(msg);
        return false;
    }
    QJsonDocument jsonDoc = jsonResult.first;
    return parseJsonDocument(jsonDoc);
}

/******************************************************************/

bool IOHMList::save()
{
    QJsonDocument jsonDocument = createJsonDocument();
    QFile outFile(m_fileName);
    return writeJsonToFile(outFile, QString(jsonDocument.toJson()));
}

/******************************************************************/

QPair<QJsonDocument, QJsonParseError> IOHMList::getJsonDocument(const QString &raw_json)
{
    QJsonParseError json_parse_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(raw_json.toUtf8(),&json_parse_error);
    return QPair<QJsonDocument, QJsonParseError>(json_doc, json_parse_error);
}

/******************************************************************/

QString IOHMList::readJsonFile()
{
    QFile stdFile(m_fileName);
    if (!stdFile.exists()) {
        sendErrorMessage(tr("File '%1' does not exists").arg(m_fileName));
        return QString();
    }
    if (!stdFile.open(QFile::ReadOnly|QFile::Text)) {
        sendErrorMessage(tr("Could not open '%1' to read").arg(m_fileName));
        return QString();
    }
    QString fileContent = stdFile.readAll();
    stdFile.close();
    return fileContent;
}

/******************************************************************/

bool IOHMList::writeJsonToFile(QFile &outFile, const QString &outJson)
{
    int length = outJson.length();
    if (!outFile.open(QFile::WriteOnly|QFile::Text)) {
        sendErrorMessage(tr("Could not open file '%1' to write").arg(outFile.fileName()));
        return false;
    }

    qint64 bytesWritten = outFile.write(qUtf8Printable(outJson),length);
    outFile.close();

    if (bytesWritten != length) {
        sendErrorMessage(tr("Could not write HMList to %1").arg(outFile.fileName()));
        if (!outFile.remove()) {
            sendErrorMessage(tr("Count not remove file %1. Please delete manualy").arg(outFile.fileName()));
        }
        return false;
    }
    return true;
}

/******************************************************************/

void IOHMList::sendErrorMessage(const QString &msg)
{
    qDebug() << msg;
    emit notifyStatusMessage(msg);
}

/******************************************************************/

QJsonDocument IOHMList::createJsonDocument()
{
    QSettings s;
    QJsonObject jsonObj;
    // Head
    jsonObj.insert(SCT_HEAD, createHeadSection());

    // Root
    jsonObj.insert(SCT_ROOT, createRootFolderSection());
    jsonObj.insert(SCT_RVIEW, createRootViewSection());

    // Folders and Views
    jsonObj.insert(SCT_FOLDERS, createFoldersSection());
    jsonObj.insert(SCT_VIEWS, createViewsSection());

    // Tests and Links
    bool storeStatistics = (s.value(SKEY_MISC_StoreStatistics, 1).toInt()==1);
    bool storeIterations = (s.value(SKEY_MISC_StoreIterations, 1).toInt()==1);
    jsonObj.insert(SCT_TESTS, createTestsSection(storeStatistics, storeIterations));

    // History
    if (m_HML->isStoreHistoricalData()) {
        jsonObj.insert(SCT_HISTORY, createHistorySection());
    }

    // Current Folder
    if (s.value(SKEY_INTERFACE_SaveCurrFolder, 1).toInt()) {
        jsonObj.insert(PRM_CUR_FOLDER, QJsonValue(m_HML->currentFolder()->getPath()));
    }

    return QJsonDocument(jsonObj);
}

/******************************************************************/

bool IOHMList::parseJsonDocument(QJsonDocument jsonDocument)
{
    QJsonObject jsonObj = jsonDocument.object();
    // Head
    parseHeadSection(jsonObj.value(SCT_HEAD));

    // root
    parseRootFolderSection(jsonObj.value(SCT_ROOT));
    parseRootViewSection(jsonObj.value(SCT_RVIEW));

    // Folders and vies
    parseFoldersSection(jsonObj.value(SCT_FOLDERS));
    parseViewsSection(jsonObj.value(SCT_VIEWS));

    // Tests
    parseTestsSection(jsonObj.value(SCT_TESTS));

    // History
    if (jsonObj.contains(SCT_HISTORY)) {
        parseHistorySection(jsonObj.value(SCT_HISTORY));
    }

    // CurrentFolder
    if (jsonObj.contains(PRM_CUR_FOLDER)) {
        QString path = jsonObj.value(PRM_CUR_FOLDER).toString();
        TNode *node = m_HML->nodeByPath(path);
        if (node->getType() != TNode::FOLDER) {
            node = m_HML->rootFolder();
        }
        m_HML->setCurrentFolder(node);
    }

    return true;
}

/******************************************************************/

QJsonValue IOHMList::createHeadSection()
{
    QJsonObject result;
    HMListInfo hmInfo = m_HML->info();
    result.insert(PRM_GUID, QJsonValue(hmInfo.guid.toString()));
    result.insert(PRM_CNT, QJsonValue(hmInfo.count));
    result.insert(PRM_STORE_HISTORY, QJsonValue(hmInfo.storeHistoricalData));
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseHeadSection(QJsonValue jsonValue)
{
    QJsonObject jsonObj = jsonValue.toObject();
    HMListInfo hmInfo = m_HML->info();
    hmInfo.guid = QUuid(jsonObj.value(PRM_GUID).toString());
    hmInfo.count = jsonObj.value(PRM_CNT).toInt();
    hmInfo.storeHistoricalData = jsonObj.value(PRM_STORE_HISTORY).toBool();
    m_HML->setInfo(hmInfo);
}

/******************************************************************/

QJsonValue IOHMList::createRootFolderSection()
{
    QJsonObject jsonObj;
    TFolder *fld = qobject_cast<TFolder*>(m_HML->rootFolder());
    // columns
    if (fld->isUseOwnColumnSettings()) {
        jsonObj.insert(FVS_COLUMNS, createColumnsSettings(fld));
    }

    // folder colors
    if (fld->isUseOwnColorSettings()) {
        jsonObj.insert(FVS_COLORS, createColorSettings(fld));
    }

    // reports
    if (fld->isUseOwnReportSettings()) {
        jsonObj.insert(FVS_REPORTS, createReportSettings(fld));
    }

    // statistics
    if (fld->isUseOwnStatSettings()) {
        jsonObj.insert(FVS_STAT, createStatSettings(fld));
    }

    // regional
    if (fld->isUseOwnRegionalSettings()) {
        jsonObj.insert(FVS_REGIONAL, createRegionalSettings(fld));
    }

    // comment
    if (!fld->getComment().isEmpty()) {
        jsonObj.insert(PRM_COMMENT, QJsonValue(fld->getComment()));
    }

    // variables
    jsonObj.insert(FVS_VARS, createVarsSettings(fld));

    // specials
    jsonObj.insert(FVS_SPECIALS, createSpecialsSettings(fld));

    return QJsonValue(jsonObj);
}

/******************************************************************/

void IOHMList::parseRootFolderSection(QJsonValue jsonValue)
{
    QJsonObject jsonObj = jsonValue.toObject();
    TFolder *fld = qobject_cast<TFolder*>(m_HML->rootFolder());

    // columns
    fld->setUseOwnColumnSettings(jsonObj.contains(FVS_COLUMNS));
    if (fld->isUseOwnColumnSettings()) {
        parseColumnSettings(jsonObj.value(FVS_COLUMNS),fld);
    }

    // folder colors
    fld->setUseOwnColorSettings(jsonObj.contains(FVS_COLORS));
    if (fld->isUseOwnColorSettings()) {
        parseColorSettings(jsonObj.value(FVS_COLORS),fld);
    }

    // reports
    fld->setUseOwnReportSettings(jsonObj.contains(FVS_REPORTS));
    if (fld->isUseOwnReportSettings()) {
        parseReportSettings(jsonObj.value(FVS_REPORTS),fld);
    }

    // statistics
    fld->setUseOwnStatSettings(jsonObj.contains(FVS_STAT));
    if (fld->isUseOwnStatSettings()) {
        parseStatSettings(jsonObj.value(FVS_STAT),fld);
    }

    // regional
    fld->setUseOwnRegionalSettings(jsonObj.contains(FVS_REGIONAL));
    if (fld->isUseOwnRegionalSettings()) {
        parseRegionalSettings(jsonObj.value(FVS_REGIONAL),fld);
    }

    // comment
    fld->setComment(jsonObj.value(PRM_COMMENT).toString());

    // variables
    parseVarsSettings(jsonObj.value(FVS_VARS),fld);

    // specials
    parseSpecialsSettings(jsonObj.value(FVS_SPECIALS),fld);
}

/******************************************************************/

QJsonValue IOHMList::createRootViewSection()
{
    QJsonObject jsonObj;
    TFolder *fld = qobject_cast<TFolder*>(m_HML->rootView());

    // columns
    if (fld->isUseOwnColumnSettings()) {
        jsonObj.insert(FVS_COLUMNS, createColumnsSettings(fld));
    }

    // folder colors
    if (fld->isUseOwnColorSettings()) {
        jsonObj.insert(FVS_COLORS, createColorSettings(fld));
    }

    // comment
    if (!fld->getComment().isEmpty()) {
        jsonObj.insert(PRM_COMMENT, QJsonValue(fld->getComment()));
    }

    return QJsonValue(jsonObj);
}

/******************************************************************/

void IOHMList::parseRootViewSection(QJsonValue jsonValue)
{
    QJsonObject jsonObj = jsonValue.toObject();
    TFolder *fld = qobject_cast<TFolder*>(m_HML->rootView());

    // columns
    fld->setUseOwnColumnSettings(jsonObj.contains(FVS_COLUMNS));
    if (fld->isUseOwnColumnSettings()) {
        parseColumnSettings(jsonObj.value(FVS_COLUMNS),fld);
    }

    // folder colors
    fld->setUseOwnColorSettings(jsonObj.contains(FVS_COLORS));
    if (fld->isUseOwnColorSettings()) {
        parseColorSettings(jsonObj.value(FVS_COLORS),fld);
    }

    // comment
    fld->setComment(jsonObj.value(PRM_COMMENT).toString());
}

/******************************************************************/

QJsonValue IOHMList::createFoldersSection()
{
    QJsonArray result;
    TFolder *folder = qobject_cast<TFolder*>(m_HML->rootFolder());
    foreach(TNode *node, folder->folderList()) {
        TFolder *fld = qobject_cast<TFolder*>(node);
        QJsonObject jsonObj;
        // node
        jsonObj.insert(PRM_ID, QJsonValue(fld->getID()));
        jsonObj.insert(PRM_TITLE, QJsonValue(fld->getName()));
        jsonObj.insert(PRM_CREATED_AT, QJsonValue(fld->getCreatedAt().toString(DT_FORMAT)));
        jsonObj.insert(PRM_MODIFIED_AT, QJsonValue(fld->getModifiedAt().toString(DT_FORMAT)));
        jsonObj.insert(PRM_DEST_FOLDER, QJsonValue(fld->parentNode()->getPath()));

        // columns
        if (fld->isUseOwnColumnSettings()) {
            jsonObj.insert(FVS_COLUMNS, createColumnsSettings(fld));
        }

        // folder colors
        if (fld->isUseOwnColorSettings()) {
            jsonObj.insert(FVS_COLORS, createColorSettings(fld));
        }

        // reports
        if (fld->isUseOwnReportSettings()) {
            jsonObj.insert(FVS_REPORTS, createReportSettings(fld));
        }

        // statistics
        if (fld->isUseOwnStatSettings()) {
            jsonObj.insert(FVS_STAT, createStatSettings(fld));
        }

        // regional
        if (fld->isUseOwnRegionalSettings()) {
            jsonObj.insert(FVS_REGIONAL, createRegionalSettings(fld));
        }

        // comment
        if (!fld->getComment().isEmpty()) {
            jsonObj.insert(PRM_COMMENT, QJsonValue(fld->getComment()));
        }

        // variables
        jsonObj.insert(FVS_VARS, createVarsSettings(fld));

        // specials
        jsonObj.insert(FVS_SPECIALS, createSpecialsSettings(fld));

        result.append(jsonObj);
    }
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseFoldersSection(QJsonValue jsonValue)
{
    foreach(const QJsonValue &fldValue, jsonValue.toArray()) {
        QJsonObject jsonObj = fldValue.toObject();
        // node
        QString destFolder = jsonObj.value(PRM_DEST_FOLDER).toString();
        TNode *parent = m_HML->nodeByPath(destFolder);
        if (!parent || parent->getType() != TNode::FOLDER) {
            QString msg = tr("Can not find dest folder '%1'").arg(destFolder);
            sendErrorMessage(msg);
            // skip or create?
            continue;
        }
        int id = jsonObj.value(PRM_ID).toInt();
        QString name = jsonObj.value(PRM_TITLE).toString();
        TFolder *fld = new TFolder(id, name);
        m_HML->addNode(parent, fld);
        fld->setCreatedAt(QDateTime::fromString(jsonObj.value(PRM_CREATED_AT).toString(), DT_FORMAT));
        fld->setModifiedAt(QDateTime::fromString(jsonObj.value(PRM_MODIFIED_AT).toString(), DT_FORMAT));

        // columns
        fld->setUseOwnColumnSettings(jsonObj.contains(FVS_COLUMNS));
        if (fld->isUseOwnColumnSettings()) {
            parseColumnSettings(jsonObj.value(FVS_COLUMNS),fld);
        }

        // folder colors
        fld->setUseOwnColorSettings(jsonObj.contains(FVS_COLORS));
        if (fld->isUseOwnColorSettings()) {
            parseColorSettings(jsonObj.value(FVS_COLORS),fld);
        }

        // reports
        fld->setUseOwnReportSettings(jsonObj.contains(FVS_REPORTS));
        if (fld->isUseOwnReportSettings()) {
            parseReportSettings(jsonObj.value(FVS_REPORTS),fld);
        }

        // statistics
        fld->setUseOwnStatSettings(jsonObj.contains(FVS_STAT));
        if (fld->isUseOwnStatSettings()) {
            parseStatSettings(jsonObj.value(FVS_STAT),fld);
        }

        // regional
        fld->setUseOwnRegionalSettings(jsonObj.contains(FVS_REGIONAL));
        if (fld->isUseOwnRegionalSettings()) {
            parseRegionalSettings(jsonObj.value(FVS_REGIONAL),fld);
        }

        // comment
        fld->setComment(jsonObj.value(PRM_COMMENT).toString());

        // variables
        parseVarsSettings(jsonObj.value(FVS_VARS),fld);

        // specials
        parseSpecialsSettings(jsonObj.value(FVS_SPECIALS),fld);
    }
}

/******************************************************************/

QJsonValue IOHMList::createViewsSection()
{
    QJsonArray result;
    TFolder *folder = qobject_cast<TFolder*>(m_HML->rootView());
    foreach(TNode *node, folder->viewList()) {
        TView *view = qobject_cast<TView*>(node);
        QJsonObject jsonObj;
        // node
        jsonObj.insert(PRM_ID, QJsonValue(view->getID()));
        jsonObj.insert(PRM_TITLE, QJsonValue(view->getName()));
        jsonObj.insert(PRM_CREATED_AT, QJsonValue(view->getCreatedAt().toString(DT_FORMAT)));
        jsonObj.insert(PRM_MODIFIED_AT, QJsonValue(view->getModifiedAt().toString(DT_FORMAT)));

        // source
        jsonObj.insert(PRM_SOURCE_FLD, QJsonValue(view->getSourceFolder()->getPath()));
        jsonObj.insert(PRM_SOURCE_RECURSIVE, QJsonValue(view->isRecursive()));

        // view criteria
        jsonObj.insert(FVS_CRITERIA, createViewCriteriaSettings(view));

        // columns
        if (view->isUseOwnColumnSettings()) {
            jsonObj.insert(FVS_COLUMNS, createColumnsSettings(view));
        }

        // colors
        if (view->isUseOwnColorSettings()) {
            jsonObj.insert(FVS_COLORS, createColorSettings(view));
        }

        // reports
        if (view->isUseOwnReportSettings()) {
            jsonObj.insert(FVS_REPORTS, createReportSettings(view));
        }

        // comment
        if (!view->getComment().isEmpty()) {
            jsonObj.insert(PRM_COMMENT, QJsonValue(view->getComment()));
        }

        result.append(jsonObj);
    }
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseViewsSection(QJsonValue jsonValue)
{
    TFolder *rootView = qobject_cast<TFolder*>(m_HML->rootView());
    foreach(const QJsonValue &fldValue, jsonValue.toArray()) {
        QJsonObject jsonObj = fldValue.toObject();
        // source
        QString srcFolder = jsonObj.value(PRM_SOURCE_FLD).toString();
        TNode *source = m_HML->nodeByPath(srcFolder);
        if (!source || source->getType() != TNode::FOLDER) {
            QString msg = tr("Can not find source folder '%1'").arg(srcFolder);
            sendErrorMessage(msg);
            source = m_HML->rootFolder();
        }
        bool recursive = jsonObj.value(PRM_SOURCE_RECURSIVE).toBool();

        // node
        int id = jsonObj.value(PRM_ID).toInt();
        QString name = jsonObj.value(PRM_TITLE).toString();
        TView *view = new TView(id, name,  qobject_cast<TFolder*>(source));
        m_HML->addNode(rootView, view);
        view->setCreatedAt(QDateTime::fromString(jsonObj.value(PRM_CREATED_AT).toString(), DT_FORMAT));
        view->setModifiedAt(QDateTime::fromString(jsonObj.value(PRM_MODIFIED_AT).toString(), DT_FORMAT));
        view->setRecursive(recursive);

        // view criteria
        parseViewCriteriaSettings(jsonObj.value(FVS_CRITERIA),view);

        // columns
        view->setUseOwnColumnSettings(jsonObj.contains(FVS_COLUMNS));
        if (view->isUseOwnColumnSettings()) {
            parseColumnSettings(jsonObj.value(FVS_COLUMNS),view);
        }

        // colors
        view->setUseOwnColorSettings(jsonObj.contains(FVS_COLORS));
        if (view->isUseOwnColorSettings()) {
            parseColorSettings(jsonObj.value(FVS_COLORS),view);
        }

        // reports
        view->setUseOwnReportSettings(jsonObj.contains(FVS_REPORTS));
        if (view->isUseOwnReportSettings()) {
            parseReportSettings(jsonObj.value(FVS_REPORTS),view);
        }

        // comment
        view->setComment(jsonObj.value(PRM_COMMENT).toString());
    }
}

/******************************************************************/

QJsonValue IOHMList::createTestsSection(const bool storeStatistics, const bool storeIterations)
{
    QJsonArray result;
    TFolder *folder = qobject_cast<TFolder*>(m_HML->rootFolder());
    int scheduleModeIdx = TSchedule::staticMetaObject.indexOfEnumerator("ScheduleMode");
    QMetaEnum scheduleModeEnum = TSchedule::staticMetaObject.enumerator(scheduleModeIdx);
    foreach(TNode *node, folder->testList()) {
        if (node->getType() != TNode::TEST) continue;
        TTest *test = qobject_cast<TTest*>(node);
        QJsonObject jsonObj;

        // node and test's main params
        jsonObj.insert(PRM_ID, QJsonValue(test->getID()));
        jsonObj.insert(PRM_TITLE, QJsonValue(test->getName()));
        jsonObj.insert(PRM_CREATED_AT, QJsonValue(test->getCreatedAt().toString(DT_FORMAT)));
        jsonObj.insert(PRM_MODIFIED_AT, QJsonValue(test->getModifiedAt().toString(DT_FORMAT)));
        jsonObj.insert(PRM_DEST_FOLDER, QJsonValue(test->parentNode()->getPath()));
        jsonObj.insert(PRM_COMMENT, QJsonValue(test->getComment()));
        jsonObj.insert(PRM_RM_AGENT, QJsonValue(test->agentName()));
        jsonObj.insert(PRM_RELATED_URL, QJsonValue(test->getRelatedURL()));

        // method specific parameters
        jsonObj.insert(TSP_SPECIFIC, createTestMethodSection(test));

        // properties
        jsonObj.insert("enabled", QJsonValue(test->isEnabled()));
        jsonObj.insert("paused", QJsonValue(test->isPaused()));
        jsonObj.insert("pauseComment", QJsonValue(test->getPauseComment()));

        // schedule
        TSchedule::ScheduleMode scheduleMode = test->schedule()->getMode();
        jsonObj.insert(PRM_SCHEDULE_MODE, QJsonValue(scheduleModeEnum.key(scheduleMode)));
        switch(scheduleMode) {
        case TSchedule::Regular :
            jsonObj.insert(PRM_INTERVAL, QJsonValue(test->interval()));
            jsonObj.insert(PRM_SCHEDULE, QJsonValue(test->scheduleName()));
            break;
        case TSchedule::OncePerDay :
            jsonObj.insert(PRM_SCHEDULE_TIME, QJsonValue(test->schedule()->getScheduleTime().toString(TIME_FORMAT)));
            break;
        case TSchedule::OncePerWeek :
        case TSchedule::OncePerMonth :
            jsonObj.insert(PRM_SCHEDULE_DAY, QJsonValue(test->schedule()->getScheduleDay()));
            jsonObj.insert(PRM_SCHEDULE_TIME, QJsonValue(test->schedule()->getScheduleTime().toString(TIME_FORMAT)));
            break;
        case TSchedule::ByExpression : {
            QJsonArray expr;
            if (!test->schedule()->getScheduleExpr1().isEmpty()) {
                expr.append(QJsonValue(test->schedule()->getScheduleExpr1()));
            }
            if (!test->schedule()->getScheduleExpr2().isEmpty()) {
                expr.append(QJsonValue(test->schedule()->getScheduleExpr2()));
            }
            jsonObj.insert(PRM_SCHEDULE_EXPR, QJsonValue(expr));
            } break;
        }

        // alert profile
        int alertProfileIdx = test->getAlertProfileID();
        if (alertProfileIdx != -1) {
            GActionProfile alertProfile = GData::actionProfiles.at(alertProfileIdx);
            jsonObj.insert(PRM_ALERTS, QJsonValue(alertProfile.name));
        }

        // Log & Reports options
        QJsonObject logObj;
        if (test->isUseCommonLog()) {
            logObj.insert(PRM_COM_LOG_MODE, QJsonValue(test->getCommonLogMode()));
        }
        if (test->isUsePrivateLog()) {
            logObj.insert(PRM_PRIV_LOG, QJsonValue(test->getPrivateLog()));
            logObj.insert(PRM_PRIV_LOG_MODE, QJsonValue(test->getPrivateLogMode()));
        }
        logObj.insert(PRM_ExcludeFromHtmlReport, QJsonValue(test->isExcludeFromHtmlReport()));
        logObj.insert(PRM_ExcludeFromWmlReport, QJsonValue(test->isExcludeFromWmlReport()));
        logObj.insert(PRM_ExcludeFromDbfReport, QJsonValue(test->isExcludeFromDbfReport()));
        jsonObj.insert(TSP_LOG, QJsonValue(logObj));

        // Dependencies
        QJsonObject dependencyObj;
        dependencyObj.insert(PRM_DEPENDS_ON, QJsonValue(test->getDependencyMode()));
        if (!test->getMasterTests().isEmpty()) {
            QJsonArray masters;
            foreach (const TTestPair &pair, test->getMasterTests()) {
                QJsonObject masterObj;
                masterObj.insert("id", QJsonValue(pair.first->getID()));
                masterObj.insert("name", QJsonValue(pair.first->getName()));
                masterObj.insert("path", QJsonValue(pair.first->getPath()));
                masterObj.insert("condition", QJsonValue(pair.second));
                masters.append(masterObj);
            }
            dependencyObj.insert("masters", QJsonValue(masters));
        }
        dependencyObj.insert(PRM_DEPEND_EXPR, QJsonValue(test->getDependencyCondition()));
        dependencyObj.insert(PRM_DEPEND_STATUS, QJsonValue(test->getDependencyOtherwiseStatus()));
        dependencyObj.insert(PRM_SYNC_COUNTERS, QJsonValue(test->isSynchronizeCounters()));
        dependencyObj.insert(PRM_SYNC_ALERTS, QJsonValue(test->isSynchronizeStatusAlerts()));
        jsonObj.insert(TSP_DEPENDENCIES, QJsonValue(dependencyObj));

        // Optional
        QJsonObject optionalObj;
        optionalObj.insert(PRM_REVERSE_ALERT, QJsonValue(test->isReverseAlert()));
        optionalObj.insert(PRM_UNKNOWN_IS_BAD, QJsonValue(test->isUnknownIsBad()));
        optionalObj.insert(PRM_WARNING_IS_BAD, QJsonValue(test->isWarningIsBad()));
        if (test->isUseWarningScript()) {
            optionalObj.insert(PRM_WARNING_EXPR, QJsonValue(test->getWarningScript()));
        }
        if (test->isUseNormalScript()) {
            optionalObj.insert(PRM_NORMAL_EXPR, QJsonValue(test->getNormalScript()));
        }
        if (test->isTuneUpReply()) {
            optionalObj.insert(PRM_TUNE_REPLY_EXP, QJsonValue(test->getTuneUpScript()));
        }
        jsonObj.insert(TSP_OPTIONAL, QJsonValue(optionalObj));

        if (storeStatistics) {
            // Store statistics
        }
        if (storeIterations) {
            // Store iterations
        }

        result.append(jsonObj);
    }
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseTestsSection(QJsonValue jsonValue)
{
    TFolder *rootFolder = qobject_cast<TFolder*>(m_HML->rootFolder());
    int scheduleModeIdx = TSchedule::staticMetaObject.indexOfEnumerator("ScheduleMode");
    QMetaEnum scheduleModeEnum = TSchedule::staticMetaObject.enumerator(scheduleModeIdx);
    foreach(const QJsonValue &testValue, jsonValue.toArray()) {
        QJsonObject jsonObj = testValue.toObject();
        // node
        int id = jsonObj.value(PRM_ID).toInt();
        QString name = jsonObj.value(PRM_TITLE).toString();
        TTest *test = new TTest(id,name);
        test->setCreatedAt(QDateTime::fromString(jsonObj.value(PRM_CREATED_AT).toString(), DT_FORMAT));
        test->setModifiedAt(QDateTime::fromString(jsonObj.value(PRM_MODIFIED_AT).toString(), DT_FORMAT));
        QString destFolder = jsonObj.value(PRM_DEST_FOLDER).toString();
        TNode *parent = m_HML->nodeByPath(destFolder);
        if (!parent || parent->getType() != TNode::FOLDER) {
            parent = rootFolder;
            QString msg = tr("Can not find dest folder '%1'").arg(destFolder);
            sendErrorMessage(msg);
        }

        // method
        parseTestMethodSection(jsonObj.value(TSP_SPECIFIC),test);

        // properties
        test->setEnabled(jsonObj.value("enabled").toBool());
        test->setPaused(jsonObj.value("paused").toBool());
        test->setPauseComment(jsonObj.value("pauseComment").toString());

        // schedule
        QString schedModeString = jsonObj.value(PRM_SCHEDULE_MODE).toString();
        TSchedule::ScheduleMode scheduleMode = static_cast<TSchedule::ScheduleMode>(scheduleModeEnum.keyToValue(schedModeString.toStdString().data()));
        switch(scheduleMode) {
        case TSchedule::Regular : {
            int interval = jsonObj.value(PRM_INTERVAL).toInt();
            QString scheduleName = jsonObj.value(PRM_SCHEDULE).toString();
            test->setRegularSchedule(interval, scheduleName);
            } break;
        case TSchedule::OncePerDay : {
            QTime time = QTime::fromString(jsonObj.value(PRM_SCHEDULE_TIME).toString(), TIME_FORMAT);
            test->schedule()->setOncePerDay(time);
            } break;
        case TSchedule::OncePerWeek : {
            QTime time = QTime::fromString(jsonObj.value(PRM_SCHEDULE_TIME).toString(), TIME_FORMAT);
            int day = jsonObj.value(PRM_SCHEDULE_DAY).toInt();
            test->schedule()->setOncePerWeek(day, time);
            } break;
        case TSchedule::OncePerMonth : {
            QTime time = QTime::fromString(jsonObj.value(PRM_SCHEDULE_TIME).toString(), TIME_FORMAT);
            int day = jsonObj.value(PRM_SCHEDULE_DAY).toInt();
            test->schedule()->setOncePerMonth(day, time);
            } break;
        case TSchedule::ByExpression : {
            QJsonArray jsonArray = jsonObj.value(PRM_SCHEDULE_EXPR).toArray();
            QString expr1, expr2;
            if (jsonArray.size()) {
                expr1 = jsonArray.at(0).toString();
            }
            if (jsonArray.size() > 1) {
                expr2 = jsonArray.at(1).toString();
            }
            test->setByExpressionSchedule(expr1, expr2);
            } break;
        }

        // alert profile
        if (jsonObj.contains(PRM_ALERTS)) {
            int alertIdx = GData::getActionProfileIdx(jsonObj.value(PRM_ALERTS).toString());
            test->setAlertProfileID(alertIdx);
        }

        // Log & Reports options
        QJsonObject logObj = jsonObj.value(TSP_LOG).toObject();
        if (logObj.contains(PRM_COM_LOG_MODE)) {
            test->setUseCommonLog(true);
            test->setCommonLogMode(logObj.value(PRM_COM_LOG_MODE).toInt());
        } else {
            test->setUseCommonLog(false);
        }
        if (logObj.contains(PRM_PRIV_LOG)) {
            test->setUsePrivateLog(true);
            test->setPrivateLogMode(logObj.value(PRM_PRIV_LOG_MODE).toInt());
            test->setPrivateLog(logObj.value(PRM_PRIV_LOG).toString());
        } else {
            test->setUsePrivateLog(false);
        }
        test->setExcludeFromHtmlReport(logObj.value(PRM_ExcludeFromHtmlReport).toBool());
        test->setExcludeFromWmlReport(logObj.value(PRM_ExcludeFromWmlReport).toBool());
        test->setExcludeFromDbfReport(logObj.value(PRM_ExcludeFromDbfReport).toBool());

        // skip dependencies (wait for all tests load)

        // optional
        QJsonObject optObj = jsonObj.value(TSP_OPTIONAL).toObject();
        test->setReverseAlert(optObj.value(PRM_REVERSE_ALERT).toBool());
        test->setUnknownIsBad(optObj.value(PRM_UNKNOWN_IS_BAD).toBool());
        test->setWarningIsBad(optObj.value(PRM_WARNING_IS_BAD).toBool());
        test->setUseWarningScript(optObj.contains(PRM_WARNING_EXPR));
        if (test->isUseWarningScript()) {
            test->setWarningScript(optObj.value(PRM_WARNING_EXPR).toString());
        }
        test->setUseNormalScript(optObj.contains(PRM_NORMAL_EXPR));
        if (test->isUseWarningScript()) {
            test->setNormalScript(optObj.value(PRM_NORMAL_EXPR).toString());
        }
        test->setTuneUpReply(optObj.contains(PRM_TUNE_REPLY_EXP));
        if (test->isUseWarningScript()) {
            test->setTuneUpScript(optObj.value(PRM_TUNE_REPLY_EXP).toString());
        }

        m_HML->addNode(parent,test);

        //! TODO Load statistics

        //! TODO Load iterations
    }

    // load dependencies "expression"
    foreach(const QJsonValue &testValue, jsonValue.toArray()) {
        QJsonObject testObj = testValue.toObject();
        QJsonObject depObj = testObj.value(TSP_DEPENDENCIES).toObject();
        Q_UNUSED(depObj)
        //! TODO implement load dependencies "expression"
    }
}

/******************************************************************/

QJsonValue IOHMList::createHistorySection()
{
    //! TODO implement createHistorySection
    return QJsonValue();
}

/******************************************************************/

void IOHMList::parseHistorySection(QJsonValue jsonValue)
{
    Q_UNUSED(jsonValue)
    //! TODO implement parseHistorySection
}

/******************************************************************/

QJsonValue IOHMList::createColumnsSettings(TNode *node)
{
    QJsonObject result;
    // column settings
    QJsonArray fields;
    foreach(const TLColumn &column, node->getColumns()) {
        QJsonObject jsonObj;
        jsonObj.insert(PRM_TITLE, QJsonValue(column.title));
        jsonObj.insert(PRM_MACRO, QJsonValue(column.macro));
        jsonObj.insert(PRM_CHECK, QJsonValue(column.checked));
        fields.append(jsonObj);
    }
    result.insert(GRP_FIELDS, QJsonValue(fields));
    // sort settings
    QJsonArray sortBy;
    foreach(const QSortPair &sort, node->getSort()) {
        QJsonObject jsonObj;
        jsonObj.insert(PRM_COLUMN, QJsonValue(sort.first));
        jsonObj.insert(PRM_ASC, QJsonValue(sort.second));
        sortBy.append(jsonObj);
    }
    result.insert(GRP_SORT, QJsonValue(sortBy));
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseColumnSettings(QJsonValue jsonValue, TNode *node)
{
    QColumnList columnList;
    foreach(const QJsonValue &fieldValue, jsonValue.toObject().value(GRP_FIELDS).toArray()) {
        QJsonObject jsonObj = fieldValue.toObject();
        TLColumn column;
        column.title   = jsonObj.value(PRM_TITLE).toString();
        column.macro   = jsonObj.value(PRM_MACRO).toString();
        column.checked = jsonObj.value(PRM_CHECK).toBool();
        columnList.append(column);
    }
    node->setColumns(columnList);

    QSortPairList sortList;
    foreach(const QJsonValue &sortValue, jsonValue.toObject().value(GRP_SORT).toArray()) {
        QJsonObject jsonObj = sortValue.toObject();
        QSortPair sortPair(jsonObj.value(PRM_COLUMN).toString(), jsonObj.value(PRM_ASC).toBool());
        sortList.append(sortPair);
    }
    node->setSort(sortList);
}

/******************************************************************/

QJsonValue IOHMList::createColorSettings(TNode *node)
{
    QJsonObject result;
    result.insert(PRM_SCHEME, QJsonValue(node->getColorScheme()));
    result.insert(PRM_CHECK, QJsonValue(node->isCheckingColorStatus()));
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseColorSettings(QJsonValue jsonValue, TNode *node)
{
    QJsonObject jsonObj = jsonValue.toObject();
    node->setColorScheme(jsonObj.value(PRM_SCHEME).toString());
    node->setCheckingColorStatus(jsonObj.value(PRM_CHECK).toBool());
}

/******************************************************************/

QJsonValue IOHMList::createReportSettings(TNode *node)
{
    QJsonObject result;
    Q_UNUSED(node)
    //! TODO implement createReportSettings
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseReportSettings(QJsonValue jsonValue, TNode *node)
{
    QJsonObject jsonObj = jsonValue.toObject();
    Q_UNUSED(jsonObj)
    Q_UNUSED(node)
    //! TODO implement parseReportSettings
}

/******************************************************************/

QJsonValue IOHMList::createStatSettings(TFolder *node)
{
    QJsonObject result;
    Q_UNUSED(node)
    //! TODO implement createStatSettings
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseStatSettings(QJsonValue jsonValue, TFolder *node)
{
    QJsonObject jsonObj = jsonValue.toObject();
    Q_UNUSED(jsonObj)
    Q_UNUSED(node)
    //! TODO implement parseStatSettings
}

/******************************************************************/

QJsonValue IOHMList::createRegionalSettings(TFolder *node)
{
    QJsonObject result;
    result.insert(PRM_GUI, QJsonValue(node->isApplyRemoteTimeToGui()));
    result.insert(PRM_SCHEDULERS, QJsonValue(node->isApplyRemoteTimeToSchedules()));
    result.insert(PRM_TIMEZONE, QJsonValue(node->getTimeZoneIanaId()));
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseRegionalSettings(QJsonValue jsonValue, TFolder *node)
{
    QJsonObject jsonObj = jsonValue.toObject();
    node->setApplyRemoteTimeToGui(jsonObj.value(PRM_GUI).toBool());
    node->setApplyRemoteTimeToSchedules(jsonObj.value(PRM_SCHEDULERS).toBool());
    node->setTimeZoneIanaId(jsonObj.value(PRM_TIMEZONE).toString());
}

/******************************************************************/

QJsonValue IOHMList::createVarsSettings(TFolder *node)
{
    QJsonObject result;
    Q_UNUSED(node)
    //! TODO implement createVarsSettings
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseVarsSettings(QJsonValue jsonValue, TFolder *node)
{
    QJsonObject jsonObj = jsonValue.toObject();
    Q_UNUSED(jsonObj)
    Q_UNUSED(node)
    //! TODO implement parseVarsSettings
}

/******************************************************************/

QJsonValue IOHMList::createSpecialsSettings(TFolder *node)
{
    QJsonObject result;
    result.insert(PRM_AFFECT_TRAY_ICON, QJsonValue(node->isTestStatusesNotAffectTrayIconColor()));
    result.insert(PRM_NON_SIMUL_EXEC, QJsonValue(node->isNonSimultaneouslyTestExecution()));
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseSpecialsSettings(QJsonValue jsonValue, TFolder *node)
{
    QJsonObject jsonObj = jsonValue.toObject();
    node->setTestStatusesNotAffectTrayIconColor(jsonObj.value(PRM_AFFECT_TRAY_ICON).toBool());
    node->setNonSimultaneouslyTestExecution(jsonObj.value(PRM_NON_SIMUL_EXEC).toBool());
}

/******************************************************************/

QJsonValue IOHMList::createViewCriteriaSettings(TView *view)
{
    QJsonObject result;
    // select items by status
    if (view->isSelectByStatus()) {
        QJsonArray statusObj;
        int idx = TView::staticMetaObject.indexOfEnumerator("VStatus");
        QMetaEnum statusEnum = TView::staticMetaObject.enumerator(idx);
        foreach(const TView::VStatus &st, view->getStatusCriteria()) {
            statusObj.append(QJsonValue(statusEnum.key(st)));
        }
        result.insert(PRM_VC_STATUS,QJsonValue(statusObj));
    }
    // select items by test method
    if (view->isSelectByTestMethod()) {
        QJsonArray methodObj;
        foreach(const TMethodID &meth, view->getMethodCriteria()) {
            methodObj.append(QJsonValue(TMethod::toName(meth)));
        }
        result.insert(PRM_VC_METHOD,QJsonValue(methodObj));
    }

    // select items by statistics
    if (view->isSelectByStats()) {
        int idx = TView::staticMetaObject.indexOfEnumerator("VCriteria");
        QMetaEnum criteriaEnum = TView::staticMetaObject.enumerator(idx);
        QJsonObject statsObj;
        TView::VCriteria statsCriteria = view->getStatsCriteria();
        statsObj.insert(PRM_VC_STAT_TYPE, QJsonValue(criteriaEnum.key(statsCriteria)));
        switch (statsCriteria) {
        case TView::VC_AliveRatio:
            statsObj.insert(PRM_VC_STAT_VALUE, QJsonValue(view->getAliveRatioValue()));
            break;
        case TView::VC_DeadRatio:
            statsObj.insert(PRM_VC_STAT_VALUE, QJsonValue(view->getDeadRatioValue()));
            break;
        case TView::VC_UnknownRatio:
            statsObj.insert(PRM_VC_STAT_VALUE, QJsonValue(view->getUnknownRatioValue()));
            break;
        case TView::VC_ReplyGT:
            statsObj.insert(PRM_VC_STAT_VALUE, QJsonValue(view->getReplyGTValue()));
            break;
        case TView::VC_ReplyLT:
            statsObj.insert(PRM_VC_STAT_VALUE, QJsonValue(view->getReplyLTValue()));
            break;
        case TView::VC_Duration:
            statsObj.insert(PRM_VC_STAT_SUBTYPE, QJsonValue(view->isDurationGreater()?"GT":"LT"));
            statsObj.insert(PRM_VC_STAT_VALUE, QJsonValue(view->getDurationValue()));
            break;
        }
        result.insert(PRM_VC_STATISTICS,QJsonValue(statsObj));
    }

    // select items by test properties
    if (view->isSelectByTestName()) {
        result.insert(PRM_VC_NAME,QJsonValue(view->getTestNameValue()));
    }
    if (view->isSelectByTarget()) {
        result.insert(PRM_VC_TARGET,QJsonValue(view->getTargetValue()));
    }
    if (view->isSelectByComment()) {
        result.insert(PRM_VC_COMMENT,QJsonValue(view->getCommentValue()));
    }
    if (view->isSelectByAgent()) {
        result.insert(PRM_VC_AGENT,QJsonValue(view->getAgentValue()));
    }

    // select items using expression
    if (view->isSelectUsingExpression()) {
        result.insert(PRM_VC_EXPRESSION,QJsonValue(view->getExpressionValue()));
    }

    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseViewCriteriaSettings(QJsonValue jsonValue, TView *view)
{
    QJsonObject jsonObj = jsonValue.toObject();

    // select items by status
    view->setSelectByStatus(jsonObj.contains(PRM_VC_STATUS));
    if (view->isSelectByStatus()) {
        int idx = TView::staticMetaObject.indexOfEnumerator("VStatus");
        QMetaEnum statusEnum = TView::staticMetaObject.enumerator(idx);
        view->clearStatusCriteria();
        foreach(const QJsonValue &val, jsonObj.value(PRM_VC_STATUS).toArray()) {
            TView::VStatus status = (TView::VStatus)statusEnum.keyToValue(val.toString().toStdString().data());
            view->addStatusCriteria(status);
        }
    }

    // select items by test method
    view->setSelectByTestMethod(jsonObj.contains(PRM_VC_METHOD));
    if (view->isSelectByTestMethod()) {
        view->clearMethodCriteria();
        foreach(const QJsonValue &val, jsonObj.value(PRM_VC_METHOD).toArray()) {
            view->addMethodCriteria(TMethod::fromString(val.toString()));
        }
    }

    // select items by statistics
    view->setSelectByStats(jsonObj.contains(PRM_VC_STATISTICS));
    if (view->isSelectByStats()) {
        QJsonObject statsObj = jsonObj.value(PRM_VC_STATISTICS).toObject();
        int idx = TView::staticMetaObject.indexOfEnumerator("VCriteria");
        QMetaEnum criteriaEnum = TView::staticMetaObject.enumerator(idx);
        QString statsType = statsObj.value(PRM_VC_STAT_TYPE).toString();
        TView::VCriteria statsCriteria = (TView::VCriteria)criteriaEnum.keyToValue(statsType.toStdString().data());
        switch (statsCriteria) {
        case TView::VC_AliveRatio:
            view->setAliveRatioValue(statsObj.value(PRM_VC_STAT_VALUE).toDouble());
            break;
        case TView::VC_DeadRatio:
            view->setDeadRatioValue(statsObj.value(PRM_VC_STAT_VALUE).toDouble());
            break;
        case TView::VC_UnknownRatio:
            view->setUnknownRatioValue(statsObj.value(PRM_VC_STAT_VALUE).toDouble());
            break;
        case TView::VC_ReplyGT:
            view->setReplyGTValue(statsObj.value(PRM_VC_STAT_VALUE).toDouble());
            break;
        case TView::VC_ReplyLT:
            view->setReplyLTValue(statsObj.value(PRM_VC_STAT_VALUE).toDouble());
            break;
        case TView::VC_Duration:
            view->setDurationGreater(statsObj.value(PRM_VC_STAT_SUBTYPE).toString() == QString("GT"));
            view->setDurationValue(statsObj.value(PRM_VC_STAT_VALUE).toInt());
            break;
        }
    }

    // select items by test properties
    view->setSelectByTestName(jsonObj.contains(PRM_VC_NAME));
    if (view->isSelectByTestName()) {
        view->setTestNameValue(jsonObj.value(PRM_VC_NAME).toString());
    }
    view->setSelectByTarget(jsonObj.contains(PRM_VC_TARGET));
    if (view->isSelectByTarget()) {
        view->setTargetValue(jsonObj.value(PRM_VC_TARGET).toString());
    }
    view->setSelectByComment(jsonObj.contains(PRM_VC_COMMENT));
    if (view->isSelectByComment()) {
        view->setCommentValue(jsonObj.value(PRM_VC_COMMENT).toString());
    }
    view->setSelectByAgent(jsonObj.contains(PRM_VC_AGENT));
    if (view->isSelectByAgent()) {
        view->setAgentValue(jsonObj.value(PRM_VC_AGENT).toString());
    }

    // select items using expression
    view->setSelectUsingExpression(jsonObj.contains(PRM_VC_EXPRESSION));
    if (view->isSelectUsingExpression()) {
        view->setExpressionValue(jsonObj.value(PRM_VC_EXPRESSION).toString());
    }
}

/******************************************************************/

QJsonValue IOHMList::createTestMethodSection(TTest *test)
{
    TTestMethod *method = test->method();
    IOTestMethodConverter *converter = IOHelper::methodConverter(method->getTMethodID());
    converter->setTestMethod(method);
    QJsonObject jsonObj = converter->toJsonObject();
    converter->deleteLater();
    jsonObj.insert(PRM_METHOD, QJsonValue(method->getTestMethodName()));
    jsonObj.insert(PRM_NAME_PATTERN, QJsonValue(method->getNamePattern()));
    jsonObj.insert(PRM_CMNT_PATTERN, QJsonValue(method->getCommentPattern()));
    return QJsonValue(jsonObj);
}

/******************************************************************/

void IOHMList::parseTestMethodSection(QJsonValue jsonValue, TTest *test)
{
    QJsonObject jsonObj = jsonValue.toObject();
    QString methodName = jsonObj.value(PRM_METHOD).toString();
    TMethodID methodID = TMethod::fromString(methodName);
    IOTestMethodConverter *converter = IOHelper::methodConverter(methodID);
    TTestMethod *method = converter->fromJsonObject(jsonObj);
    converter->deleteLater();
    method->setNamePattern(jsonObj.value(PRM_NAME_PATTERN).toString());
    method->setCommentPattern(jsonObj.value(PRM_CMNT_PATTERN).toString());
    test->setMethod(method);
}

/******************************************************************/

} // namespace SDPO
