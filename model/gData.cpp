#include "gData.h"

namespace SDPO {

/*****************************************************************/

GActionProfileList GData::actionProfiles;

/*****************************************************************/

GColorProfileList GData::colorProfiles;

/*****************************************************************/

GMailProfileList GData::mailProfiles;

/*****************************************************************/

GUserProfileList GData::userProfiles;

/*****************************************************************/

QString GData::currentUser = "local";

/*****************************************************************/

GConnectionList GData::connections;

/*****************************************************************/

GSnmpCredentials GData::snmpCredentials;

/*****************************************************************/

GData::GData(QObject *parent) :
    QObject(parent)
{
}

/*****************************************************************/

GColorProfile GData::getColorProfile(const QString name)
{
    int idx = 0;
    for (int i=0; i< colorProfiles.count(); i++) {
        if (name == colorProfiles.at(i).name) {
            idx = i;
        }
    }
    return colorProfiles.at(idx);
}

/*****************************************************************/

int GData::getActionProfileIdx(const QString name)
{
    int idx = -1; // not found
    for (int i=0; i< actionProfiles.count(); i++) {
        if (name == actionProfiles.at(i).name) {
            idx = i;
        }
    }
    return idx;
}

/*****************************************************************/

SnmpProfile GData::getSnmpProfile(const QString &name)
{
    int idx = 1; // not found
    for (int i=0; i< snmpCredentials.count(); i++) {
        if (name == snmpCredentials.at(i).name) {
            idx = i;
        }
    }
    return snmpCredentials.at(idx);
}

/*****************************************************************/

GUserProfile GData::getCurrentUserProfile()
{
     GUserProfile result;
     for (int i=0; i< userProfiles.count(); i++) {
         if (currentUser == userProfiles.at(i).id) {
             result = userProfiles.at(i);
         }
     }
     return result;
}

/*****************************************************************/

} // namespace SDPO
