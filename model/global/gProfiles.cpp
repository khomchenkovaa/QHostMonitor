#include "gProfiles.h"
#include <QDebug>

namespace SDPO {

/*****************************************************************/

QColor GColorProfile::colorByStatus(const int status) const
{
    return getColorByTestStatus((TestStatus)status, false);
}

/*****************************************************************/

QColor GColorProfile::bgColorByStatus(const int status) const
{
    return getColorByTestStatus((TestStatus)status, true);
}

/*****************************************************************/

QColor GColorProfile::getColorByTestStatus(const TestStatus status, bool background) const
{
    int idx = background ? 1 : 0;
    switch (status) {
    case TestStatus::Resolving:
        return htmlText.at(idx);
    case TestStatus::HostAlive:
    case TestStatus::Ok:
        return testOk.at(idx);
    case TestStatus::NoAnswer:
    case TestStatus::Bad:
    case TestStatus::BadContents:
        return testBad.at(idx);
    case TestStatus::Unknown:
    case TestStatus::UnknownHost:
        return testUnknown.at(idx);
    case TestStatus::Disabled:
        return testDisabled.at(idx);
    case TestStatus::WaitForMaster:
        return testWaitForMaster.at(idx);
    case TestStatus::OutOfSchedule:
    case TestStatus::Paused:
        return testOutOfSchedule.at(idx);
    case TestStatus::Warning:
        return testWarning.at(idx);
    case TestStatus::Normal:
        return testNormal.at(idx);
    case TestStatus::NotTested:
        return testNotTested.at(idx);
    case TestStatus::Checking:
        return testChecking.at(idx);
    }
    return htmlText.at(idx);
}

/*****************************************************************/

int GUserProfile::getColumnCount() const
{
    int cnt = 0;
    foreach (const TLColumn &column, columns) {
        if (column.checked) cnt++;
    }
    return cnt;
}

/*****************************************************************/

TLColumn GUserProfile::getColumn(const int idx) const
{
    TLColumn result;
    int cnt = 0;
    foreach (const TLColumn &column, columns) {
        if (column.checked) {
            if (idx == cnt) {
                result = column;
            } else {
                cnt++;
            }
        }
    }
    return result;
}

/*****************************************************************/

QString GUserProfile::getColumnMacro(const int idx) const
{
    TLColumn column = getColumn(idx);
    return column.macro;
}

/*****************************************************************/

GUserProfile GUserProfile::clone()
{
    GUserProfile profile;
    profile.id = id;
    profile.name = name;
    profile.password = password;
    profile.enabled = enabled;
    profile.email = email;
    profile.pager = pager;
    profile.icq = icq;
    profile.style = style;
    profile.showGridLines = showGridLines;
    profile.gridForLogViewer = gridForLogViewer;
    profile.showTestsInSubfolders = showTestsInSubfolders;
    profile.colorScheme = colorScheme;
    profile.ipmRefreshTime = ipmRefreshTime;
    profile.ipmShowPacketsCounter = ipmShowPacketsCounter;
    profile.tcpMonitor = tcpMonitor;
    profile.udpMonitor = udpMonitor;
    profile.icmpMonitor = icmpMonitor;
    foreach (const TLColumn &column, columns) {
        TLColumn newColumn = column;
        profile.columns.append(newColumn);
    }
    foreach (const QSortPair &pair, sort) {
        QSortPair newPair = pair;
        profile.sort.append(newPair);
    }
    return profile;
}

/*****************************************************************/

} // namespace SDPO
