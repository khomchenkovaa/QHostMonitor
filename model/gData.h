#ifndef GDATA_H
#define GDATA_H

#include "global/gProfiles.h"

namespace SDPO {

typedef QList<GActionProfile> GActionProfileList;
typedef QList<GColorProfile> GColorProfileList;
typedef QList<GMailProfile> GMailProfileList;
typedef QList<GUserProfile> GUserProfileList;

class GData : public QObject
{
    Q_OBJECT

public:
    explicit GData(QObject *parent = 0);

    static GActionProfileList actionProfiles;
    static GColorProfileList colorProfiles;
    static GMailProfileList mailProfiles;
    static GUserProfileList userProfiles;
    static QString currentUser;

    static GColorProfile getColorProfile(const QString name);
    static int getActionProfileIdx(const QString name);
    static GUserProfile getCurrentUserProfile();

};

} // namespace SDPO

#endif // GDATA_H
