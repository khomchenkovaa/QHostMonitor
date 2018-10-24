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
    return parseJsonData(jsonDoc);
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

void IOHMList::sendErrorMessage(const QString &msg)
{
    qDebug() << msg;
    emit notifyStatusMessage(msg);
}

/******************************************************************/

bool IOHMList::parseJsonData(QJsonDocument json_doc)
{
    QJsonObject jsonObj = json_doc.object();
    // head
    m_HML->setGuid(QUuid(jsonObj["GUID"].toString()));

    return false;
}

/******************************************************************/

QJsonDocument IOHMList::createJsonDocument()
{
    QSettings s;
    QJsonObject jsonObj;
    // head
    jsonObj.insert("GUID", QJsonValue(m_HML->guid().toString()));
    jsonObj.insert("count", QJsonValue(TRoot::counter()));
    jsonObj.insert("history", QJsonValue(m_HML->isStoreHistoricalData()));
    if (s.value(SKEY_INTERFACE_SaveCurrFolder, 1).toInt()) {
        jsonObj.insert("currentFolder", QJsonValue(m_HML->currentFolder()->getPath()));
    }

    // root
    jsonObj.insert("root", createRootFolderSection());
    jsonObj.insert("rootView", createRootViewSection());

    // Folders and views
    jsonObj.insert("folders", createFoldersSection());
    jsonObj.insert("views", createViewsSection());

    // tests
    bool storeStatistics = (s.value(SKEY_MISC_StoreStatistics, 1).toInt()==1);
    bool storeIterations = (s.value(SKEY_MISC_StoreIterations, 1).toInt()==1);
    jsonObj.insert("tests", createTestsSection(storeStatistics, storeIterations));

    // history
    if (m_HML->isStoreHistoricalData()) {
        jsonObj.insert("history", createHistorySection());
    }

    QJsonDocument jsonDoc(jsonObj);
    return jsonDoc;
}

/******************************************************************/

QJsonValue IOHMList::createRootFolderSection()
{
    QJsonObject result;
    TFolder *fld = qobject_cast<TFolder*>(m_HML->rootFolder());
    // columns
    if (fld->isUseOwnColumnSettings()) {
        result.insert("columns", createColumnsSettings(fld));
        result.insert("sort", createSortSettings(fld));
    }

    // folder colors
    if (fld->isUseOwnColorSettings()) {
        QJsonObject colorObj;
        colorObj.insert("scheme", QJsonValue(fld->getColorScheme()));
        colorObj.insert("checking", QJsonValue(fld->isCheckingColorStatus()));
        result.insert("colors", QJsonValue(colorObj));
    }

    // reports
    //! TODO

    // statistics
    //! TODO

    // regional
    if (fld->isUseOwnRegionalSettings()) {
        QJsonObject regionalObj;
        regionalObj.insert("gui", QJsonValue(fld->isApplyRemoteTimeToGui()));
        regionalObj.insert("schedulers", QJsonValue(fld->isApplyRemoteTimeToSchedules()));
        regionalObj.insert("timezone", QJsonValue(fld->getTimeZoneIanaId()));
        result.insert("regional", QJsonValue(regionalObj));
    }

    // comment
    if (!fld->getComment().isEmpty()) {
        result.insert("comment", QJsonValue(fld->getComment()));
    }

    // variables
    //! TODO

    // specials
    QJsonObject specialsObj;
    specialsObj.insert("testStatusesNotAffectTrayIcon", QJsonValue(fld->isTestStatusesNotAffectTrayIconColor()));
    specialsObj.insert("nonSimultaneouslyTestExecution", QJsonValue(fld->isNonSimultaneouslyTestExecution()));
    result.insert("specials", QJsonValue(specialsObj));

    return QJsonValue(result);
}

/******************************************************************/

