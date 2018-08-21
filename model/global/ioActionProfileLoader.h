#ifndef IOACTIONPROFILELOADER_H
#define IOACTIONPROFILELOADER_H

#include <QTime>
#include "ioDataLoader.h"
#include "action/tTestAction.h"

namespace SDPO {

class IOActionProfileLoader : public IODataLoader
{
    Q_OBJECT
public:
    explicit IOActionProfileLoader(QObject *parent = 0);

    void load();
    void save();

private:
    void parseJsonData(QJsonDocument json_doc);
    TestAction *parseAction(QJsonObject json_obj);
    QJsonDocument createJsonDocument();
    QJsonValue createActionValue(TestAction *action);
};

} // namespace SDPO

#endif // IOACTIONPROFILELOADER_H
