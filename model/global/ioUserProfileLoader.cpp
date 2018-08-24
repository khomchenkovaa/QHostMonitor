#include "ioUserProfileLoader.h"
#include "gData.h"

namespace SDPO {

/*****************************************************************/

IOUserProfileLoader::IOUserProfileLoader(QObject *parent) :
    IODataLoader("users.json", parent)
{
}

/*****************************************************************/

void IOUserProfileLoader::load()
{
    GData::userProfiles.clear();
    QString rawJson = readJsonFile();
    if (rawJson.size() == 0) return;

    QPair<QJsonDocument, QJsonParseError> jsonResult = getJsonDocument(rawJson);
    QJsonParseError jsonError = jsonResult.second;
    if (jsonError.error != QJsonParseError::NoError) {
        QString msg = tr("Error parsing JSON Users file at %1: %2").arg(jsonError.offset).arg(jsonError.errorString());
        sendErrorMessage(msg);
        return;
    }
    QJsonDocument jsonDoc = jsonResult.first;
    parseJsonData(jsonDoc);
}

/*****************************************************************/

void IOUserProfileLoader::save()
{
    QJsonDocument jsonDocument = createJsonDocument();
    writeJsonToStdConfigFile(QString(jsonDocument.toJson()));
}

/*****************************************************************/

void IOUserProfileLoader::parseJsonData(QJsonDocument json_doc)
{
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &item, json_array) {
        QJsonObject json_obj = item.toObject();
        GUserProfile profile;
        profile.id = json_obj["id"].toString();
        profile.name = json_obj["name"].toString();
        profile.password = json_obj["password"].toString();
        profile.enabled = json_obj["enabled"].toBool();
        profile.email = json_obj["email"].toString();
        profile.pager = json_obj["pager"].toString();
        profile.icq = json_obj["icq"].toString();
        profile.setStyle(json_obj["style"].toInt());
        profile.showGridLines = json_obj["showGridLines"].toBool();
        profile.gridForLogViewer = json_obj["gridForLogViewer"].toBool();
        profile.showTestsInSubfolders = json_obj["showTestsInSubfolders"].toBool();
        profile.colorScheme = json_obj["colorScheme"].toString();
        profile.ipmRefreshTime = json_obj["ipmRefreshTime"].toDouble();
        profile.ipmShowPacketsCounter = json_obj["ipmShowPacketsCounter"].toBool();
        profile.tcpMonitor = parseIPMonitor(json_obj["tcpMonitor"]);
        profile.udpMonitor = parseIPMonitor(json_obj["udpMonitor"]);
        profile.icmpMonitor = parseIPMonitor(json_obj["icmpMonitor"]);
        profile.columns = parseColumns(json_obj["columns"]);
        profile.sort = parseSort(json_obj["sort"]);
        GData::userProfiles.append(profile);
    }
}

/*****************************************************************/

QJsonDocument IOUserProfileLoader::createJsonDocument()
{
    QJsonArray jsonArray;
    foreach (const GUserProfile &profile, GData::userProfiles) {
         QJsonObject jsonObj;
         jsonObj.insert("id",QJsonValue(profile.id));
         jsonObj.insert("name",QJsonValue(profile.name));
         jsonObj.insert("password",QJsonValue(profile.password));
         jsonObj.insert("enabled",QJsonValue(profile.enabled));
         jsonObj.insert("email",QJsonValue(profile.email));
         jsonObj.insert("pager",QJsonValue(profile.pager));
         jsonObj.insert("icq",QJsonValue(profile.icq));
         jsonObj.insert("style",QJsonValue(profile.getStyle()));
         jsonObj.insert("showGridLines",QJsonValue(profile.showGridLines));
         jsonObj.insert("gridForLogViewer",QJsonValue(profile.gridForLogViewer));
         jsonObj.insert("showTestsInSubfolders",QJsonValue(profile.showTestsInSubfolders));
         jsonObj.insert("colorScheme",QJsonValue(profile.colorScheme));
         jsonObj.insert("ipmRefreshTime",QJsonValue(profile.ipmRefreshTime));
         jsonObj.insert("ipmShowPacketsCounter",QJsonValue(profile.ipmShowPacketsCounter));
         jsonObj.insert("tcpMonitor",jsonIPMonutor(profile.tcpMonitor));
         jsonObj.insert("udpMonitor",jsonIPMonutor(profile.udpMonitor));
         jsonObj.insert("icmpMonitor",jsonIPMonutor(profile.icmpMonitor));
         jsonObj.insert("columns",jsonColumns(profile.columns));
         jsonObj.insert("sort",jsonSort(profile.sort));
         jsonArray.append(QJsonValue(jsonObj));
    }
    QJsonDocument jsonDoc(jsonArray);
    return jsonDoc;
}

