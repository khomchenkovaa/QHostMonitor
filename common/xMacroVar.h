#pragma once

#include <QString>
#include <vector>

namespace SDPO {

// Macrovariables

namespace Macro {
    enum Group {
        TP, TS, SS, AI, LS, ST, SP
    };

    enum Variable {
        Unknown,
        // TP (test properties)
        TestName, TestID, HostName, HostID, Agent, TestMethod, MethodID, MethodName, TestedObjectInfo,
        Interval, Interval_Sec, Interval_Min, ScheduleName,
        AlertProfile, AlertThreshold, AlertThresholValue,
        MasterTest, MasterTests,
        PrivateLog, RelatedURL,
        TaskComment, CommentLine1, CommentLine2, CommentLine3, CommentLine4, CommentLine5, CommentID,
        CreatedTime, ModifiedTime,
        // TS (test status)
        DATE, TIME, DateTime, LastTestTime,
        Reply, Reply_CStyle, Reply_Number, Reply_Integer,
        Status, StatusID, SimpleStatus, CurrentStatusIteration,
        Recurrences, CurrentStatusDuration, CurrentStatusDuration_sec, PauseComment,
        // SS (suggested status)
        FailureID, LastFailureID,
        SuggestedStatus, SuggestedSimpleStatus,TestingMethod,
        SuggestedReply, SuggestedReply_Integer, SuggestedLastReply,
        SuggestedRecurrences, FailureIteration,
        // AI (Acknowledgement info)
        AcknowledgedAt, AcknowledgedDate, AcknowledgedTime, AcknowledgedBy,
        AckComment, AckResponseTime, AckRecurrences,
        // LS (last status)
        LastStatus, LastSimpleStatus, LastReply, LastReply_CStyle,
        PreviousStatus, PreviousStatusTime, PreviousStatusDuration, PreviousStatusDuration_Sec,
        // ST (statistics)
        StatusChangedTime, StatusChangesCnt,
        TotalTests, TotalTime,
        FailedCnt, PassedCnt, UnknownCnt,
        AliveTime, DeadTime, UnknownTime,
        AliveRatio, DeadRatio, UnknownRatio,
        AverageReply, MinReply, MaxReply,
        // SP (test methods specific variables)
        Host, HostAddr, Path, Object, Object2,
        ServiceComp, ServiceName, TraceBrief, TraceFull,
        HostURL, HttpPage, HttpHeader, HttpCode, DnsResult, DnsResults,
        FileName, FileSize, FileTime, ProcessName, ProcessID, TestMode,
        NTEventSource, NTEventComp, NTEventTime, NTEventType, NTEventID, NTEventText, NTEventUser,
        TrapHost, TrapHostInfo, TrapType, TimeTicks,
        Enterprise, EnterpriseName, EnterpriseNameShort,
        MibOid, MibName, MibNameShort, MibType, MibValue, MibRelative,
        TrapAllValues, TrapAllValues_Name, TrapAllValues_NameShort, TrapAllValues_NameValue, TrapAllValues_NameValueShort
    };

} // namespace MV

struct MVGroupsStruct {
    Macro::Group id;
    QString name;
};

struct MVariablesStruct {
    Macro::Variable id;
    QString name;
    Macro::Group group;
};

// TP, TS, SS, AI, LS, ST, SP
extern const std::vector<MVGroupsStruct> mvGroupsList;

extern const std::vector<MVariablesStruct> mvVariablesList;


} // namespace SDPO
