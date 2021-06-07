#ifndef GDATA_H
#define GDATA_H

#include "global/gProfiles.h"
#include "testmethod.h"

namespace SDPO {

/*****************************************************************/

enum class GConnectionMethod { cmKeepActive, cmReconnect };

/*****************************************************************/

struct GConnection {
    QString           resource; // Resource (UNC)
    QString           server;   // Server or Domain
    QString           login;
    QString           password;
    GConnectionMethod type;
    TMethodIdList     methods;

    GConnection() {
        clear();
    }

    void clear() {
        resource.clear();
        server.clear();
        login.clear();
        password.clear();
        type = GConnectionMethod::cmKeepActive;
        methods.clear();
    }
};

/*****************************************************************/

typedef QList<GActionProfile> GActionProfileList;
typedef QList<GColorProfile>  GColorProfileList;
typedef QList<GMailProfile>   GMailProfileList;
typedef QList<GUserProfile>   GUserProfileList;
typedef QList<GConnection>    GConnectionList;

/*****************************************************************/

class GData : public QObject
{
    Q_OBJECT

public:
    explicit GData(QObject *parent = nullptr);

    static GActionProfileList actionProfiles;
    static GColorProfileList  colorProfiles;
    static GMailProfileList   mailProfiles;
    static GUserProfileList   userProfiles;
    static QString            currentUser;
    static GConnectionList    connections;

    static GColorProfile getColorProfile(const QString name);
    static int getActionProfileIdx(const QString name);
    static GUserProfile getCurrentUserProfile();

};

/*****************************************************************/

} // namespace SDPO

#endif // GDATA_H