QJsonValue IOHMList::createRootViewSection()
{
    QJsonObject result;
    TFolder *fld = qobject_cast<TFolder*>(m_HML->rootView());
    // columns
    if (fld->isUseOwnColumnSettings()) {
        result.insert("columns", createColumnsSettings(fld));
        result.insert("sort", createSortSettings(fld));
    }

    // folder colors
    if (fld->isUseOwnColorSettings()) {
        QJsonObject colorObj;
        colorObj.insert("scheme", QJsonValue(fld->getColorScheme()));
        colorObj.insert("checking", QJsonValue(fld->isCheckingColorStatus()));
        result.insert("colors", QJsonValue(colorObj));
    }

    // comment
    if (!fld->getComment().isEmpty()) {
        result.insert("comment", QJsonValue(fld->getComment()));
    }

    return QJsonValue(result);
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
            jsonObj.insert("columns", createColumnsSettings(fld));
            jsonObj.insert("sort", createSortSettings(fld));
        }

        // folder colors
        if (fld->isUseOwnColorSettings()) {
            QJsonObject colorObj;
            colorObj.insert("scheme", QJsonValue(fld->getColorScheme()));
            colorObj.insert("checking", QJsonValue(fld->isCheckingColorStatus()));
            jsonObj.insert("colors", QJsonValue(colorObj));
        }

        // reports
        //! TODO

        // statistics
        //! TODO

        // regional
        if (fld->isUseOwnRegionalSettings()) {
            QJsonObject regionalObj;
            regionalObj.insert("gui", QJsonValue(fld->isApplyRemoteTimeToGui()));
            regionalObj.insert("schedulers", QJsonValue(fld->isApplyRemoteTimeToSchedules()));
            regionalObj.insert("timezone", QJsonValue(fld->getTimeZoneIanaId()));
            jsonObj.insert("regional", QJsonValue(regionalObj));
        }

        // comment
        if (!fld->getComment().isEmpty()) {
            jsonObj.insert("comment", QJsonValue(fld->getComment()));
        }

        // variables
        //! TODO

        // specials
        QJsonObject specialsObj;
        specialsObj.insert("testStatusesNotAffectTrayIcon", QJsonValue(fld->isTestStatusesNotAffectTrayIconColor()));
        specialsObj.insert("nonSimultaneouslyTestExecution", QJsonValue(fld->isNonSimultaneouslyTestExecution()));
        jsonObj.insert("specials", QJsonValue(specialsObj));

        result.append(jsonObj);
    }
    return QJsonValue(result);
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
        jsonObj.insert("criteria", createViewCriteriaSettings(view));

        // columns
        if (view->isUseOwnColumnSettings()) {
            jsonObj.insert("columns", createColumnsSettings(view));
            jsonObj.insert("sort", createSortSettings(view));
        }

        // colors
        if (view->isUseOwnColorSettings()) {
            QJsonObject colorObj;
            colorObj.insert("scheme", QJsonValue(view->getColorScheme()));
            colorObj.insert("checking", QJsonValue(view->isCheckingColorStatus()));
            jsonObj.insert("colors", QJsonValue(colorObj));
        }

        // reports
        //! TODO

        // comment
        if (!view->getComment().isEmpty()) {
            jsonObj.insert("comment", QJsonValue(view->getComment()));
        }

        result.append(jsonObj);
    }
    return QJsonValue(result);
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
        jsonObj.insert("comment", QJsonValue(test->getComment()));

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
        logObj.insert("excludeFromHtmlReport", QJsonValue(test->isExcludeFromHtmlReport()));
        logObj.insert("excludeFromWmlReport", QJsonValue(test->isExcludeFromWmlReport()));
        logObj.insert("excludeFromDbfReport", QJsonValue(test->isExcludeFromDbfReport()));
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

QJsonValue IOHMList::createHistorySection()
{
    return QJsonValue();
}

/******************************************************************/

QJsonValue IOHMList::createColumnsSettings(TNode *node)
{
    QJsonArray result;
    foreach(const TLColumn &column, node->getColumns()) {
        QJsonObject jsonObj;
        jsonObj.insert("title", QJsonValue(column.title));
        jsonObj.insert("macro", QJsonValue(column.macro));
        jsonObj.insert("checked", QJsonValue(column.checked));
        result.append(jsonObj);
    }
    return QJsonValue(result);
}

/******************************************************************/

QJsonValue IOHMList::createSortSettings(TNode *node)
{
    QJsonArray result;
    foreach(const QSortPair &sort, node->getSort()) {
        QJsonObject jsonObj;
        jsonObj.insert("column", QJsonValue(sort.first));
        jsonObj.insert("asc", QJsonValue(sort.second));
        result.append(jsonObj);
    }
    return QJsonValue(result);
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

} // namespace SDPO
