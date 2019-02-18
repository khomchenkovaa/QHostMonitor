#include "ioConnectionLoader.h"
#include "gData.h"

namespace SDPO {

/*****************************************************************/

IOConnectionLoader::IOConnectionLoader(QObject *parent) :
    IODataLoader("connection.json", parent)
{    
}

/*****************************************************************/

void IOConnectionLoader::load()
{
    GData::connections.clear();
    QString rawJson = readJsonFile();
    if (rawJson.size() == 0) return;

    QPair<QJsonDocument, QJsonParseError> jsonResult = getJsonDocument(rawJson);
    QJsonParseError jsonError = jsonResult.second;
    if (jsonError.error != QJsonParseError::NoError) {
        QString msg = tr("Error parsing JSON Connections file at %1: %2").arg(jsonError.offset).arg(jsonError.errorString());
        sendErrorMessage(msg);
        return;
    }
    QJsonDocument jsonDoc = jsonResult.first;
    parseJsonData(jsonDoc);

}

/*****************************************************************/

void IOConnectionLoader::save()
{

}

/*****************************************************************/

void IOConnectionLoader::parseJsonData(QJsonDocument json_doc)
{
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &item, json_array) {
        QJsonObject json_obj = item.toObject();
        GConnection conn;
        conn.resource = json_obj[JSON_RESOUCE].toString();
        conn.server = json_obj[JSON_SERVER].toString();
        conn.login = json_obj[JSON_LOGIN].toString();
        conn.password = json_obj[JSON_PASSWORD].toString();
        conn.type = json_obj[JSON_KEEP_ALIVE].toBool() ? GConnectionMethod::cmKeepActive : GConnectionMethod::cmReconnect;
        conn.methods = parseJsonMethodList(json_obj[JSON_METHODS]);
        GData::connections.append(conn);
    }
}

/*****************************************************************/

TMethodIdList IOConnectionLoader::parseJsonMethodList(const QJsonValue jsonValue)
{
    TMethodIdList result;
    foreach(const QJsonValue &value, jsonValue.toArray()) {
        TMethodID mId = TMethod::fromString(value.toString());
        if (mId != TMethodID::Empty) {
            result.append(mId);
        }
    }
    return result;
}

/*****************************************************************/

} // namespace SDPO
