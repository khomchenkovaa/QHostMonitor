#ifndef GDATA_H
#define GDATA_H

#include "global/gProfiles.h"
#include "global/gConnection.h"
#include "snmp.h"

namespace SDPO {

typedef QList<GActionProfile> GActionProfileList;
typedef QList<GColorProfile>  GColorProfileList;
typedef QList<GMailProfile>   GMailProfileList;
typedef QList<GUserProfile>   GUserProfileList;
typedef QList<GConnection>    GConnectionList;
typedef QList<SnmpProfile>    GSnmpCredentials;

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
    static GSnmpCredentials   snmpCredentials;

    static GColorProfile getColorProfile(const QString name);
    static int getActionProfileIdx(const QString name);
    static SnmpProfile getSnmpProfile(const QString& name);
    static GUserProfile getCurrentUserProfile();

};

} // namespace SDPO

#endif // GDATA_H
