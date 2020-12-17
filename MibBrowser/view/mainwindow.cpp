#include "mainwindow.h"
#include "qMibGetValueDlg.h"
#include "qMibGetTableDlg.h"

#include <QtWidgets>

using namespace MibBrowser;
using namespace SDPO;

/*************************************************************/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mibBrowser(new MibBrowserWidget(this))
{
    setupUI();
}

/*************************************************************/

MainWindow::~MainWindow()
{
}

/*************************************************************/

void MainWindow::setupUI()
{
    resize(986, 610);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    QFont font;
    font.setPointSize(9);
    setFont(font);

    setupActions();

    setCentralWidget(mibBrowser);
}

/*************************************************************/

void MainWindow::setupActions()
{
    // Actions
    QAction *actAppendMib = new QAction(QIcon::fromTheme("folder-new"),tr("&Append MIB file..."),this);
    actAppendMib->setShortcuts(QKeySequence::Open);
    QAction *actLoadDb = new QAction(QIcon::fromTheme("document-open"),tr("&Load database"),this);
    QAction *actSaveDb = new QAction(QIcon::fromTheme("document-save"),tr("&Save database"),this);
    actSaveDb->setShortcuts(QKeySequence::Save);
    QAction *actClear = new QAction(QIcon::fromTheme("edit-clear"),tr("&Clear"),this);
    QAction *actExit = new QAction(QIcon::fromTheme("application-exit"),tr("&Exit"),this);
    actExit->setShortcuts(QKeySequence::Quit);
    connect(actExit, &QAction::triggered, this, &MainWindow::close);

    QAction *actStat = new QAction(tr("&Statistics..."),this);

    QAction *actHelp = new QAction(QIcon::fromTheme("help-contents"),tr("&Help"),this);
    actHelp->setShortcuts(QKeySequence::HelpContents);
    QAction *actSupport = new QAction(QIcon::fromTheme("help-faq"),tr("&Support..."),this);
    QAction *actAbout = new QAction(QIcon::fromTheme("help-about"),tr("&About..."),this);

    // Menu bar
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *menuFile = new QMenu(tr("&File"), menuBar);
    menuFile->addAction(actAppendMib);
    menuFile->addSeparator();
    menuFile->addAction(actLoadDb);
    menuFile->addAction(actSaveDb);
    menuFile->addAction(actClear);
    menuFile->addSeparator();
    menuFile->addAction(actExit);
    menuBar->addAction(menuFile->menuAction());

    QMenu *menuSearch = new QMenu(tr("&Search"), menuBar);
    menuSearch->addAction(mibBrowser->actionFindName());
    menuSearch->addAction(mibBrowser->actionFindNext());
    menuSearch->addSeparator();
    menuSearch->addAction(mibBrowser->actionFindOid());
    menuBar->addAction(menuSearch->menuAction());

    QMenu *menuView = new QMenu(tr("&View"), menuBar);
    menuView->addAction(mibBrowser->actionChart());
    menuView->addSeparator();
    menuView->addAction(mibBrowser->actionSysInfo());
    menuView->addAction(mibBrowser->actionGetValue());
    menuView->addAction(mibBrowser->actionGetTable());
    menuView->addSeparator();
    menuView->addAction(actStat);
    menuBar->addAction(menuView->menuAction());

    QMenu *menuHelp = new QMenu(tr("&Help"), menuBar);
    menuHelp->addAction(actHelp);
    menuHelp->addAction(actSupport);
    menuHelp->addSeparator();
    menuHelp->addAction(actAbout);
    menuBar->addAction(menuHelp->menuAction());

    actAppendMib->setDisabled(true);
    actLoadDb->setDisabled(true);
    actSaveDb->setDisabled(true);
    actClear->setDisabled(true);
    actStat->setDisabled(true);
    actHelp->setDisabled(true);
    actSupport->setDisabled(true);
    actAbout->setDisabled(true);

    setMenuBar(menuBar);
}

/*************************************************************/
