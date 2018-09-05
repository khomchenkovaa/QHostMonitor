#ifndef GPROFILES_H
#define GPROFILES_H

#include <QString>
#include <QStringList>
#include <QColor>
#include "tEnums.h"

namespace SDPO {

class TestAction;

/*****************************************************************/

struct GActionProfile
{
    QString            name;
    QList<TestAction*> onBad;
    QList<TestAction*> onGood;
    QStringList        comments;

    void clearActions() {
        qDeleteAll(onBad);
        onBad.clear();
        qDeleteAll(onGood);
        onGood.clear();
    }
};

/*****************************************************************/

struct GMailProfile
{
    QString     name;
    QString     type;
    QString     charset;
    QStringList body;
};

/*****************************************************************/

typedef QList<QColor> QColorList;

struct GColorProfile
{
    QString    name;
    QColorList htmlText;
    QColorList header;
    QColorList folder;
    QColorList testNotTested;
    QColorList testOk;
    QColorList testNormal;
    QColorList testWarning;
    QColorList testBad;
    QColorList testAcknowledged;
    QColorList testUnknown;
    QColorList message;
    QColorList testChecking;
    QColorList testDisabled;
    QColorList testWaitForMaster;
    QColorList testOutOfSchedule;
    QColorList links;
    QColorList linkVisited;
    QColorList linkActive;

    QColor colorByStatus(const int status) const;
    QColor bgColorByStatus(const int status) const;

private:
    QColor getColorByTestStatus(const TestStatus status, bool background = false) const;
};

/*****************************************************************/

enum class TestListStyle { Report, List, Icon, SmallIcon };

/*****************************************************************/

struct GIPMonitor
{
    int    vLinesNumber;
    int    hLinesNumber;
    QColor backgroundColor;
    QColor gridColor;
    QColor inPacketsColor;
    QColor outPacketsColor;
    QColor errorColor;
};

struct TLColumn
{
    QString title;
    QString macro;
    bool checked;
};

/*****************************************************************/

typedef QPair<QString, bool> QSortPair;
typedef QList<QSortPair> QSortPairList;
typedef QList<TLColumn> QColumnList;

struct GUserProfile
{
    QString       id;
    QString       name;
    QString       password;
    bool          enabled;
    QString       email;
    QString       pager;
    QString       icq;
    unsigned      permissions;
    TestListStyle style;
    bool          showGridLines;
    bool          gridForLogViewer;
    bool          showTestsInSubfolders;
    QString       colorScheme;
    double        ipmRefreshTime;
    bool          ipmShowPacketsCounter;
    GIPMonitor    tcpMonitor;
    GIPMonitor    udpMonitor;
    GIPMonitor    icmpMonitor;
    QColumnList   columns;
    QSortPairList sort;

    int  getStyle() const { return (int)style; }
    void setStyle(const int value) { style = (TestListStyle)value; }
    int getColumnCount() const;
    TLColumn getColumn(const int idx) const;
    QString getColumnMacro(const int idx) const;
    void setPermission(const PermissionID id, const bool value);
    bool hasPermission(const PermissionID id) const;
    GUserProfile clone();
};

/*****************************************************************/


} // namespace SDPO

#endif // GPROFILES_H
