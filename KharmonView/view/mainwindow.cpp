#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace KharmonView;

/*************************************************************/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
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

void MainWindow::setupUI()
{
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::cmdNew);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::cmdOpen);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::cmdSave);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::cmdSaveAs);
    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);
}

/*************************************************************/
