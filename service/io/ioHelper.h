#ifndef IOHELPER_H
#define IOHELPER_H

#include "method/sdpoTestMethodConverters.h"

#define TIME_FORMAT "HH:mm:ss"

// Common required parameters
#define PRM_METHOD "Method"
#define PRM_TITLE  "Title"

// Common optional parameters
#define PRM_LINKED_TO     "LinkedTo"
#define PRM_NAME_PATTERN  "NamePattern"
#define PRM_DEST_FOLDER   "DestFolder"
#define PRM_RM_AGENT      "RMAgent"
#define PRM_COMMENT       "Comment"
#define PRM_CMNT_PATTERN  "CmntPattern"
#define PRM_RELATED_URL   "RelatedURL"

#define PRM_SCHEDULE      "Schedule"
#define PRM_SCHEDULE_MODE "ScheduleMode"
#define PRM_INTERVAL      "Interval"
#define PRM_SCHEDULE_DAY  "ScheduleDay"
#define PRM_SCHEDULE_TIME "ScheduleTime"
#define PRM_SCHEDULE_EXPR "ScheduleExpr"
#define PRM_ALERTS        "Alerts"

#define PRM_REVERSE_ALERT  "ReverseAlert"
#define PRM_UNKNOWN_IS_BAD "UnknownIsBad"
#define PRM_WARNING_IS_BAD "WarningIsBad"
#define PRM_USE_WARNING    "UseWarning"
#define PRM_WARNING_EXPR   "WarningExpr"
#define PRM_USE_NORMAL     "UseNormal"
#define PRM_NORMAL_EXPR    "NormalExpr"
#define PRM_TUNEUP_REPLY   "TuneupReply"
#define PRM_TUNE_REPLY_EXP "TuneReplyExp"

#define PRM_USE_COMMON_LOG "UseCommonLog"
#define PRM_PRIV_LOG       "PrivateLog"
#define PRM_PRIV_LOG_MODE  "PrivLogMode"
#define PRM_COM_LOG_MODE   "CommLogMode"

#define PRM_DEPENDS_ON                   "DependsOn"
#define PRM_DEPEND_EXPR                  "DpExpression"
#define PRM_DEPEND_EXPR_ID               "DpExprID"
#define PRM_DEPEND_STATUS                "DpOStatus"
#define PRM_DEPEND_STAT_ID               "DpOStatusID"
#define PRM_SYNC_COUNTERS                "SyncCounters"
#define PRM_SYNC_ALERTS                  "SyncAlerts"
#define PRM_MASTER_TEST_ALIVE            "MasterTest-Alive"
#define PRM_MASTER_TEST_ALIVE_OR_UNKNOWN "MasterTest-AliveOrUnknown"
#define PRM_MASTER_TEST_DEAD             "MasterTest-Dead"
#define PRM_MASTER_TEST_DEAD_OR_UNKNOWN  "MasterTest-DeadOrUnknown"

namespace SDPO {

class IOHelper
{
public:
    IOHelper();

    static IOTestMethodConverter* methodConverter(const TMethodID methodId);

private:
    // singleton
    explicit IOHelper(const IOHelper& rhs);
    IOHelper& operator= (const IOHelper& rhs);
};

} // namespace SDPO

#endif // IOHELPER_H
