#include "ioColorProfileLoader.h"
#include "gData.h"

namespace SDPO {

/*****************************************************************/

IOColorProfileLoader::IOColorProfileLoader(QObject *parent) :
    IODataLoader("palettes.json", parent)
{
}

/*****************************************************************/

void IOColorProfileLoader::load()
{
    GData::colorProfiles.clear();
    QString rawJson = readJsonFile();
    if (rawJson.size() == 0) return;

    QPair<QJsonDocument, QJsonParseError> jsonResult = getJsonDocument(rawJson);
    QJsonParseError jsonError = jsonResult.second;
    if (jsonError.error != QJsonParseError::NoError) {
        QString msg = tr("Error parsing JSON Palettes file at %1: %2").arg(jsonError.offset).arg(jsonError.errorString());
        sendErrorMessage(msg);
        return;
    }
    QJsonDocument jsonDoc = jsonResult.first;
    parseJsonData(jsonDoc);
}

/*****************************************************************/

void IOColorProfileLoader::save()
{
    QJsonDocument jsonDocument = createJsonDocument();
    writeJsonToStdConfigFile(QString(jsonDocument.toJson()));
}

/*****************************************************************/

void IOColorProfileLoader::parseJsonData(QJsonDocument json_doc)
{
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &item, json_array) {
        QJsonObject json_obj = item.toObject();
        GColorProfile profile;
        profile.name = json_obj["name"].toString();
        profile.htmlText = parseColor(json_obj["htmlText"]);
        profile.header = parseColor(json_obj["header"]);
        profile.folder = parseColor(json_obj["folder"]);
        profile.testNotTested = parseColor(json_obj["testNotTested"]);
        profile.testOk = parseColor(json_obj["testOk"]);
        profile.testNormal = parseColor(json_obj["testNormal"]);
        profile.testWarning = parseColor(json_obj["testWarning"]);
        profile.testBad = parseColor(json_obj["testBad"]);
        profile.testAcknowledged = parseColor(json_obj["testAcknowledged"]);
        profile.testUnknown = parseColor(json_obj["testUnknown"]);
        profile.message = parseColor(json_obj["message"]);
        profile.testChecking = parseColor(json_obj["testChecking"]);
        profile.testDisabled = parseColor(json_obj["testDisabled"]);
        profile.testWaitForMaster = parseColor(json_obj["testWaitForMaster"]);
        profile.testOutOfSchedule = parseColor(json_obj["testOutOfSchedule"]);
        profile.links = parseColor(json_obj["links"]);
        profile.linkVisited = parseColor(json_obj["linkVisited"]);
        profile.linkActive = parseColor(json_obj["linkActive"]);

        GData::colorProfiles.append(profile);
    }
}

/*****************************************************************/

QJsonDocument IOColorProfileLoader::createJsonDocument()
{
    QJsonArray jsonArray;
    foreach (const GColorProfile &profile, GData::colorProfiles) {
         QJsonObject jsonObj;
         jsonObj.insert("name",QJsonValue(profile.name));
         jsonObj.insert("htmlText",jsonColor(profile.htmlText));
         jsonObj.insert("header",jsonColor(profile.header));
         jsonObj.insert("folder",jsonColor(profile.folder));
         jsonObj.insert("testNotTested",jsonColor(profile.testNotTested));
         jsonObj.insert("testOk",jsonColor(profile.testOk));
         jsonObj.insert("testNormal",jsonColor(profile.testNormal));
         jsonObj.insert("testWarning",jsonColor(profile.testWarning));
         jsonObj.insert("testBad",jsonColor(profile.testBad));
         jsonObj.insert("testAcknowledged",jsonColor(profile.testAcknowledged));
         jsonObj.insert("testUnknown",jsonColor(profile.testUnknown));
         jsonObj.insert("message",jsonColor(profile.message));
         jsonObj.insert("testChecking",jsonColor(profile.testChecking));
         jsonObj.insert("testDisabled",jsonColor(profile.testDisabled));
         jsonObj.insert("testWaitForMaster",jsonColor(profile.testWaitForMaster));
         jsonObj.insert("testOutOfSchedule",jsonColor(profile.testOutOfSchedule));
         jsonObj.insert("links",jsonColor(profile.links));
         jsonObj.insert("linkVisited",jsonColor(profile.linkVisited));
         jsonObj.insert("linkActive",jsonColor(profile.linkActive));

         jsonArray.append(QJsonValue(jsonObj));
    }
    QJsonDocument jsonDoc(jsonArray);
    return jsonDoc;
}

/*****************************************************************/

QColorList IOColorProfileLoader::parseColor(const QJsonValue jsonValue)
{
    QColorList result;
    foreach (const QJsonValue &line, jsonValue.toArray()) {
        result << QColor(line.toString());
    }
    return result;
}

/*****************************************************************/

QJsonValue IOColorProfileLoader::jsonColor(const QColorList &value)
{
    QJsonArray result;
    foreach(const QColor &color, value) {
        result.append(QJsonValue(color.name()));
    }
    return QJsonValue(result);
}

/*****************************************************************/

} // namespace SDPO