/*****************************************************************/

GIPMonitor IOUserProfileLoader::parseIPMonitor(const QJsonValue jsonValue)
{
    GIPMonitor result;
    QJsonObject json_obj = jsonValue.toObject();
    result.vLinesNumber = json_obj["vLinesNumber"].toInt();
    result.hLinesNumber = json_obj["hLinesNumber"].toInt();
    result.backgroundColor = QColor(json_obj["backgroundColor"].toString());
    result.gridColor = QColor(json_obj["gridColor"].toString());
    result.inPacketsColor = QColor(json_obj["inPacketsColor"].toString());
    result.outPacketsColor = QColor(json_obj["outPacketsColor"].toString());
    result.errorColor = QColor(json_obj["errorColor"].toString());
    return result;
}

/*****************************************************************/

QJsonValue IOUserProfileLoader::jsonIPMonutor(const GIPMonitor &value)
{
    QJsonObject jsonObj;
    jsonObj.insert("vLinesNumber",QJsonValue(value.vLinesNumber));
    jsonObj.insert("hLinesNumber",QJsonValue(value.hLinesNumber));
    jsonObj.insert("backgroundColor",QJsonValue(value.backgroundColor.name()));
    jsonObj.insert("gridColor",QJsonValue(value.gridColor.name()));
    jsonObj.insert("inPacketsColor",QJsonValue(value.inPacketsColor.name()));
    jsonObj.insert("outPacketsColor",QJsonValue(value.outPacketsColor.name()));
    jsonObj.insert("errorColor",QJsonValue(value.errorColor.name()));
    return QJsonValue(jsonObj);
}

/*****************************************************************/

QColumnList IOUserProfileLoader::parseColumns(const QJsonValue jsonValue)
{
    QColumnList result;
    foreach (const QJsonValue &value, jsonValue.toArray()) {
        QJsonObject json_obj = value.toObject();
        TLColumn column;
        column.title = json_obj["title"].toString();
        column.macro = json_obj["macro"].toString();
        column.checked = json_obj["checked"].toBool();
        result << column;
    }
    return result;
}

/*****************************************************************/

QJsonValue IOUserProfileLoader::jsonColumns(const QColumnList &value)
{
    QJsonArray result;
    foreach(const TLColumn &column, value) {
        QJsonObject jsonObj;
        jsonObj.insert("title",QJsonValue(column.title));
        jsonObj.insert("macro",QJsonValue(column.macro));
        jsonObj.insert("checked",QJsonValue(column.checked));
        result.append(QJsonValue(jsonObj));
    }
    return QJsonValue(result);
}

/*****************************************************************/

QSortPairList IOUserProfileLoader::parseSort(const QJsonValue jsonValue)
{
    QSortPairList result;
    foreach (const QJsonValue &value, jsonValue.toArray()) {
        QJsonObject json_obj = value.toObject();
        QPair<QString,bool> pair;
        pair.first = json_obj["column"].toString();
        pair.second = json_obj["asc"].toBool();
        result << pair;
    }
    return result;
}

/*****************************************************************/

QJsonValue IOUserProfileLoader::jsonSort(const QSortPairList &value)
{
    QJsonArray result;
    foreach(const QSortPair &pair, value) {
        QJsonObject jsonObj;
        jsonObj.insert("column",QJsonValue(pair.first));
        jsonObj.insert("asc",QJsonValue(pair.second));
        result.append(QJsonValue(jsonObj));
    }
    return QJsonValue(result);
}

/*****************************************************************/

} // namespace SDPO
