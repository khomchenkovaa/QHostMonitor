#ifndef IOHMLIST_H
#define IOHMLIST_H

#include "tEnums.h"
#include "method/sdpoTestMethodConverters.h"

#include <QPair>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>

namespace SDPO {

class HMListService;

class IOHMList : public QObject
{
    Q_OBJECT

    HMListService *m_HML;

    QString m_fileName;
    IOTestMethodConverter *m_curMethodConverter;
public:
    explicit IOHMList(HMListService *hml, QString fileName, QObject *parent = 0);
    ~IOHMList();

    bool load();
    bool save();

signals:
    void notifyStatusMessage(QString msg);

private:
    QPair<QJsonDocument, QJsonParseError> getJsonDocument(const QString &raw_json);
    QString readJsonFile();
    void sendErrorMessage(const QString &msg);
    bool parseJsonData(QJsonDocument json_doc);
    QJsonDocument createJsonDocument();
    bool writeJsonToFile(QFile &outFile, const QString &outJson);
};

} // namespace SDPO

#endif // IOHMLIST_H
