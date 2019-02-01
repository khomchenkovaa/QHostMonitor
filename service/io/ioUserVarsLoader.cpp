#include "ioUserVarsLoader.h"
#include "global/gUserVars.h"
#include <QDebug>

namespace SDPO {

/*****************************************************************/

IOUserVarsLoader::IOUserVarsLoader(QObject *parent) :
    IODataLoader("userVars.json", parent)
{
}

/*****************************************************************/

void IOUserVarsLoader::load()
{
    GUserVars::variables.clear();
    QString rawJson = readJsonFile();
    if (rawJson.size() == 0) return;

    QPair<QJsonDocument, QJsonParseError> jsonResult = getJsonDocument(rawJson);
    QJsonParseError jsonError = jsonResult.second;
    if (jsonError.error != QJsonParseError::NoError) {
        QString msg = tr("Error parsing JSON User Vars file at %1: %2").arg(jsonError.offset).arg(jsonError.errorString());
        sendErrorMessage(msg);
        return;
    }
    QJsonDocument jsonDoc = jsonResult.first;
    parseJsonData(jsonDoc);
}

/*****************************************************************/

void IOUserVarsLoader::save()
{
    QJsonDocument jsonDocument = createJsonDocument();
    writeJsonToStdConfigFile(QString(jsonDocument.toJson()));
}


/*****************************************************************/

void IOUserVarsLoader::parseJsonData(QJsonDocument json_doc)
{
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &item, json_array) {
        QJsonObject json_obj = item.toObject();
        QString variable = json_obj["variable"].toString();
        QString value = json_obj["value"].toString();
        GUserVars::add(variable, value);
    }
}

/*****************************************************************/

QJsonDocument IOUserVarsLoader::createJsonDocument()
{
    QJsonArray jsonArray;
    QMapIterator<QString, QString> i(GUserVars::variables);
    while (i.hasNext()) {
         i.next();
         QJsonObject jsonObj;
         jsonObj.insert("variable",QJsonValue(i.key()));
         jsonObj.insert("value",QJsonValue(i.value()));
         jsonArray.append(QJsonValue(jsonObj));
    }
    QJsonDocument jsonDoc(jsonArray);
    return jsonDoc;
}

/*****************************************************************/

} // namespace SDPO
