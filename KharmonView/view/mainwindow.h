#ifndef KHARMONVIEW_MAINWINDOW_H
#define KHARMONVIEW_MAINWINDOW_H

#include "snmpobjectmodel.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace KharmonView {

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

private:
    void setupUI();

private:
    Ui::MainWindow *ui;
};

} // namespace KharmonView

#endif // KHARMONVIEW_MAINWINDOW_H
