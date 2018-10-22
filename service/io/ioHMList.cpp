#include "ioHMList.h"

#include "utils.h"
#include "hmListService.h"
#include "gData.h"
#include "gSettings.h"

#include <QDebug>


namespace SDPO {

/******************************************************************/

IOHMList::IOHMList(HMListService *hml, QString fileName, QObject *parent) :
    QObject(parent),
    m_HML(hml),
    m_fileName(fileName)
{
    m_curMethodConverter = 0;
}

/******************************************************************/

IOHMList::~IOHMList()
{
    Utils::DestructorMsg(this);
    if (m_curMethodConverter) {
        delete m_curMethodConverter;
        m_curMethodConverter = 0;
    }
}

/******************************************************************/

bool IOHMList::load()
{
    QString rawJson = readJsonFile();
    if (rawJson.isEmpty()) return false;

    QPair<QJsonDocument, QJsonParseError> jsonResult = getJsonDocument(rawJson);
    QJsonParseError jsonError = jsonResult.second;
    if (jsonError.error != QJsonParseError::NoError) {
        QString msg = tr("Error parsing HML file at %1: %2").arg(jsonError.offset).arg(jsonError.errorString());
        sendErrorMessage(msg);
        return false;
    }
    QJsonDocument jsonDoc = jsonResult.first;
    return parseJsonData(jsonDoc);
}

/******************************************************************/

bool IOHMList::save()
{
    QJsonDocument jsonDocument = createJsonDocument();
    QFile outFile(m_fileName);
    return writeJsonToFile(outFile, QString(jsonDocument.toJson()));
}

/******************************************************************/

QPair<QJsonDocument, QJsonParseError> IOHMList::getJsonDocument(const QString &raw_json)
{
    QJsonParseError json_parse_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(raw_json.toUtf8(),&json_parse_error);
    return QPair<QJsonDocument, QJsonParseError>(json_doc, json_parse_error);
}

/******************************************************************/

QString IOHMList::readJsonFile()
{
    QFile stdFile(m_fileName);
    if (!stdFile.exists()) {
        sendErrorMessage(tr("File '%1' does not exists").arg(m_fileName));
        return QString();
    }
    if (!stdFile.open(QFile::ReadOnly|QFile::Text)) {
        sendErrorMessage(tr("Could not open '%1' to read").arg(m_fileName));
        return QString();
    }
    QString fileContent = stdFile.readAll();
    stdFile.close();
    return fileContent;
}

/******************************************************************/

void IOHMList::sendErrorMessage(const QString &msg)
{
    qDebug() << msg;
    emit notifyStatusMessage(msg);
}

/******************************************************************/

bool IOHMList::parseJsonData(QJsonDocument json_doc)
{
    Q_UNUSED(json_doc)
    return false;
}

/******************************************************************/

QJsonDocument IOHMList::createJsonDocument()
{
    QSettings s;
    QJsonObject jsonObj;
    jsonObj.insert("GUID", QJsonValue(m_HML->guid().toString()));
    jsonObj.insert("count", QJsonValue(TRoot::counter()));
    if (s.value(SKEY_MISC_StoreStatistics, 1).toInt()) {
        // Store statistics
    }
    if (s.value(SKEY_MISC_StoreIterations, 1).toInt()) {
        // Store iterations
    }
    if (s.value(SKEY_INTERFACE_SaveCurrFolder, 1).toInt()) {
        // Store current folder
    }
    QJsonDocument jsonDoc(jsonObj);
    return jsonDoc;
}

/******************************************************************/

bool IOHMList::writeJsonToFile(QFile &outFile, const QString &outJson)
{
    int length = outJson.length();
    if (!outFile.open(QFile::WriteOnly|QFile::Text)) {
        sendErrorMessage(tr("Could not open file '%1' to write").arg(outFile.fileName()));
        return false;
    }

    qint64 bytesWritten = outFile.write(qUtf8Printable(outJson),length);
    outFile.close();

    if (bytesWritten != length) {
        sendErrorMessage(tr("Could not write HMList to %1").arg(outFile.fileName()));
        if (!outFile.remove()) {
            sendErrorMessage(tr("Count not remove file %1. Please delete manualy").arg(outFile.fileName()));
        }
        return false;
    }
    return true;
}

/******************************************************************/

} // namespace SDPO
