#include "ioTestMethodLoader.h"
#include "testmethod.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

namespace SDPO {

/*****************************************************************/

IOTestMethodLoader::IOTestMethodLoader(QObject *parent) :
    IODataLoader("testMethod.json", parent)
{
}

/*****************************************************************/

void IOTestMethodLoader::load()
{
    QString rawJson = readJsonFromResource();
    if (rawJson.size() == 0) return;

    QPair<QJsonDocument, QJsonParseError> jsonResult = getJsonDocument(rawJson);
    QJsonParseError jsonError = jsonResult.second;
    if (jsonError.error != QJsonParseError::NoError) {
        QString msg = tr("Error parsing JSON Test Method file at %1: %2").arg(jsonError.offset).arg(jsonError.errorString());
        sendErrorMessage(msg);
        return;
    }
    QJsonDocument jsonDoc = jsonResult.first;
    loadGroups(jsonDoc.object());
    loadMethods(jsonDoc.object());
}

/*****************************************************************/

void IOTestMethodLoader::loadGroups(QJsonObject json_obj)
{
    QJsonArray group_array = json_obj["groups"].toArray();
    foreach (const QJsonValue &item, group_array) {
        QJsonObject jsonGroup = item.toObject();
        TestGroup group;
        group.id = jsonGroup["id"].toInt();
        group.name = jsonGroup["name"].toString();
        group.icon = jsonGroup["icon"].toString();
        group.parent = jsonGroup["parent"].toInt();
        QJsonArray descr_array = jsonGroup["description"].toArray();
        foreach (const QJsonValue &descr, descr_array) {
            group.description << descr.toString();
        }
        TestMethod::groups.append(group);
    }
}

/*****************************************************************/

void IOTestMethodLoader::loadMethods(QJsonObject json_obj)
{
    QJsonArray test_array = json_obj["tests"].toArray();
    foreach (const QJsonValue &item, test_array) {
        QJsonObject jsonTest = item.toObject();
        TestMethodMetaInfo method;
        method.id = static_cast<TMethodID>(jsonTest["id"].toInt());
        method.name = jsonTest["name"].toString();
        method.title = jsonTest["title"].toString();
        method.text = jsonTest["text"].toString();
        method.icon = jsonTest["icon"].toString();
        method.html = jsonTest["html"].toString();
        method.parent = jsonTest["parent"].toInt();
        method.active = (jsonTest["active"].toString() == "yes");
        method.namePattern = jsonTest["testname"].toString();
        method.commentPattern = jsonTest["comment"].toString();
        QJsonArray descr_array = jsonTest["description"].toArray();
        foreach (const QJsonValue &descr, descr_array) {
            method.description << descr.toString();
        }
        TestMethod::metaInfo.append(method);
    }
}

/*****************************************************************/

} // namespace SDPO
