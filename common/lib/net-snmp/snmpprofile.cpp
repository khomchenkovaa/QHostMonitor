#include "snmpprofile.h"

using namespace SDPO;

/*****************************************************************/

GSnmpCredentials SnmpProfile::credentials;

/*****************************************************************/

SnmpProfile SnmpProfile::findByName(const QString &name)
{
    int idx = defaultIdx(); // not found
    for (int i=0; i< credentials.count(); i++) {
        if (name == credentials.at(i).name) {
            idx = i;
        }
    }
    return credentials.at(idx);
}

/*****************************************************************/

QStringList SnmpProfile::names()
{
    QStringList result;
    foreach(const SnmpProfile& item, credentials) {
        result.append(item.name);
    }
    return result;
}

/*****************************************************************/

int SnmpProfile::defaultIdx()
{
    int idx = -1;
    for (int i=0; i< credentials.count(); i++) {
        if (idx == -1) idx = i;
        if (credentials.at(i).version == SNMPv2c) {
            idx = i;
            break;
        }
    }
    return idx;
}

/*****************************************************************/

