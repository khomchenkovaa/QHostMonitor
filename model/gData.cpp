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
