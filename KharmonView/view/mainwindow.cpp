#include "mainwindow.h"

#include <QtWidgets>

using namespace KharmonView;

/*************************************************************/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , actionNew         (new QAction(this))
    , actionOpen        (new QAction(this))
    , actionSave        (new QAction(this))
    , actionSaveAs      (new QAction(this))
    , actionExit        (new QAction(this))
    , actionObjAdd      (new QAction(this))
    , actionObjEdit     (new QAction(this))
    , actionObjRemove   (new QAction(this))
    , actionAbout       (new QAction(this))
    , actionDefaults    (new QAction(this))
    , objectTree        (new QTreeView(this))
    , navPath           (new QLabel(this))
    , modelList         (new QTreeView(this))
    , propertyList      (new QTreeView(this))
    , editName          (new QLineEdit(this))
    , editHost          (new QLineEdit(this))
    , editModIndex      (new QLineEdit(this))
    , editSnmpPort      (new QLineEdit(this))
    , editSnmpVersion   (new QLineEdit(this))
    , editSnmpCommunity (new QLineEdit(this))
    , editSnmpTimeout   (new QLineEdit(this))
    , editSnmpRetries   (new QLineEdit(this))
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

    if (index.isValid()) {
        editName->setText(node->getName());
    } else {
        editName->setText(SnmpObject::objectTitle());
    }

    if (node->getModIdx()) {
        editModIndex->setText(QString::number(node->getModIdx()));
        editModIndex->setEnabled(true);
    } else {
        editModIndex->clear();
        editModIndex->setDisabled(true);
    }

    editHost->setText(node->getHost());
    editSnmpPort->setText(QString::number(node->getPort()));
    editSnmpVersion->setText(QString::number(node->getVersion()));
    editSnmpCommunity->setText(node->getCommunity());
    editSnmpTimeout->setText(QString::number(node->getTimeout()));
    editSnmpRetries->setText(QString::number(node->getRetries()));
}

/*************************************************************/

void MainWindow::setupUI()
{
    setObjectName(QStringLiteral("MainWindow"));
    resize(800, 600);
    setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
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

    QLabel *objectInfo = new QLabel(this);
    objectInfo->setText("Object Info");
    navPath->setText("Navigation Path");

    QFormLayout *objectForm = new QFormLayout();
    objectForm->setHorizontalSpacing(10);
    objectForm->addRow(objectInfo);
    objectForm->addRow(tr("name"), editName);
    objectForm->addRow(tr("host"), editHost);
    objectForm->addRow(tr("module"), editModIndex);
    objectForm->addRow(tr("snmp_port"), editSnmpPort);
    objectForm->addRow(tr("snmp_version"), editSnmpVersion);
    objectForm->addRow(tr("snmp_community"), editSnmpCommunity);
    objectForm->addRow(tr("snmp_timeout"), editSnmpTimeout);
    objectForm->addRow(tr("snmp_retries"), editSnmpRetries);

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->setObjectName(QStringLiteral("leftLayout"));
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->addWidget(objectTree);
    leftLayout->addLayout(objectForm);

    QWidget *leftWidget = new QWidget(this);
    leftWidget->setLayout(leftLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->setObjectName(QStringLiteral("rightLayout"));
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->addWidget(navPath);
    rightLayout->addWidget(modelList);
    rightLayout->addWidget(propertyList);

    QWidget *rightWidget = new QWidget(this);
    rightWidget->setLayout(rightLayout);

    QSplitter *splitter = new QSplitter(this);
    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);

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

    actionObjEdit->setObjectName(QStringLiteral("actionObjEdit"));
    actionObjEdit->setIcon(QIcon::fromTheme(QStringLiteral("format-text-direction-ltr")));
    actionObjEdit->setText(QApplication::translate("MainWindow", "Edit object", Q_NULLPTR));

    actionObjRemove->setObjectName(QStringLiteral("actionObjRemove"));
    actionObjRemove->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    actionObjRemove->setText(QApplication::translate("MainWindow", "Remove object", Q_NULLPTR));

    actionAbout->setObjectName(QStringLiteral("actionAbout"));
    actionAbout->setIcon(QIcon::fromTheme(QStringLiteral("help-about")));
    actionAbout->setText(QApplication::translate("MainWindow", "About", Q_NULLPTR));

    actionDefaults->setObjectName(QStringLiteral("actionDefaults"));
    actionDefaults->setIcon(QIcon::fromTheme(QStringLiteral("preferences-system")));
    actionDefaults->setText(QApplication::translate("MainWindow", "Defaults", Q_NULLPTR));
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
    toolBar->addAction(actionAbout);
}

/*************************************************************/

void MainWindow::init()
{

}

/*************************************************************/
