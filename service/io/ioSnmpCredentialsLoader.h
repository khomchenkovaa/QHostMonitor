#ifndef IOSNMPCREDENTIALSLOADER_H
#define IOSNMPCREDENTIALSLOADER_H

#include "ioDataLoader.h"

namespace SDPO {

class IOSnmpCredentialsLoader : public IODataLoader
{
    Q_OBJECT
public:
    IOSnmpCredentialsLoader(QObject *parent = nullptr);

    void load();
    void save();

private:
    void parseJsonData(QJsonDocument json_doc);
    QJsonDocument createJsonDocument();
};

} // namespace SDPO

#endif // IOSNMPCREDENTIALSLOADER_H
