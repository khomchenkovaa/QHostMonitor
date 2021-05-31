#ifndef KHARMONVIEW_MAINWINDOW_H
#define KHARMONVIEW_MAINWINDOW_H

#include "snmpobjectmodel.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QTreeView;
class QLabel;
class QLineEdit;
QT_END_NAMESPACE

namespace KharmonView {

class SnmpObjectWidget;
class SnmpResultWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void setModel(SnmpObjectModel *model);

signals:
    void cmdNew();
    void cmdOpen();
    void cmdSave();
    void cmdSaveAs();

private slots:
    void updateInfo(const QModelIndex& index);
    void cmdObjAdd();
    void cmdObjEdit();
    void cmdObjRemove();
    void cmdDefaults();

private:
    void setupUI();
    void setupActions();
    void setupMenuBar();
    void setupStatusBar();
    void setupToolBar();
    void init();

private:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionObjAdd;
    QAction *actionObjEdit;
    QAction *actionObjRemove;
    QAction *actionAbout;
    QAction *actionDefaults;

    QTreeView *objectTree;
    SnmpObjectWidget *objectInfo;
    SnmpResultWidget *snmpResult;

};

} // namespace KharmonView

#endif // KHARMONVIEW_MAINWINDOW_H
