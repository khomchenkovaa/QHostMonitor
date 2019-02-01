#include "ioMailProfileLoader.h"
#include "gData.h"

namespace SDPO {

/*****************************************************************/

IOMailProfileLoader::IOMailProfileLoader(QObject *parent) :
    IODataLoader("mailList.json", parent)
{
}

/*****************************************************************/

void IOMailProfileLoader::load()
{
    GData::mailProfiles.clear();
    QString rawJson = readJsonFile();
    if (rawJson.size() == 0) return;

    QPair<QJsonDocument, QJsonParseError> jsonResult = getJsonDocument(rawJson);
    QJsonParseError jsonError = jsonResult.second;
    if (jsonError.error != QJsonParseError::NoError) {
        QString msg = tr("Error parsing JSON Mail List file at %1: %2").arg(jsonError.offset).arg(jsonError.errorString());
        sendErrorMessage(msg);
        return;
    }
    QJsonDocument jsonDoc = jsonResult.first;
    parseJsonData(jsonDoc);
}

/*****************************************************************/

void IOMailProfileLoader::save()
{
    QJsonDocument jsonDocument = createJsonDocument();
    writeJsonToStdConfigFile(QString(jsonDocument.toJson()));
}

/*****************************************************************/

void IOMailProfileLoader::parseJsonData(QJsonDocument json_doc)
{
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &item, json_array) {
        QJsonObject json_obj = item.toObject();
        GMailProfile profile;
        profile.name = json_obj["name"].toString();
        profile.type = json_obj["type"].toString();
        profile.charset = json_obj["charset"].toString();
        QJsonArray body_array = json_obj["body"].toArray();
        foreach (const QJsonValue &line, body_array) {
            profile.body << line.toString();
        }
        GData::mailProfiles.append(profile);
    }
}

/*****************************************************************/

QJsonDocument IOMailProfileLoader::createJsonDocument()
{
    QJsonArray jsonArray;
    foreach (const GMailProfile &profile, GData::mailProfiles) {
         QJsonObject jsonObj;
         jsonObj.insert("name",QJsonValue(profile.name));
         jsonObj.insert("type",QJsonValue(profile.type));
         jsonObj.insert("charset",QJsonValue(profile.charset));
         QJsonArray body_array;
         foreach(const QString &line, profile.body) {
             body_array.append(QJsonValue(line));
         }
         jsonObj.insert("body", QJsonValue(body_array));
         jsonArray.append(QJsonValue(jsonObj));
    }
    QJsonDocument jsonDoc(jsonArray);
    return jsonDoc;
}

/*****************************************************************/

} // namespace SDPO
