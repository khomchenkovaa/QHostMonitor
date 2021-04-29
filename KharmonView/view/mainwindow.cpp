#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace KharmonView;

/*************************************************************/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

/*************************************************************/

MainWindow::~MainWindow()
{
    delete ui;
}

/*************************************************************/

void MainWindow::setModel(SnmpObjectModel *model)
{
    ui->objectTree->setModel(model);
}

/*************************************************************/

