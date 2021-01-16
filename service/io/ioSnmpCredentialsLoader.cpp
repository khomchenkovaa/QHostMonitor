#include "ioSnmpCredentialsLoader.h"
#include "snmp.h"
#include "snmpprofile.h"

using namespace SDPO;

#define IO_SNMP_VERSION_1  "SNMP v1"
#define IO_SNMP_VERSION_2c "SNMP v2c"
#define IO_SNMP_VERSION_3  "SNMP v3"

/*****************************************************************/

IOSnmpCredentialsLoader::IOSnmpCredentialsLoader(QObject *parent)
    : IODataLoader("snmpCredentials.json", parent)
{

}

/*****************************************************************/

void IOSnmpCredentialsLoader::load()
{
    SnmpProfile::credentials.clear();
    QString rawJson = readJsonFile();
    if (rawJson.size() == 0) return;

    QPair<QJsonDocument, QJsonParseError> jsonResult = getJsonDocument(rawJson);
    QJsonParseError jsonError = jsonResult.second;
    if (jsonError.error != QJsonParseError::NoError) {
        QString msg = tr("Error parsing JSON Snmp Profile List file at %1: %2").arg(jsonError.offset).arg(jsonError.errorString());
        sendErrorMessage(msg);
        return;
    }
    QJsonDocument jsonDoc = jsonResult.first;
    parseJsonData(jsonDoc);
}

/*****************************************************************/

void IOSnmpCredentialsLoader::save()
{
    QJsonDocument jsonDocument = createJsonDocument();
    writeJsonToStdConfigFile(QString(jsonDocument.toJson()));
}

/*****************************************************************/

void IOSnmpCredentialsLoader::parseJsonData(QJsonDocument json_doc)
{
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &item, json_array) {
        QJsonObject json_obj = item.toObject();
        SnmpProfile profile;
        profile.name = json_obj["name"].toString();
        QString version = json_obj["type"].toString();
        if (version.compare(IO_SNMP_VERSION_1) == 0) {
            profile.version = SNMPv1;
        } else if (version.compare(IO_SNMP_VERSION_2c) == 0) {
            profile.version = SNMPv2c;
        } else if (version.compare(IO_SNMP_VERSION_3) == 0) {
            profile.version = SNMPv3;
        }
        profile.community = json_obj["community"].toString();
        if (profile.version == SNMPv3) {
            //! TODO parse SNMP v3 properties
        }
        SnmpProfile::credentials.append(profile);
    }
}

/*****************************************************************/

QJsonDocument IOSnmpCredentialsLoader::createJsonDocument()
{
    QJsonArray jsonArray;
    foreach (const SnmpProfile &profile, SnmpProfile::credentials) {
         QJsonObject jsonObj;
         jsonObj.insert("name",QJsonValue(profile.name));
         QString version = IO_SNMP_VERSION_2c;
         switch (profile.version) {
         case SNMPv1:
             version = IO_SNMP_VERSION_1;
             break;
         case SNMPv3:
             version = IO_SNMP_VERSION_3;
             break;
         default:
             break;
         }
         jsonObj.insert("version",QJsonValue(version));
         jsonObj.insert("community",QJsonValue(profile.community));
         if (profile.version == SNMPv3) {
             //! TODO insert SNMP v3 properties
         }
         jsonArray.append(QJsonValue(jsonObj));
    }
    QJsonDocument jsonDoc(jsonArray);
    return jsonDoc;
}

/*****************************************************************/
