#include "mainwindow.h"

#include "snmpobjectwidget.h"
#include "snmpresultwidget.h"
#include "snmpobjectedit.h"
#include "snmpobjectdefaults.h"

#include <QtWidgets>

using namespace KharmonView;

/*************************************************************/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow (parent)
    , actionNew       (new QAction(this))
    , actionOpen      (new QAction(this))
    , actionSave      (new QAction(this))
    , actionSaveAs    (new QAction(this))
    , actionExit      (new QAction(this))
    , actionObjAdd    (new QAction(this))
    , actionObjEdit   (new QAction(this))
    , actionObjRemove (new QAction(this))
    , actionAbout     (new QAction(this))
    , actionDefaults  (new QAction(this))
    , actionLogs      (new QAction(this))
    , objectTree      (new QTreeView(this))
    , objectInfo      (new SnmpObjectWidget(this))
    , snmpResult      (new SnmpResultWidget(this))
{
    setupUI();
    init();
}

/*************************************************************/

MainWindow::~MainWindow()
{
}

/*************************************************************/

void MainWindow::setModel(SnmpObjectModel *model)
{
    objectTree->setModel(model);
    QObject::connect(objectTree->selectionModel(), &QItemSelectionModel::currentChanged,
                     this, &MainWindow::updateInfo);
    updateInfo(objectTree->currentIndex());
}

/*************************************************************/

void MainWindow::updateInfo(const QModelIndex &index)
{
    SnmpObjectModel *model = qobject_cast<SnmpObjectModel *>(objectTree->model());
    SnmpObject *node = model->nodeFromIndex(index);
    objectInfo->setSnmpObject(node);
    snmpResult->setSnmpObject(node);
}

/*************************************************************/

void MainWindow::cmdObjAdd()
{
    const QModelIndex index = objectTree->selectionModel()->currentIndex();
    SnmpObjectModel *model = qobject_cast<SnmpObjectModel *>(objectTree->model());
    SnmpObjectEdit dlg(Q_NULLPTR, this);
    if (dlg.exec() == QDialog::Accepted) {
        SnmpObject *child = dlg.getObject();
        model->nodeAdd(index, child);
        updateInfo(objectTree->selectionModel()->currentIndex());
    }
}

/*************************************************************/

void MainWindow::cmdObjEdit()
{
    const QModelIndex index = objectTree->selectionModel()->currentIndex();
    if (!index.isValid()) return;
    SnmpObjectModel *model = qobject_cast<SnmpObjectModel *>(objectTree->model());
    SnmpObject *node = model->nodeFromIndex(index);
    SnmpObjectEdit dlg(node, this);
    if (dlg.exec() == QDialog::Accepted) {
        model->nodeChanged(index);
        updateInfo(objectTree->selectionModel()->currentIndex());
    }
}

/*************************************************************/

void MainWindow::cmdObjRemove()
{
    const QModelIndex index = objectTree->selectionModel()->currentIndex();
    SnmpObjectModel *model = qobject_cast<SnmpObjectModel *>(objectTree->model());
    SnmpObject *node = model->nodeFromIndex(index);
    if (node == SnmpObject::root) {
        QMessageBox::warning(this, tr("Remove Object"), tr("There is no legal object for deletion"));
        return;
    }

    QString question = tr("Remove Object '%1'").arg(node->getName());
    if (node->childCount()) {
        question.append(tr(" with all children"));
    }
    question.append(" ?");

    if (QMessageBox::Yes == QMessageBox::question(this, tr("Remove Object"), question)) {
        model->nodeRemove(index);
        updateInfo(objectTree->selectionModel()->currentIndex());
    }
}

/*************************************************************/

void MainWindow::cmdDefaults()
{
    SnmpObjectDefaults dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        updateInfo(objectTree->selectionModel()->currentIndex());
    }
}

/*************************************************************/

void MainWindow::cmdLogMessages()
{
    // TODO
}

/*************************************************************/

void MainWindow::setupUI()
{
    setObjectName(QStringLiteral("MainWindow"));
    resize(800, 600);
    setWindowTitle(QApplication::translate("MainWindow", "KharmonView", Q_NULLPTR));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    QFont font;
    font.setPointSize(9);
    setFont(font);

    setupActions();
    setupMenuBar();
    setupStatusBar();
    setupToolBar();

    QSplitter *objectPanel = new QSplitter(this);
    objectPanel->setObjectName(QStringLiteral("ObjectPanel"));
    objectPanel->setOrientation(Qt::Vertical);
    objectPanel->addWidget(objectTree);
    objectPanel->addWidget(objectInfo);
    objectPanel->setStretchFactor(0, 2);
    objectPanel->setStretchFactor(1, 1);

    QSplitter *splitter = new QSplitter(this);
    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(objectPanel);
    splitter->addWidget(snmpResult);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(splitter);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
}

/*************************************************************/

