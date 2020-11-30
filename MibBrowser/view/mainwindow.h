#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mibbrowserwidget.h"

#include <QMainWindow>

namespace MibBrowser {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void getValueDld();
    void getTableDlg();
    void findNameDlg();
    void findOidDlg();

private:
    void setupUI();
    void setupActions();

private:
    SDPO::MibBrowserWidget *mibBrowser;
};

} // namespace MibBrowser

#endif // MAINWINDOW_H
