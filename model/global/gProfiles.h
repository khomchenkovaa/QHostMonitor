#ifndef GPROFILES_H
#define GPROFILES_H

#include <QString>
#include <QStringList>
#include <QColor>
#include <QUuid>

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

typedef QPair<QString, bool>  QIpPair;
typedef QList<QIpPair>        QIpPairList;
typedef QPair<QUuid, QString> QFoldersPair;
typedef QList<QFoldersPair>   QFoldersList;
typedef QList<TLColumn>       QColumnList;
typedef QPair<QString, bool>  QSortPair;
typedef QList<QSortPair>      QSortPairList;

struct GUserProfile
{
    // user profile
    QString       id;
    QString       name;        // Full name
    QString       password;
    bool          enabled;     // status
    QString       email;
    QString       pager;
    QString       icq;
    unsigned      permissions; // user has rights to
    QIpPairList   rccFrom;     // accept remote connections from
    bool          rccLimit;    // limit number of RCC connection for the account
    int           rccNumber;   // max number of RCC connection for the account
    bool          allowAll;    // access to all folders in ant HML list
    QFoldersList  folders;     // access to folders only
    // GUI preferences
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
