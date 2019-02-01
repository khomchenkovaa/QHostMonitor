#include "tTestInfo.h"
#include "utils.h"
#include "tTest.h"

namespace SDPO {

/******************************************************************/

TestInfo::TestInfo(TNode *test, QString path, QObject *parent) :
    QObject(parent),
    m_test(test),
    m_path(path)
{

}


/******************************************************************/

TNode *TestInfo::getTest() const
{
    return m_test;
}

/******************************************************************/

QString TestInfo::path() const
{
    return m_path;
}

/******************************************************************/

QVariant TestInfo::getData(int line) const
{
    switch (line) {
    case  0: return m_test->getGlobal(Macro::TestName);    //  1-Test name
    case  1: return m_test->getGlobal(Macro::Status);      //  2 - The current status of the test
    case  2: return m_test->getGlobal(Macro::Recurences);  //  3 - The number of consecutive tests resulting in the same status as the current one
    case  3: return m_test->getGlobal(Macro::Reply);       //  4 - The value last returned by the test (the meaning of the Reply parameter is test specific)
    case  4: return m_test->getGlobal(Macro::LastTestTime);//  5 - The time when the test was last performed
    case  5: return m_test->getGlobal(Macro::LastStatus);  //  6 - The status of the previous test
    case  6: return m_test->getGlobal(Macro::LastReply);   //  7 - The value returned by the previous test (test-specific)
    case  7: return m_test->getGlobal(Macro::Interval);    //  8 - The time between two consecutive runs defined for the test (hh:mm:ss) !!!
    case  8: return m_test->getGlobal(Macro::TestMethod);  //  9 - The type of the test: ping(timeout - %1 ms)
    case  9: return m_test->getGlobal(Macro::CommentLine1);// 10 - Comment line #1 (34,35,36,37 - Comment lines #2-5)
    case 10: return m_test->getGlobal(Macro::RelatedURL);  // 11 - Test-related URL
    case 11: return m_test->getGlobal(Macro::MasterTest);  // 12 - The name of the Master test (for more information on test dependencies see Common test properties)
    case 12: return m_test->getGlobal(Macro::ScheduleName);// 13 - The name of the associated schedule
    case 13: return m_test->getGlobal(Macro::AlertProfile);// 14 - Alert profile name
    case 14: return m_test->getGlobal(Macro::PrivateLog);  // 15 - The specified private log file name
    case 15: return m_test->getGlobal(Macro::AliveRatio);  // 16 - "Good" to overall tests ratio, in percent
    case 16: return m_test->getGlobal(Macro::DeadRatio);   // 17 - "Bad" to overall tests ratio, in percent
    case 17: return m_test->getGlobal(Macro::UnknownRatio);// 18 - "Unknown" to overall tests ratio, in percent
    case 18: return m_test->getGlobal(Macro::TotalTime);   // 19 - The time the test has been in monitoring
    case 19: return m_test->getGlobal(Macro::AliveTime);   // 20 - The overall time the test has had a "Good" status
    case 20: return m_test->getGlobal(Macro::DeadTime);    // 21 - The overall time the test has had a "Bad" status
    case 21: return m_test->getGlobal(Macro::UnknownTime); // 22 - The overall time the test has had an "Unknown" status
    case 22: return m_test->getGlobal(Macro::TotalTests);  // 23 - Overall tests performed
    case 23: return m_test->getGlobal(Macro::PassedCnt);   // 24 - The number of "Good" tests
    case 24: return m_test->getGlobal(Macro::FailedCnt);   // 25 - The number of "Bad" tests
    case 25: return m_test->getGlobal(Macro::UnknownCnt);  // 26 - The number of "Unknown" tests
    case 26: return m_test->getGlobal(Macro::AverageReply);// 27 - The average value of the results obtained
    case 27: return m_test->getGlobal(Macro::MinReply);    // 28 - The minimum value of the results obtained
    case 28: return m_test->getGlobal(Macro::MaxReply);    // 29 - The maximum value of the results obtained
    case 29: return m_test->getGlobal(Macro::StatusChangedTime); // 30 - The time when the status last changed
    case 30: return m_test->getGlobal(Macro::StatusChangesCnt);  // 31 - The number of times the status has changed
    case 31: return m_test->getGlobal(Macro::CreatedTime); // 32 - The time when the test was created
    case 32: return m_test->getGlobal(Macro::ModifiedTime);// 33 - The time when the test was last modified
    case 33: return m_test->getGlobal(Macro::CommentLine2);// 34 - Comment line #2
    case 34: return m_test->getGlobal(Macro::CommentLine3);// 35 - Comment line #3
    case 35: return m_test->getGlobal(Macro::CommentLine4);// 36 - Comment line #4
    case 36: return m_test->getGlobal(Macro::CommentLine5);// 37 - Comment line #5
    case 37: return m_test->getGlobal(Macro::Agent);       // 38 - Test by = HostMonitor
    case 38: return m_test->getGlobal(Macro::AcknowledgedAt);    // 39 - The date and time when test status was acknowledged
    case 39: return m_test->getGlobal(Macro::AcknowledgedBy);    // 40 - Name of the operator who has acknowledged the test status (=local?)
    case 40: return m_test->getGlobal(Macro::AckComment);  // 41 - Shows the comment which was provided for "acknowledge" operation
    case 41: return m_path; // field for filtering
    default: return QVariant();
    }
}

/******************************************************************/

} // namespace SDPO
