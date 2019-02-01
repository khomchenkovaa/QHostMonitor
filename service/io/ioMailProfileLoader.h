#ifndef IOMAILPROFILELOADER_H
#define IOMAILPROFILELOADER_H

#include "ioDataLoader.h"

namespace SDPO {

class IOMailProfileLoader : public IODataLoader
{
    Q_OBJECT
public:
    explicit IOMailProfileLoader(QObject *parent = 0);

    void load();
    void save();

private:
    void parseJsonData(QJsonDocument json_doc);
    QJsonDocument createJsonDocument();

};

} // namespace SDPO

#endif // IOMAILPROFILELOADER_H
