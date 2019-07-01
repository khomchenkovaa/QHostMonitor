#ifndef IODATALOADER_H
#define IODATALOADER_H

#include <QObject>
#include <QString>
#include <QPair>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>

namespace SDPO {

class IODataLoader : public QObject
{
    Q_OBJECT


public:
    explicit IODataLoader(QString resFile, QObject *parent = nullptr);

signals:
    void notifyStatusMessage(QString msg);

protected:
    QString resourcePrefix;
    QString resourceFile;

    QPair<QJsonDocument, QJsonParseError> getJsonDocument(const QString &raw_json);
    QString readJsonFile();
    QString readJsonFromResource();
    void sendErrorMessage(const QString &msg);
    QDir openConfigDirectory();
    void writeJsonToStdConfigFile(const QString &defJson);
    void writeJsonToFile(QFile &stdConfigFile, const QString &defJson);

};

} // namespace SDPO

#endif // IODATALOADER_H
