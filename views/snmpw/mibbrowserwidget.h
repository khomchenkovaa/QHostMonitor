#ifndef MIBBROWSERWIDGET_H
#define MIBBROWSERWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QModelIndex;
class QTreeView;
class QLineEdit;
class QPlainTextEdit;
class QAction;
class QMenu;
QT_END_NAMESPACE

namespace SDPO {

class MibTreeModel;
class MibTreeProxyModel;

class MibBrowserWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MibBrowserWidget(QWidget *parent = nullptr);

    QString getOid() const;
    void setOid(const QString& oid);
    void findByName(const QString& name);

    QAction *actionSysInfo()  { return actSysInfo; }
    QAction *actionGetValue() { return actGetValue; }
    QAction *actionGetNext()  { return actGetNext; }
    QAction *actionGetRow()   { return actGetRow; }
    QAction *actionGetTable() { return actGetTable; }
    QAction *actionChart()    { return actChart; }
    QAction *actionFindName() { return actFindName; }
    QAction *actionFindNext() { return actFindNext; }
    QAction *actionFindOid()  { return actFindOid; }

private slots:
    void updateFields(const QModelIndex& proxyIndex);
    void updateActions(const QModelIndex& proxyIndex);
    void getValueDld(const QString& cmd = QString());
    void getTableDlg();
    void findNameDlg();
    void findOidDlg();
    void contextMenu(QPoint pos);

private:
    void setupUI();
    void setupActions();
    void init();

private:
    MibTreeModel      *m_Model;
    MibTreeProxyModel *m_Proxy;
    QTreeView         *treeMibs;
    QLineEdit         *editMib;
    QLineEdit         *editOid;
    QLineEdit         *editType;
    QLineEdit         *editAccess;
    QLineEdit         *editStatus;
    QLineEdit         *editEnums;
    QLineEdit         *editIndexes;
    QLineEdit         *editAugments;
    QLineEdit         *editVarbinds;
    QLineEdit         *editHint;
    QLineEdit         *editUnits;
    QPlainTextEdit    *txtDescription;
    QLineEdit         *editReference;
    QLineEdit         *editDefault;

    QAction *actSysInfo;
    QAction *actGetValue;
    QAction *actGetNext;
    QAction *actGetRow;
    QAction *actGetTable;
    QAction *actChart;
    QAction *actFindName;
    QAction *actFindNext;
    QAction *actFindOid;

    QMenu   *ctxMenu;
};

} // namespace SDPO

#endif // MIBBROWSERWIDGET_H
