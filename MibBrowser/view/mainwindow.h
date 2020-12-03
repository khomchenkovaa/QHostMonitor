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

private:
    void setupUI();
    void setupActions();

private:
    SDPO::MibBrowserWidget *mibBrowser;
};

} // namespace MibBrowser

#endif // MAINWINDOW_H
