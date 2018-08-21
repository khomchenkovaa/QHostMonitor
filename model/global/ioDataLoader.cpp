#include "ioDataLoader.h"
#include <QStandardPaths>
#include <QDebug>

namespace SDPO {

/*****************************************************************/

IODataLoader::IODataLoader(QString resFile, QObject *parent) :
    QObject(parent),
    resourcePrefix(":/resources"),
    resourceFile(resFile)
{
}

/*****************************************************************/

QPair<QJsonDocument, QJsonParseError> IODataLoader::getJsonDocument(const QString &raw_json)
{
    QJsonParseError json_parse_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(raw_json.toUtf8(),
                                                     &json_parse_error);
    return QPair<QJsonDocument, QJsonParseError>(json_doc, json_parse_error);
}

/*****************************************************************/

QString IODataLoader::readJsonFile()
{
    QString defaultJson = readJsonFromResource();
    QDir configDir = openConfigDirectory();
    QString path = configDir.filePath(resourceFile);
    QFile stdFile(path);
    if (stdFile.exists()) {
        if (!stdFile.open(QFile::ReadOnly|QFile::Text)) {
            sendErrorMessage("Could not open " + path);
            return defaultJson;
        }
        defaultJson = stdFile.readAll();
        stdFile.close();
    } else {
        writeJsonToFile(stdFile, defaultJson);
    }
    return defaultJson;
}

/*****************************************************************/

QString IODataLoader::readJsonFromResource()
{
    QDir resDir (resourcePrefix);
    if (!resDir.exists()) {
        sendErrorMessage("Internal resource path missing " +
                         resDir.canonicalPath());
        return "";
    }
    QString path = resDir.filePath(resourceFile);
    QFile resFile(path);
    if (!resFile.open(QFile::ReadOnly | QFile::Text)) {
        sendErrorMessage("Cound not open internal resource " +
                         resourceFile);
        return "";
    }
    QString jsonData = resFile.readAll();

    return jsonData;
}

/*****************************************************************/

void IODataLoader::sendErrorMessage(const QString &msg)
{
    qDebug() << msg;
    emit notifyStatusMessage(msg);
}

/*****************************************************************/

QDir IODataLoader::openConfigDirectory()
{
    QDir configDir(QStandardPaths::writableLocation(
                        QStandardPaths::AppConfigLocation));
    if (!configDir.exists()) {
        QDir dir;
        if (!dir.mkpath(configDir.path())) {
            sendErrorMessage("Could not create configuration directory");
            abort();
        }
    }
    return configDir;
}

/*****************************************************************/

void IODataLoader::writeJsonToStdConfigFile(const QString &defJson)
{
    QDir configDir = openConfigDirectory();
    QString path = configDir.filePath(resourceFile);
    QFile stdFile(path);
    writeJsonToFile(stdFile, defJson);
}

/*****************************************************************/

void IODataLoader::writeJsonToFile(QFile &stdConfigFile, const QString &defJson)
{
    int length = defJson.length();
    if (!stdConfigFile.open(QFile::WriteOnly|QFile::Text)) {
        sendErrorMessage("Could not open file to write " + stdConfigFile.fileName());
    } else {
        qint64 bytesWritten = stdConfigFile.write(qPrintable(defJson),length);
        if (bytesWritten != length) {
          sendErrorMessage("Could not write default JSON to " + stdConfigFile.fileName());
          if (!stdConfigFile.remove()) {
              sendErrorMessage("Count not remove configuration file. Please delete " +
                               stdConfigFile.fileName());
          }
        }
        stdConfigFile.close();
    }
}

/*****************************************************************/

} // namespace SDPO
