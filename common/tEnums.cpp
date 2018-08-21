#include "tEnums.h"

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
