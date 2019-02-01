#ifndef HIOTESTMETHODLOADER_H
#define HIOTESTMETHODLOADER_H

#include "ioDataLoader.h"

namespace SDPO {

class IOTestMethodLoader : public IODataLoader
{
    Q_OBJECT
public:
    explicit IOTestMethodLoader(QObject *parent = 0);

public:
    void load();

private:
    void loadGroups(QJsonObject json_obj);
    void loadMethods(QJsonObject json_obj);
};

} // namespace SDPO

#endif // HIOTESTMETHODLOADER_H
