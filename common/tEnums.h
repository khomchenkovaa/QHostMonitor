/********************************************************************
 * Represents Enumerators: TestingMethod, SimpleStatus, TestStatus
 * ******************************************************************/
#pragma once

#include "xMacroVar.h"
#include <QString>
#include <QDebug>

namespace SDPO {

/*****************************************************************/

enum class TestStatus {
    NotTested,   // Special
    HostAlive,   // Good
    NoAnswer,    // Bad
    Unknown,
    UnknownHost, // Unknown, might be processed as “bad” statuses depending on “Treat Unknown status as Bad” option
    Checking,    // Special
    Resolving,   // Special
    Ok,          // Good
    Bad,         // Bad
    Disabled,    // Inactive
    BadContents, // Bad
    WaitForMaster,
    OutOfSchedule,
    Paused,      // Inactive
    Warning,     // User defined, might be processed as “bad” statuses depending on “Treat Warning status as Bad” option
    Normal       // User defined
};

struct TestStatusStruct {
    TestStatus id;
    QString name;
};

/*****************************************************************/

enum class SimpleStatusID {
    UP = 0,
    DOWN,
    UNKNOWN,
    WARNING
};

struct SimpleStatusStruct {
    SimpleStatusID id;
    QString name;
};

/*****************************************************************/

class TEnums {

    static std::vector<TestStatusStruct> testStatusList;
    static std::vector<SimpleStatusStruct>simpleStatusList;

public:
    static QString testStatus(TestStatus status);
    static TestStatus testStatusFromString(const QString name);
    static QString simpleStatus(SimpleStatusID status);
    static MVariablesStruct mVar(Macro::Variable mv);
    static Macro::Variable mvFromString(const QString name);

};

/*****************************************************************/

} // namespace SDPO
