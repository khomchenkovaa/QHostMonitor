#include "tEnums.h"
#include "QString"

namespace SDPO {

/*****************************************************************/

std::vector<TestStatusStruct> TEnums::testStatusList = {
    { TestStatus::NotTested,     "Not tested" },
    { TestStatus::HostAlive,     "Host is alive" },
    { TestStatus::NoAnswer,      "No answer" },
    { TestStatus::Unknown,       "Unknown" },
    { TestStatus::UnknownHost,   "Unknown host" },
    { TestStatus::Checking,      "Checking" },
    { TestStatus::Resolving,     "Resolving" },
    { TestStatus::Ok,            "Ok" },
    { TestStatus::Bad,           "Bad" },
    { TestStatus::Disabled,      "Disabled" },
    { TestStatus::BadContents,   "Bad contents" },
    { TestStatus::WaitForMaster, "Wait for Master" },
    { TestStatus::OutOfSchedule, "Out of schedule" },
    { TestStatus::Paused,        "Paused" },
    { TestStatus::Warning,       "Warning" },
    { TestStatus::Normal,        "Normal" }
};

/*****************************************************************/

std::vector<SimpleStatusStruct> TEnums::simpleStatusList = {
    { SimpleStatusID::UP,      "UP" },
    { SimpleStatusID::DOWN,    "DOWN" },
    { SimpleStatusID::UNKNOWN, "UNKNOWN" },
    { SimpleStatusID::WARNING, "WARNING" }
};

/*****************************************************************/

QStringList TEnums::permissions;

/*****************************************************************/

void TEnums::init()
{
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
    if ((unsigned)status >= testStatusList.size()) status = TestStatus::Unknown;
    return testStatusList.at((unsigned)status).name;
}

/*****************************************************************/

TestStatus TEnums::testStatusFromString(const QString name) {
    TestStatus result = TestStatus::Unknown;
    for(unsigned i=0;i<testStatusList.size();++i) {
        if (testStatusList.at(i).name == name ) {
            result = testStatusList.at(i).id;
            break;
        }
    }
    return result;
}

/*****************************************************************/

QString TEnums::simpleStatus(SimpleStatusID status) {
    if ((unsigned)status >= simpleStatusList.size()) status = SimpleStatusID::UNKNOWN;
    return simpleStatusList.at((unsigned)status).name;
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
