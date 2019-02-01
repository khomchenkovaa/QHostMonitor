#ifndef IOUSERPROFILELOADER_H
#define IOUSERPROFILELOADER_H

#include "ioDataLoader.h"
#include "global/gProfiles.h"

namespace SDPO {

class IOUserProfileLoader : public IODataLoader
{
    Q_OBJECT
public:
    explicit IOUserProfileLoader(QObject *parent = 0);

    void load();
    void save();

private:
    void parseJsonData(QJsonDocument json_doc);
    QJsonDocument createJsonDocument();
    GIPMonitor parseIPMonitor(const QJsonValue jsonValue);
    QJsonValue jsonIPMonutor(const GIPMonitor &value);
    QColumnList parseColumns(const QJsonValue jsonValue);
    QJsonValue jsonColumns(const QColumnList &value);
    QSortPairList parseSort(const QJsonValue jsonValue);
    QJsonValue jsonSort(const QSortPairList &value);
    QIpPairList parseRccFrom(const QJsonValue jsonValue);
    QJsonValue jsonRccFrom(const QIpPairList &value);
    QFoldersList parseFolders(const QJsonValue jsonValue);
    QJsonValue jsonFolders(const QFoldersList &value);
};

} // namespace SDPO

#endif // IOUSERPROFILELOADER_H
