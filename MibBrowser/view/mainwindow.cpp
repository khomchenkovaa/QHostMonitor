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

void MainWindow::getValueDld()
{
    QMibGetValueDlg dlg;
    dlg.setOid(mibBrowser->getOid());
    dlg.exec();
}

/*************************************************************/

void MainWindow::getTableDlg()
{
    QMibGetTableDlg dlg;
    dlg.setOid(mibBrowser->getOid());
    dlg.exec();
}

/*************************************************************/

void MainWindow::findNameDlg()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Find Name"),tr("Name (e.g. sysUptime)"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        mibBrowser->findByName(name);
    }
}

/*************************************************************/

void MainWindow::findOidDlg()
{
    bool ok;
    QString oid = QInputDialog::getText(this, tr("Find OID"),tr("OID (e.g. 1.3.6.1.2.1.1.1)"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        mibBrowser->setOid(oid);
    }
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

    QAction *actFindName = new QAction(QIcon::fromTheme("edit-find"),tr("Find name..."),this);
    actFindName->setShortcuts(QKeySequence::Find);
    connect(actFindName, &QAction::triggered, this, &MainWindow::findNameDlg);
    QAction *actSearchNext = new QAction(QIcon::fromTheme("go-next"),tr("Search next"),this);
    actSearchNext->setShortcuts(QKeySequence::FindNext);
    QAction *actFindOid = new QAction(QIcon::fromTheme("system-search"),tr("Find OID..."),this);
    connect(actFindOid, &QAction::triggered, this, &MainWindow::findOidDlg);

    QAction *actCharts = new QAction(tr("C&harts"),this);
    QAction *actSysInfo = new QAction(tr("System &info..."),this);
    connect(actSysInfo, &QAction::triggered, this, &MainWindow::getValueDld);
    QAction *actCounter = new QAction(tr("&Counter..."),this);
    connect(actCounter, &QAction::triggered, this, &MainWindow::getValueDld);
    QAction *actTable = new QAction(tr("&Table..."),this);
    connect(actTable, &QAction::triggered, this, &MainWindow::getTableDlg);
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
    menuSearch->addAction(actFindName);
    menuSearch->addAction(actSearchNext);
    menuSearch->addSeparator();
    menuSearch->addAction(actFindOid);
    menuBar->addAction(menuSearch->menuAction());

    QMenu *menuView = new QMenu(tr("&View"), menuBar);
    menuView->addAction(actCharts);
    menuView->addSeparator();
    menuView->addAction(actSysInfo);
    menuView->addAction(actCounter);
    menuView->addAction(actTable);
    menuView->addSeparator();
    menuView->addAction(actStat);
    menuBar->addAction(menuView->menuAction());

    QMenu *menuHelp = new QMenu(tr("&Help"), menuBar);
    menuHelp->addAction(actHelp);
    menuHelp->addAction(actSupport);
    menuHelp->addSeparator();
    menuHelp->addAction(actAbout);
    menuBar->addAction(menuHelp->menuAction());

    setMenuBar(menuBar);
}

/*************************************************************/
