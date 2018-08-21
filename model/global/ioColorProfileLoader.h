#ifndef IOCOLORPROFILELOADER_H
#define IOCOLORPROFILELOADER_H

#include "ioDataLoader.h"
#include "global/gProfiles.h"

namespace SDPO {

class IOColorProfileLoader : public IODataLoader
{
    Q_OBJECT
public:
    explicit IOColorProfileLoader(QObject *parent = 0);

    void load();
    void save();

private:
    void parseJsonData(QJsonDocument json_doc);
    QJsonDocument createJsonDocument();
    QColorList parseColor(const QJsonValue jsonValue);
    QJsonValue jsonColor(const QColorList &value);

};

} // namespace SDPO

#endif // IOCOLORPROFILELOADER_H
