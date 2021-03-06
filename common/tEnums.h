#ifndef TENUMS_H
#define TENUMS_H
/********************************************************************
** Represents Enumerators:
** TestStatus, SimpleStatus, Prmissions
** ******************************************************************/

#include <QObject>
#include <QString>

namespace SDPO {

//! Test status enumerator
enum class TestStatus {
    NotTested,   //!< Special
    HostAlive,   //!< Good
    NoAnswer,    //!< Bad
    Unknown,
    UnknownHost, //!< Unknown, might be processed as “bad” statuses depending on “Treat Unknown status as Bad” option
    Checking,    //!< Special
    Resolving,   //!< Special
    Ok,          //!< Good
    Bad,         //!< Bad
    Disabled,    //!< Inactive
    BadContents, //!< Bad
    WaitForMaster,
    OutOfSchedule,
    Paused,      //!< Inactive
    Warning,     //!< User defined, might be processed as “bad” statuses depending on “Treat Warning status as Bad” option
    Normal       //!< User defined
};

/*****************************************************************/

enum class SimpleStatusID {
    UP = 0,
    DOWN,
    UNKNOWN,
    WARNING
};


//! Permissions enumerator
enum class PermissionID {
    PRM_CREATE,          //!< add tests/folders
    PRM_EDIT,            //!< configure tests/folders
    PRM_DELETE,          //!< remove tests/folders
    PRM_DISABLE,         //!< disable/enable tests
    PRM_STATISTIC,       //!< reset statistic
    PRM_MONITORING,      //!< start/stop monitoring
    PRM_OPTIONS,         //!< change options
    PRM_SCHEDULES,       //!< manage schedules
    PRM_MAIL_PROFILES,   //!< manage mail profiles
    PRM_COLOR_PROFILES,  //!< manage color profiles
    PRM_REPORT_PROFILES, //!< manage report profiles
    PRM_ACTION_PROFILES, //!< manage action profiles
    PRM_USER_PROFILES,   //!< manage user profiles
    PRM_ACKNOWLEDGE,     //!< acknowledge test status
    PRM_PAUSE,           //!< pause/resume tests
    PRM_GUI,             //!< edit GUI options for the account
    PRM_GUI_ALL,         //!< edit GUI options for ALL accounts
    PRM_READ             //!< view test settings (read-only)
};

/*****************************************************************/

class TEnums {

    static const QStringList testStatusList;
    static const QStringList simpleStatusList;
    static const QStringList permissions;

public:

    static QString testStatus(TestStatus status);
    static TestStatus testStatusFromString(const QString &name);
    static QString simpleStatus(SimpleStatusID status);
    static SimpleStatusID simpleStatusFromString(const QString &name, bool *ok=nullptr);
    static QString permissionName(const PermissionID id);
};

/*****************************************************************/

} // namespace SDPO

#endif // TENUMS_H
