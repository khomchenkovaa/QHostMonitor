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
        jsonObj.insert("id", QJsonValue(fld->getID()));
        jsonObj.insert("name", QJsonValue(fld->getName()));
        jsonObj.insert("path", QJsonValue(fld->getPath()));
        jsonObj.insert("created", QJsonValue(fld->getCreatedAt().toString(DT_FORMAT)));
        jsonObj.insert("modified", QJsonValue(fld->getModifiedAt().toString(DT_FORMAT)));
        jsonObj.insert("parentID", QJsonValue(fld->parentNode()->getID()));

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
    TFolder *rootFolder = qobject_cast<TFolder*>(m_HML->rootFolder());
    foreach(const QJsonValue &fldValue, jsonValue.toArray()) {
        QJsonObject jsonObj = fldValue.toObject();
        // node
        int parentID = jsonObj.value("parentID").toInt();
        TNode *parent = rootFolder->findByID(parentID);
        if (!parent || parent->getType() != TNode::FOLDER) {
            QString msg = tr("Can not find folder with id %1").arg(parentID);
            sendErrorMessage(msg);
            // skip ?
            continue;
        }
        int id = jsonObj.value("id").toInt();
        QString name = jsonObj.value("name").toString();
        TFolder *fld = new TFolder(id, name);
        m_HML->addNode(parent, fld);
        fld->setCreatedAt(QDateTime::fromString(jsonObj.value("created").toString(), DT_FORMAT));
        fld->setModifiedAt(QDateTime::fromString(jsonObj.value("modified").toString(), DT_FORMAT));

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
        jsonObj.insert("id", QJsonValue(view->getID()));
        jsonObj.insert("name", QJsonValue(view->getName()));
        jsonObj.insert("path", QJsonValue(view->getPath()));
        jsonObj.insert("created", QJsonValue(view->getCreatedAt().toString(DT_FORMAT)));
        jsonObj.insert("modified", QJsonValue(view->getModifiedAt().toString(DT_FORMAT)));

        // source
        QJsonObject sourceObj;
        sourceObj.insert("folderID", QJsonValue(view->getSourceFolder()->getID()));
        sourceObj.insert("folder", QJsonValue(view->getSourceFolder()->getPath()));
        sourceObj.insert("recursive", QJsonValue(view->isRecursive()));
        jsonObj.insert("source", QJsonValue(sourceObj));

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
        QJsonObject srcObj = jsonObj.value("source").toObject();
        int folderID = srcObj.value("folderID").toInt();
        bool recursive = srcObj.value("recursive").toBool();
        TNode *source = m_HML->rootFolder()->findByID(folderID);
        if (!source || source->getType() != TNode::FOLDER) {
            source = m_HML->rootFolder();
        }

        // node
        int id = jsonObj.value("id").toInt();
        QString name = jsonObj.value("name").toString();
        TView *view = new TView(id, name,  qobject_cast<TFolder*>(source));
        m_HML->addNode(rootView, view);
        view->setCreatedAt(QDateTime::fromString(jsonObj.value("created").toString(), DT_FORMAT));
        view->setModifiedAt(QDateTime::fromString(jsonObj.value("modified").toString(), DT_FORMAT));
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
    foreach(TNode *node, folder->testList()) {
        if (node->getType() != TNode::TEST) continue;
        TTest *test = qobject_cast<TTest*>(node);
        QJsonObject jsonObj;

        // node
        jsonObj.insert("id", QJsonValue(test->getID()));
        jsonObj.insert("name", QJsonValue(test->getName()));
        jsonObj.insert("path", QJsonValue(test->getPath()));
        jsonObj.insert("created", QJsonValue(test->getCreatedAt().toString(DT_FORMAT)));
        jsonObj.insert("modified", QJsonValue(test->getModifiedAt().toString(DT_FORMAT)));
        jsonObj.insert("parentID", QJsonValue(test->parentNode()->getID()));
        jsonObj.insert(PRM_COMMENT, QJsonValue(test->getComment()));

        // method
        QJsonObject methodObj;
        TTestMethod* method = test->method();
        methodObj.insert("type", QJsonValue(method->getTestMethodName()));
        methodObj.insert("namePattern", QJsonValue(method->getNamePattern()));
        methodObj.insert("commentPattern", QJsonValue(method->getCommentPattern()));
        IOTestMethodConverter *converter = IOHelper::methodConverter(method->getTMethodID());
        converter->setTestMethod(method);
        methodObj.insert("params",converter->toJson());
        delete converter;
        jsonObj.insert("method", QJsonValue(methodObj));

        // properties
        jsonObj.insert("enabled", QJsonValue(test->isEnabled()));
        jsonObj.insert("paused", QJsonValue(test->isPaused()));
        jsonObj.insert("pauseComment", QJsonValue(test->getPauseComment()));

        // alert profile
        jsonObj.insert("alert", QJsonValue(test->getAlertProfileID()));

        // Log & Reports options
        QJsonObject logObj;
        if (test->isUseCommonLog()) {
            logObj.insert("commonLogMode", QJsonValue(test->getCommonLogMode()));
        }
        if (test->isUsePrivateLog()) {
            logObj.insert("privateLogMode", QJsonValue(test->getPrivateLogMode()));
            logObj.insert("privateLog", QJsonValue(test->getPrivateLog()));
        }
        logObj.insert("ExcludeFromHtmlReport", QJsonValue(test->isExcludeFromHtmlReport()));
        logObj.insert("ExcludeFromWmlReport", QJsonValue(test->isExcludeFromWmlReport()));
        logObj.insert("ExcludeFromDbfReport", QJsonValue(test->isExcludeFromDbfReport()));
        jsonObj.insert("log", QJsonValue(logObj));

        // Dependencies
        QJsonObject dependencyObj;
        dependencyObj.insert("mode", QJsonValue(test->getDependencyMode()));
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
        dependencyObj.insert("expression", QJsonValue(test->getDependencyCondition()));
        dependencyObj.insert("otherwiseStatus", QJsonValue(test->getDependencyOtherwiseStatus()));
        dependencyObj.insert("synchronizeCounters", QJsonValue(test->isSynchronizeCounters()));
        dependencyObj.insert("synchronizeAlerts", QJsonValue(test->isSynchronizeStatusAlerts()));
        jsonObj.insert("dependencies", QJsonValue(dependencyObj));

        // optional
        QJsonObject optionalObj;
        optionalObj.insert("reverse", QJsonValue(test->isReverseAlert()));
        optionalObj.insert("UnknownIsBad", QJsonValue(test->isUnknownIsBad()));
        optionalObj.insert("WarningIsBad", QJsonValue(test->isWarningIsBad()));
        if (test->isUseWarningScript()) {
            optionalObj.insert("WarningScript", QJsonValue(test->getWarningScript()));
        }
        if (test->isUseNormalScript()) {
            optionalObj.insert("NormalScript", QJsonValue(test->getNormalScript()));
        }
        if (test->isTuneUpReply()) {
            optionalObj.insert("TuneUpScript", QJsonValue(test->getTuneUpScript()));
        }
        jsonObj.insert("optional", QJsonValue(optionalObj));

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
    foreach(const QJsonValue &testValue, jsonValue.toArray()) {
        QJsonObject testObj = testValue.toObject();
        // node
        int id = testObj.value("id").toInt();
        QString name = testObj.value("name").toString();
        TTest *test = new TTest(id,name);
        test->setCreatedAt(QDateTime::fromString(testObj.value("created").toString(), DT_FORMAT));
        test->setModifiedAt(QDateTime::fromString(testObj.value("modified").toString(), DT_FORMAT));
        int parentId = testObj.value("parentID").toInt();
        TNode *parent = rootFolder->findByID(parentId);
        if (!parent || parent->getType() != TNode::FOLDER) {
            parent = rootFolder;
        }
        m_HML->addNode(parent,test);

        // method
        QJsonObject methodObj = testObj.value("method").toObject();
        QString methodName = methodObj.value("type").toString();
        TMethodID methodID = TMethod::fromString(methodName);
        IOTestMethodConverter *converter = IOHelper::methodConverter(methodID);
        TTestMethod *method = converter->fromJson(methodObj.value("params"));
        method->setNamePattern(methodObj.value("namePattern").toString());
        method->setCommentPattern(methodObj.value("commentPattern").toString());
        test->setTest(method);
        delete converter;

        // properties
        test->setEnabled(testObj.value("enabled").toBool());
        test->setPaused(testObj.value("paused").toBool());
        test->setPauseComment(testObj.value("pauseComment").toString());

        // alert profile
        //!

        // Log & Reports options
        QJsonObject logObj = testObj.value("log").toObject();
        if (logObj.contains("commonLogMode")) {
            test->setUseCommonLog(true);
            test->setCommonLogMode(logObj.value("commonLogMode").toInt());
        } else {
            test->setUseCommonLog(false);
        }
        if (logObj.contains("privateLogMode")) {
            test->setUsePrivateLog(true);
            test->setPrivateLogMode(logObj.value("privateLogMode").toInt());
            test->setPrivateLog(logObj.value("privateLog").toString());
        } else {
            test->setUsePrivateLog(false);
        }
        test->setExcludeFromHtmlReport(logObj.value("ExcludeFromHtmlReport").toBool());
        test->setExcludeFromWmlReport(logObj.value("ExcludeFromWmlReport").toBool());
        test->setExcludeFromDbfReport(logObj.value("ExcludeFromDbfReport").toBool());

        // skip dependencies (wait for all tests load)

        // optional
        QJsonObject optObj = testObj.value("optional").toObject();
        test->setReverseAlert(optObj.value("reverse").toBool());
        test->setUnknownIsBad(optObj.value("UnknownIsBad").toBool());
        test->setWarningIsBad(optObj.value("WarningIsBad").toBool());
        test->setUseWarningScript(optObj.contains("WarningScript"));
        if (test->isUseWarningScript()) {
            test->setWarningScript(optObj.value("WarningScript").toString());
        }
        test->setUseNormalScript(optObj.contains("NormalScript"));
        if (test->isUseWarningScript()) {
            test->setNormalScript(optObj.value("NormalScript").toString());
        }
        test->setTuneUpReply(optObj.contains("TuneUpScript"));
        if (test->isUseWarningScript()) {
            test->setTuneUpScript(optObj.value("TuneUpScript").toString());
        }

        // Load statistics

        // Load iterations
    }

    // load dependencies
    foreach(const QJsonValue &testValue, jsonValue.toArray()) {
        QJsonObject testObj = testValue.toObject();
        QJsonObject depObj = testObj.value("dependencies").toObject();
        Q_UNUSED(depObj)
        //! TODO
    }
}

/******************************************************************/

QJsonValue IOHMList::createHistorySection()
{
    //! TODO
    return QJsonValue();
}

/******************************************************************/

void IOHMList::parseHistorySection(QJsonValue jsonValue)
{
    Q_UNUSED(jsonValue)
    //! TODO
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
    //! TODO
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseReportSettings(QJsonValue jsonValue, TNode *node)
{
    QJsonObject jsonObj = jsonValue.toObject();
    Q_UNUSED(jsonObj)
    Q_UNUSED(node)
}

/******************************************************************/

QJsonValue IOHMList::createStatSettings(TFolder *node)
{
    QJsonObject result;
    Q_UNUSED(node)
    //! TODO
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseStatSettings(QJsonValue jsonValue, TFolder *node)
{
    QJsonObject jsonObj = jsonValue.toObject();
    Q_UNUSED(jsonObj)
    Q_UNUSED(node)
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
    //! TODO
    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseVarsSettings(QJsonValue jsonValue, TFolder *node)
{
    QJsonObject jsonObj = jsonValue.toObject();
    Q_UNUSED(jsonObj)
    Q_UNUSED(node)
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
        result.insert("status",QJsonValue(statusObj));
    }
    // select items by test method
    if (view->isSelectByTestMethod()) {
        QJsonArray methodObj;
        foreach(const TMethodID &meth, view->getMethodCriteria()) {
            methodObj.append(QJsonValue(TMethod::toName(meth)));
        }
        result.insert("method",QJsonValue(methodObj));
    }

    // select items by statistics
    if (view->isSelectByStats()) {
        int idx = TView::staticMetaObject.indexOfEnumerator("VCriteria");
        QMetaEnum criteriaEnum = TView::staticMetaObject.enumerator(idx);
        QJsonObject statsObj;
        TView::VCriteria statsCriteria = view->getStatsCriteria();
        statsObj.insert("type", QJsonValue(criteriaEnum.key(statsCriteria)));
        switch (statsCriteria) {
        case TView::VC_AliveRatio:
            statsObj.insert("value", QJsonValue(view->getAliveRatioValue()));
            break;
        case TView::VC_DeadRatio:
            statsObj.insert("value", QJsonValue(view->getDeadRatioValue()));
            break;
        case TView::VC_UnknownRatio:
            statsObj.insert("value", QJsonValue(view->getUnknownRatioValue()));
            break;
        case TView::VC_ReplyGT:
            statsObj.insert("value", QJsonValue(view->getReplyGTValue()));
            break;
        case TView::VC_ReplyLT:
            statsObj.insert("value", QJsonValue(view->getReplyLTValue()));
            break;
        case TView::VC_Duration:
            if (view->isDurationGreater()) {
                statsObj.insert("GT", QJsonValue(view->getDurationValue()));
            } else {
                statsObj.insert("LT", QJsonValue(view->getDurationValue()));
            }
            break;
        }
        result.insert("statistics",QJsonValue(statsObj));
    }

    // select items by test properties
    if (view->isSelectByTestName()) {
        result.insert("name",QJsonValue(view->getTestNameValue()));
    }
    if (view->isSelectByTarget()) {
        result.insert("target",QJsonValue(view->getTargetValue()));
    }
    if (view->isSelectByComment()) {
        result.insert("comment",QJsonValue(view->getCommentValue()));
    }
    if (view->isSelectByAgent()) {
        result.insert("agent",QJsonValue(view->getAgentValue()));
    }

    // select items using expression
    if (view->isSelectUsingExpression()) {
        result.insert("expression",QJsonValue(view->getExpressionValue()));
    }

    return QJsonValue(result);
}

/******************************************************************/

void IOHMList::parseViewCriteriaSettings(QJsonValue jsonValue, TView *view)
{
    QJsonObject jsonObj = jsonValue.toObject();

    // select items by status
    if (jsonObj.contains("status")) {
        view->setSelectByStatus(true);
        int idx = TView::staticMetaObject.indexOfEnumerator("VStatus");
        QMetaEnum statusEnum = TView::staticMetaObject.enumerator(idx);
        view->clearStatusCriteria();
        foreach(const QJsonValue &val, jsonObj.value("status").toArray()) {
            TView::VStatus status = (TView::VStatus)statusEnum.keyToValue(val.toString().toStdString().data());
            view->addStatusCriteria(status);
        }
    } else {
        view->setSelectByStatus(false);
    }

    // select items by test method
    if (jsonObj.contains("method")) {
        view->setSelectByTestMethod(true);
        view->clearMethodCriteria();
        foreach(const QJsonValue &val, jsonObj.value("method").toArray()) {
            view->addMethodCriteria(TMethod::fromString(val.toString()));
        }
    } else {
        view->setSelectByTestMethod(false);
    }

    // select items by statistics
    if (jsonObj.contains("statistics")) {
        view->setSelectByStats(true);
        QJsonObject statsObj = jsonObj.value("statistics").toObject();
        int idx = TView::staticMetaObject.indexOfEnumerator("VCriteria");
        QMetaEnum criteriaEnum = TView::staticMetaObject.enumerator(idx);
        TView::VCriteria statsCriteria = (TView::VCriteria)criteriaEnum.keyToValue(statsObj.value("type").toString().toStdString().data());
        switch (statsCriteria) {
        case TView::VC_AliveRatio:
            view->setAliveRatioValue(statsObj.value("value").toDouble());
            break;
        case TView::VC_DeadRatio:
            view->setDeadRatioValue(statsObj.value("value").toDouble());
            break;
        case TView::VC_UnknownRatio:
            view->setUnknownRatioValue(statsObj.value("value").toDouble());
            break;
        case TView::VC_ReplyGT:
            view->setReplyGTValue(statsObj.value("value").toDouble());
            break;
        case TView::VC_ReplyLT:
            view->setReplyLTValue(statsObj.value("value").toDouble());
            break;
        case TView::VC_Duration:
            if (statsObj.contains("GT")) {
                view->setDurationGreater(true);
                view->setDurationValue(statsObj.value("GT").toInt());
            } else {
                view->setDurationGreater(false);
                view->setDurationValue(statsObj.value("LT").toInt());
            }
        }
    } else {
        view->setSelectByStats(false);
    }

    // select items by test properties
    if (jsonObj.contains("name")) {
        view->setSelectByTestName(true);
        view->setTestNameValue(jsonObj.value("name").toString());
    } else {
        view->setSelectByTestName(false);
    }
    if (jsonObj.contains("target")) {
        view->setSelectByTarget(true);
        view->setTargetValue(jsonObj.value("target").toString());
    } else {
        view->setSelectByTarget(false);
    }
    if (jsonObj.contains("comment")) {
        view->setSelectByComment(true);
        view->setCommentValue(jsonObj.value("comment").toString());
    } else {
        view->setSelectByComment(false);
    }
    if (jsonObj.contains("agent")) {
        view->setSelectByAgent(true);
        view->setAgentValue(jsonObj.value("agent").toString());
    } else {
        view->setSelectByAgent(false);
    }

    // select items using expression
    if (jsonObj.contains("expression")) {
        view->setSelectUsingExpression(true);
        view->setExpressionValue(jsonObj.value("expression").toString());
    } else {
        view->setSelectUsingExpression(false);
    }
}

/******************************************************************/

} // namespace SDPO
