#include "xMacroVar.h"

using namespace SDPO;
/******************************************************************/

std::vector<MVGroupsStruct> TMacro::groupList = {
    { Macro::TP, "Test properties" },
    { Macro::TS, "Test status" },
    { Macro::SS, "Suggested status" },
    { Macro::AI, "Acknowledgement info" },
    { Macro::LS, "Last status" },
    { Macro::ST, "Statistics" },
    { Macro::SP, "Test methods specific variables" }
};

/******************************************************************/

std::vector<MVariablesStruct> TMacro::varList = {
    { Macro::Unknown, "Unknown", Macro::TP },
    // TP (test properties)
    { Macro::TestName,	         "TestName",	       Macro::TP },
    { Macro::TestID,	         "TestID",	           Macro::TP },
    { Macro::HostName,	         "HostName",	       Macro::TP },
    { Macro::HostID,	         "HostID",	           Macro::TP },
    { Macro::Agent,	             "Agent",	           Macro::TP },
    { Macro::TestMethod,	     "TestMethod",	       Macro::TP },
    { Macro::MethodID,	         "MethodID",	       Macro::TP },
    { Macro::MethodName,	     "MethodName",	       Macro::TP },
    { Macro::TestedObjectInfo,	 "TestedObjectInfo",   Macro::TP },
    { Macro::Interval,	         "Interval",	       Macro::TP },
    { Macro::Interval_Sec,	     "Interval_Sec",	   Macro::TP },
    { Macro::Interval_Min,	     "Interval_Min",	   Macro::TP },
    { Macro::ScheduleName,	     "ScheduleName",	   Macro::TP },
    { Macro::AlertProfile,	     "AlertProfile",	   Macro::TP },
    { Macro::AlertThreshold,	 "AlertThreshold",	   Macro::TP },
    { Macro::AlertThresholValue, "AlertThresholValue", Macro::TP },
    { Macro::MasterTest,	     "MasterTest",	       Macro::TP },
    { Macro::MasterTests,	     "MasterTests",	       Macro::TP },
    { Macro::TargetPort,	     "TargetPort",	       Macro::TP },
    { Macro::PrivateLog,	     "PrivateLog",	       Macro::TP },
    { Macro::RelatedURL,	     "RelatedURL",	       Macro::TP },
    { Macro::TaskComment,	     "TaskComment",	       Macro::TP },
    { Macro::CommentLine1,	     "CommentLine1",	   Macro::TP },
    { Macro::CommentLine2,	     "CommentLine2",	   Macro::TP },
    { Macro::CommentLine3,	     "CommentLine3",	   Macro::TP },
    { Macro::CommentLine4,	     "CommentLine4",	   Macro::TP },
    { Macro::CommentLine5,	     "CommentLine5",	   Macro::TP },
    { Macro::CommentID,	         "CommentID",	       Macro::TP },
    { Macro::CreatedTime,	     "CreatedTime",	       Macro::TP },
    { Macro::ModifiedTime,	     "ModifiedTime",	   Macro::TP },
    // TS (test status)
    { Macro::DATE,	                   "DATE",	                   Macro::TS },
    { Macro::TIME,	                   "TIME",	                   Macro::TS },
    { Macro::DateTime,	               "DateTime",	               Macro::TS },
    { Macro::LastTestTime,	           "LastTestTime",	           Macro::TS },
    { Macro::Reply,	                   "Reply",	                   Macro::TS },
    { Macro::Reply_CStyle,	           "Reply_CStyle",	           Macro::TS },
    { Macro::Reply_Number,	           "Reply_Number",	           Macro::TS },
    { Macro::Reply_Integer,	           "Reply_Integer",	           Macro::TS },
    { Macro::Status,	               "Status",	               Macro::TS },
    { Macro::StatusID,	               "StatusID",	               Macro::TS },
    { Macro::SimpleStatus,	           "SimpleStatus",	           Macro::TS },
    { Macro::CurrentStatusIteration,   "CurrentStatusIteration",   Macro::TS },
    { Macro::Recurrences,	           "Recurrences",	           Macro::TS },
    { Macro::CurrentStatusDuration,	   "CurrentStatusDuration",	   Macro::TS },
    { Macro::CurrentStatusDuration_sec,"CurrentStatusDuration_sec",Macro::TS },
    { Macro::PauseComment,             "PauseComment",             Macro::TS },
    // SS (suggested status)
    { Macro::FailureID,	             "FailureID",	          Macro::SS },
    { Macro::LastFailureID,	         "LastFailureID",	      Macro::SS },
    { Macro::SuggestedStatus,	     "SuggestedStatus",	      Macro::SS },
    { Macro::SuggestedSimpleStatus,	 "SuggestedSimpleStatus", Macro::SS },
    { Macro::TestingMethod,	         "TestingMethod",	      Macro::SS },
    { Macro::SuggestedReply,	     "SuggestedReply",	      Macro::SS },
    { Macro::SuggestedReply_Integer, "SuggestedReply_Integer",Macro::SS },
    { Macro::SuggestedLastReply,	 "SuggestedLastReply",	  Macro::SS },
    { Macro::SuggestedRecurrences,	 "SuggestedRecurrences",  Macro::SS },
    { Macro::FailureIteration, 	     "FailureIteration", 	  Macro::SS },
    // AI (Acknowledgement info)
    { Macro::AcknowledgedAt,  "AcknowledgedAt",	 Macro::AI },
    { Macro::AcknowledgedDate,"AcknowledgedDate",Macro::AI },
    { Macro::AcknowledgedTime,"AcknowledgedTime",Macro::AI },
    { Macro::AcknowledgedBy,  "AcknowledgedBy",	 Macro::AI },
    { Macro::AckComment,	  "AckComment",	     Macro::AI },
    { Macro::AckResponseTime, "AckResponseTime", Macro::AI },
    { Macro::AckRecurrences,  "AckRecurrences",	 Macro::AI },
    // LS (last status)
    { Macro::LastStatus,	            "LastStatus",	             Macro::LS },
    { Macro::LastSimpleStatus,	        "LastSimpleStatus",	         Macro::LS },
    { Macro::LastReply,	                "LastReply",	             Macro::LS },
    { Macro::LastReply_CStyle,	        "LastReply_CStyle",	         Macro::LS },
    { Macro::PreviousStatus,	        "PreviousStatus",	         Macro::LS },
    { Macro::PreviousStatusTime,	    "PreviousStatusTime",	     Macro::LS },
    { Macro::PreviousStatusDuration,	"PreviousStatusDuration",	 Macro::LS },
    { Macro::PreviousStatusDuration_Sec,"PreviousStatusDuration_Sec",Macro::LS },
    // ST (statistics)
    { Macro::StatusChangedTime,"StatusChangedTime",	Macro::ST },
    { Macro::StatusChangesCnt, "StatusChangesCnt",	Macro::ST },
    { Macro::TotalTests,	   "TotalTests",	    Macro::ST },
    { Macro::TotalTime,	       "TotalTime",	        Macro::ST },
    { Macro::FailedCnt,	       "FailedCnt",	        Macro::ST },
    { Macro::PassedCnt,	       "PassedCnt",	        Macro::ST },
    { Macro::UnknownCnt,	   "UnknownCnt",	    Macro::ST },
    { Macro::AliveTime,	       "AliveTime",	        Macro::ST },
    { Macro::DeadTime,	       "DeadTime",	        Macro::ST },
    { Macro::UnknownTime,	   "UnknownTime",	    Macro::ST },
    { Macro::AliveRatio,	   "AliveRatio",	    Macro::ST },
    { Macro::DeadRatio,	       "DeadRatio",	        Macro::ST },
    { Macro::UnknownRatio,	   "UnknownRatio",	    Macro::ST },
    { Macro::AverageReply,	   "AverageReply",	    Macro::ST },
    { Macro::MinReply,	       "MinReply",	        Macro::ST },
    { Macro::MaxReply, 	       "MaxReply", 	        Macro::ST },
    // SP (test methods specific variables)
    { Macro::Host,	      "Host",	    Macro::SP },
    { Macro::HostAddr,    "HostAddr",	Macro::SP },
    { Macro::Path,	      "Path",	    Macro::SP },
    { Macro::Object,      "Object",	    Macro::SP },
    { Macro::Object2,     "Object2",	Macro::SP },
    { Macro::ServiceComp, "ServiceComp",Macro::SP },
    { Macro::ServiceName, "ServiceName",Macro::SP },
    { Macro::TraceBrief,  "TraceBrief",	Macro::SP },
    { Macro::TraceFull,	  "TraceFull",	Macro::SP },
    { Macro::HostURL,	  "HostURL",	Macro::SP },
    { Macro::HttpPage,	  "HttpPage",	Macro::SP },
    { Macro::HttpHeader,  "HttpHeader",	Macro::SP },
    { Macro::HttpCode,	  "HttpCode",	Macro::SP },
    { Macro::DnsResult,	  "DnsResult",	Macro::SP },
    { Macro::DnsResults,  "DnsResults",	Macro::SP },
    { Macro::FileName,	  "FileName",	Macro::SP },
    { Macro::FileSize,	  "FileSize",	Macro::SP },
    { Macro::FileTime,	  "FileTime",	Macro::SP },
    { Macro::ProcessName, "ProcessName",Macro::SP },
    { Macro::ProcessID,	  "ProcessID",	Macro::SP },
    { Macro::TestMode,	  "TestMode",	Macro::SP },
    { Macro::NTEventSource, "NTEventSource",Macro::SP },
    { Macro::NTEventComp,	"NTEventComp",	Macro::SP },
    { Macro::NTEventTime,	"NTEventTime",	Macro::SP },
    { Macro::NTEventType,	"NTEventType",	Macro::SP },
    { Macro::NTEventID,	    "NTEventID",	Macro::SP },
    { Macro::NTEventText,	"NTEventText",	Macro::SP },
    { Macro::NTEventUser,	"NTEventUser",	Macro::SP },
    { Macro::TrapHost,	    "TrapHost",	    Macro::SP },
    { Macro::TrapHostInfo,	"TrapHostInfo",	Macro::SP },
    { Macro::TrapType,	    "TrapType",	    Macro::SP },
    { Macro::TimeTicks,	    "TimeTicks",	Macro::SP },
    { Macro::Enterprise,	     "Enterprise",	Macro::SP },
    { Macro::EnterpriseName,	 "EnterpriseName",	Macro::SP },
    { Macro::EnterpriseNameShort,"EnterpriseNameShort",	Macro::SP },
    { Macro::MibOid,	    "MibOid",	    Macro::SP },
    { Macro::MibName,	    "MibName",	    Macro::SP },
    { Macro::MibNameShort,	"MibNameShort",	Macro::SP },
    { Macro::MibType,	    "MibType",	    Macro::SP },
    { Macro::MibValue,	    "MibValue",	    Macro::SP },
    { Macro::MibRelative,	"MibRelative",	Macro::SP },
    { Macro::TrapAllValues,	               "TrapAllValues",	                Macro::SP },
    { Macro::TrapAllValues_Name,	       "TrapAllValues_Name",	        Macro::SP },
    { Macro::TrapAllValues_NameShort,	   "TrapAllValues_NameShort",	    Macro::SP },
    { Macro::TrapAllValues_NameValue,	   "TrapAllValues_NameValue",	    Macro::SP },
    { Macro::TrapAllValues_NameValueShort, "TrapAllValues_NameValueShort",	Macro::SP }
};

/******************************************************************/

MVariablesStruct TMacro::varStruct(Macro::Variable mv)
{
    if (static_cast<unsigned>(mv) >= varList.size()) mv = Macro::Unknown;
    return varList.at(mv);
}

/******************************************************************/

Macro::Variable TMacro::var(const QString name)
{
    Macro::Variable result = Macro::Unknown;
    for(unsigned i=0;i<varList.size();++i) {
        if ( name.compare(varList.at(i).name, Qt::CaseInsensitive) == 0 ) {
            result = varList.at(i).id;
            break;
        }
    }
    return result;
}

/******************************************************************/
