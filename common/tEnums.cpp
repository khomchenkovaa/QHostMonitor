#include "tEnums.h"

namespace SDPO {

/*****************************************************************/
// Test Status
const QStringList TEnums::testStatusList = QStringList()
        << QObject::tr("Not tested")      // NotTested
        << QObject::tr("Host is alive")   // HostAlive
        << QObject::tr("No answer")       // NoAnswer
        << QObject::tr("Unknown")         // Unknown
        << QObject::tr("Unknown host")    // UnknownHost
        << QObject::tr("Checking")        // Checking
        << QObject::tr("Resolving")       // Resolving
        << QObject::tr("Ok")              // Ok
        << QObject::tr("Bad")             // Bad
        << QObject::tr("Disabled")        // Disabled
        << QObject::tr("Bad contents")    // BadContents
        << QObject::tr("Wait for Master") // WaitForMaster
        << QObject::tr("Out of schedule") // OutOfSchedule
        << QObject::tr("Paused")          // Paused
        << QObject::tr("Warning")         // Warning
        << QObject::tr("Normal");         // Normal

/*****************************************************************/
// Simple Status
const QStringList TEnums::simpleStatusList = QStringList()
        << QObject::tr("UP")
        << QObject::tr("DOWN")
        << QObject::tr("UNKNOWN")
        << QObject::tr("WARNING");

/*****************************************************************/

const QStringList TEnums::permissions = QStringList()
        << QObject::tr("add tests/folders")                 // PRM_CREATE
        << QObject::tr("configure tests/folders")           // PRM_EDIT
        << QObject::tr("remove tests/folders")              // PRM_DELETE
        << QObject::tr("disable/enable tests")              // PRM_DISABLE
        << QObject::tr("reset statistic")                   // PRM_STATISTIC
        << QObject::tr("start/stop monitoring")             // PRM_MONITORING
        << QObject::tr("change options")                    // PRM_OPTIONS
        << QObject::tr("manage schedules")                  // PRM_SCHEDULES
        << QObject::tr("manage mail profiles")              // PRM_MAIL_PROFILES
        << QObject::tr("manage color profiles")             // PRM_COLOR_PROFILES
        << QObject::tr("manage report profiles")            // PRM_REPORT_PROFILES
        << QObject::tr("manage action profiles")            // PRM_ACTION_PROFILES
        << QObject::tr("manage user profiles")              // PRM_USER_PROFILES
        << QObject::tr("acknowledge test status")           // PRM_ACKNOWLEDGE
        << QObject::tr("pause/resume tests")                // PRM_PAUSE
        << QObject::tr("edit GUI options for the account")  // PRM_GUI
        << QObject::tr("edit GUI options for ALL accounts") // PRM_GUI_ALL
        << QObject::tr("view test settings (read-only)");   // PRM_READ

/*****************************************************************/

QString TEnums::testStatus(TestStatus status) {
    return testStatusList.at(static_cast<int>(status));
}

/*****************************************************************/

TestStatus TEnums::testStatusFromString(const QString &name) {
    int idx = testStatusList.indexOf(name);
    if (idx == -1) {
        return TestStatus::Unknown;
    }
    return static_cast<TestStatus>(idx);
}

/*****************************************************************/

QString TEnums::simpleStatus(SimpleStatusID status) {
    return simpleStatusList.at(static_cast<int>(status));
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
    return permissions.at(static_cast<int>(id));
}

/*****************************************************************/

MVariablesStruct TEnums::mVar(Macro::Variable mv) {
    if (static_cast<unsigned>(mv) >= mvVariablesList.size()) mv = Macro::Unknown;
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