void MainWindow::setupActions()
{
    actionNew->setObjectName(QStringLiteral("actionNew"));
    actionNew->setIcon(QIcon::fromTheme(QStringLiteral("document-new")));
    actionNew->setText(QApplication::translate("MainWindow", "New", Q_NULLPTR));
    actionNew->setShortcuts(QKeySequence::New);
    connect(actionNew, &QAction::triggered, this, &MainWindow::cmdNew);

    actionOpen->setObjectName(QStringLiteral("actionOpen"));
    actionOpen->setIcon(QIcon::fromTheme(QStringLiteral("document-open")));
    actionOpen->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
    actionOpen->setShortcuts(QKeySequence::Open);
    connect(actionOpen, &QAction::triggered, this, &MainWindow::cmdOpen);

    actionSave->setObjectName(QStringLiteral("actionSave"));
    actionSave->setIcon(QIcon::fromTheme(QStringLiteral("document-save")));
    actionSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
    actionSave->setShortcuts(QKeySequence::Save);
    connect(actionSave, &QAction::triggered, this, &MainWindow::cmdSave);

    actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
    actionSaveAs->setIcon(QIcon::fromTheme(QStringLiteral("document-save-as")));
    actionSaveAs->setText(QApplication::translate("MainWindow", "Save as", Q_NULLPTR));
    connect(actionSaveAs, &QAction::triggered, this, &MainWindow::cmdSaveAs);

    actionExit->setObjectName(QStringLiteral("actionExit"));
    actionExit->setIcon(QIcon::fromTheme(QStringLiteral("application-exit")));
    actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
    actionExit->setShortcuts(QKeySequence::Quit);
    connect(actionExit, &QAction::triggered, this, &QMainWindow::close);

    actionObjAdd->setObjectName(QStringLiteral("actionObjAdd"));
    actionObjAdd->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    actionObjAdd->setText(QApplication::translate("MainWindow", "Add object", Q_NULLPTR));
    connect(actionObjAdd, &QAction::triggered, this, &MainWindow::cmdObjAdd);

    actionObjEdit->setObjectName(QStringLiteral("actionObjEdit"));
    actionObjEdit->setIcon(QIcon::fromTheme(QStringLiteral("format-text-direction-ltr")));
    actionObjEdit->setText(QApplication::translate("MainWindow", "Edit object", Q_NULLPTR));
    connect(actionObjEdit, &QAction::triggered, this, &MainWindow::cmdObjEdit);

    actionObjRemove->setObjectName(QStringLiteral("actionObjRemove"));
    actionObjRemove->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    actionObjRemove->setText(QApplication::translate("MainWindow", "Remove object", Q_NULLPTR));
    connect(actionObjRemove, &QAction::triggered, this, &MainWindow::cmdObjRemove);

    actionAbout->setObjectName(QStringLiteral("actionAbout"));
    actionAbout->setIcon(QIcon::fromTheme(QStringLiteral("help-about")));
    actionAbout->setText(QApplication::translate("MainWindow", "About", Q_NULLPTR));

    actionDefaults->setObjectName(QStringLiteral("actionDefaults"));
    actionDefaults->setIcon(QIcon::fromTheme(QStringLiteral("preferences-system")));
    actionDefaults->setText(QApplication::translate("MainWindow", "Defaults", Q_NULLPTR));
    connect(actionDefaults, &QAction::triggered, this, &MainWindow::cmdDefaults);

    actionLogs->setObjectName(QStringLiteral("actionLogs"));
    actionLogs->setIcon(QIcon(":img/actions/Log_Event.png"));
    actionLogs->setText(QApplication::translate("MainWindow", "Logs", Q_NULLPTR));
    connect(actionLogs, &QAction::triggered, this, &MainWindow::cmdLogMessages);
}

/*************************************************************/

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = new QMenuBar(this);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 800, 25));
    QMenu *menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QStringLiteral("menuFile"));
    menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
    QMenu *menuEdit = new QMenu(menuBar);
    menuEdit->setObjectName(QStringLiteral("menuEdit"));
    menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", Q_NULLPTR));
    QMenu *menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QStringLiteral("menuHelp"));
    menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    setMenuBar(menuBar);

    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuEdit->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    menuFile->addAction(actionNew);
    menuFile->addAction(actionOpen);
    menuFile->addSeparator();
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSaveAs);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);
    menuEdit->addAction(actionObjAdd);
    menuEdit->addAction(actionObjEdit);
    menuEdit->addAction(actionObjRemove);
    menuEdit->addSeparator();
    menuEdit->addAction(actionDefaults);
    menuHelp->addAction(actionLogs);
    menuHelp->addAction(actionAbout);
}

/*************************************************************/

void MainWindow::setupStatusBar()
{
    QStatusBar *statusBar = new QStatusBar(this);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    setStatusBar(statusBar);
}

/*************************************************************/

void MainWindow::setupToolBar()
{
    QToolBar *toolBar = new QToolBar(this);
    toolBar->setObjectName(QStringLiteral("toolBar"));
    toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));

    addToolBar(Qt::TopToolBarArea, toolBar);

    toolBar->addAction(actionNew);
    toolBar->addAction(actionOpen);
    toolBar->addAction(actionSave);
    toolBar->addAction(actionSaveAs);
    toolBar->addSeparator();
    toolBar->addAction(actionObjAdd);
    toolBar->addAction(actionObjEdit);
    toolBar->addAction(actionObjRemove);
    toolBar->addSeparator();
    toolBar->addAction(actionDefaults);
    toolBar->addSeparator();
    toolBar->addAction(actionLogs);
    toolBar->addAction(actionAbout);
}

/*************************************************************/

void MainWindow::init()
{

}

/*************************************************************/
