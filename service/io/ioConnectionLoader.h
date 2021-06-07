#ifndef IOCONNECTIONLOADER_H
#define IOCONNECTIONLOADER_H

#include "ioDataLoader.h"
#include "gData.h"

#define JSON_RESOUCE    "resource"
#define JSON_SERVER     "server"
#define JSON_LOGIN      "login"
#define JSON_PASSWORD   "password"
#define JSON_KEEP_ALIVE "keepAlive"
#define JSON_METHODS    "methods"

namespace SDPO {

class IOConnectionLoader : public IODataLoader
{
    Q_OBJECT
public:
    explicit IOConnectionLoader(QObject *parent = nullptr);

    void load();
    void save();
private:
    void parseJsonData(QJsonDocument json_doc);

    TMethodIdList parseJsonMethodList(const QJsonValue jsonValue);

};

} // namespace SDPO

#endif // IOCONNECTIONLOADER_H
