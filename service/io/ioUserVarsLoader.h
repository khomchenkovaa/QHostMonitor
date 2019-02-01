#ifndef IOUSERVARSLOADER_H
#define IOUSERVARSLOADER_H

#include "ioDataLoader.h"

namespace SDPO {

class IOUserVarsLoader : public IODataLoader
{
    Q_OBJECT


public:
    explicit IOUserVarsLoader(QObject *parent = 0);

    void load();
    void save();

private:
    void parseJsonData(QJsonDocument json_doc);
    QJsonDocument createJsonDocument();
};

} // namespace SDPO

#endif // IOUSERVARSLOADER_H
