#include "tEnums.h"

namespace SDPO {

/*****************************************************************/

QStringList TEnums::testStatusList;
QStringList TEnums::simpleStatusList;
QStringList TEnums::permissions;

/*****************************************************************/

void TEnums::init()
{
    // Test Status
    if (testStatusList.count()) return;
    testStatusList << QObject::tr("Not tested");      // NotTested
    testStatusList << QObject::tr("Host is alive");   // HostAlive
    testStatusList << QObject::tr("No answer");       // NoAnswer
    testStatusList << QObject::tr("Unknown");         // Unknown
    testStatusList << QObject::tr("Unknown host");    // UnknownHost
    testStatusList << QObject::tr("Checking");        // Checking
    testStatusList << QObject::tr("Resolving");       // Resolving
    testStatusList << QObject::tr("Ok");              // Ok
    testStatusList << QObject::tr("Bad");             // Bad
    testStatusList << QObject::tr("Disabled");        // Disabled
    testStatusList << QObject::tr("Bad contents");    // BadContents
    testStatusList << QObject::tr("Wait for Master"); // WaitForMaster
    testStatusList << QObject::tr("Out of schedule"); // OutOfSchedule
    testStatusList << QObject::tr("Paused");          // Paused
    testStatusList << QObject::tr("Warning");         // Warning
    testStatusList << QObject::tr("Normal");          // Normal

    // Simple Status
    if (simpleStatusList.count()) return;
    simpleStatusList << QObject::tr("UP");      // UP
    simpleStatusList << QObject::tr("DOWN");    // DOWN
    simpleStatusList << QObject::tr("UNKNOWN"); // UNKNOWN
    simpleStatusList << QObject::tr("WARNING"); // WARNING

    // User permissions
    if (permissions.count()) return;
    permissions << QObject::tr("add tests/folders");                 // PRM_CREATE
    permissions << QObject::tr("configure tests/folders");           // PRM_EDIT
    permissions << QObject::tr("remove tests/folders");              // PRM_DELETE
    permissions << QObject::tr("disable/enable tests");              // PRM_DISABLE
    permissions << QObject::tr("reset statistic");                   // PRM_STATISTIC
    permissions << QObject::tr("start/stop monitoring");             // PRM_MONITORING
    permissions << QObject::tr("change options");                    // PRM_OPTIONS
    permissions << QObject::tr("manage schedules");                  // PRM_SCHEDULES
    permissions << QObject::tr("manage mail profiles");              // PRM_MAIL_PROFILES
    permissions << QObject::tr("manage color profiles");             // PRM_COLOR_PROFILES
    permissions << QObject::tr("manage report profiles");            // PRM_REPORT_PROFILES
    permissions << QObject::tr("manage action profiles");            // PRM_ACTION_PROFILES
    permissions << QObject::tr("manage user profiles");              // PRM_USER_PROFILES
    permissions << QObject::tr("acknowledge test status");           // PRM_ACKNOWLEDGE
    permissions << QObject::tr("pause/resume tests");                // PRM_PAUSE
    permissions << QObject::tr("edit GUI options for the account");  // PRM_GUI
    permissions << QObject::tr("edit GUI options for ALL accounts"); // PRM_GUI_ALL
    permissions << QObject::tr("view test settings (read-only)");    // PRM_READ
}

/*****************************************************************/

QString TEnums::testStatus(TestStatus status) {
    return testStatusList.at((int)status);
}

/*****************************************************************/

TestStatus TEnums::testStatusFromString(const QString &name) {
    int idx = testStatusList.indexOf(name);
    if (idx == -1) {
        return TestStatus::Unknown;
    }
    return (TestStatus)idx;
}

/*****************************************************************/

QString TEnums::simpleStatus(SimpleStatusID status) {
    return simpleStatusList.at((int)status);
}

/*****************************************************************/

SimpleStatusID TEnums::simpleStatusFromString(const QString &name, bool *ok)
{
    if (name == "Up" || name == "Good") {
        if (ok) *ok = true;
        return SimpleStatusID::UP;
    } else if (name == "Down" || name == "Bad"){
        if (ok) *ok = true;
        return SimpleStatusID::DOWN;
    } else if (name == "Unknown"){
        if (ok) *ok = true;
        return SimpleStatusID::UNKNOWN;
    } else if (name == "Warning"){
        if (ok) *ok = true;
        return SimpleStatusID::WARNING;
    }
    if (ok) *ok = false;
    return SimpleStatusID::UNKNOWN;
}

/*****************************************************************/

QString TEnums::permissionName(const PermissionID id)
{
    return permissions.at((int)id);
}

/*****************************************************************/

MVariablesStruct TEnums::mVar(Macro::Variable mv) {
    if ((unsigned)mv >= mvVariablesList.size()) mv = Macro::Unknown;
    return mvVariablesList.at(mv);
}

/*****************************************************************/

Macro::Variable TEnums::mvFromString(const QString name) {
    Macro::Variable result = Macro::Unknown;
    for(unsigned i=0;i<mvVariablesList.size();++i) {
        if ( name.compare(mvVariablesList.at(i).name, Qt::CaseInsensitive) == 0 ) {
            result = mvVariablesList.at(i).id;
            break;
        }
    }
    return result;
}

/*****************************************************************/

} // namespace SDPO
