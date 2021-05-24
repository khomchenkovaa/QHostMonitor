#include "mainwindow.h"

#include "snmpmodulemodel.h"
#include "snmpparammodel.h"

#include <QtWidgets>

using namespace KharmonView;

/*************************************************************/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow (parent)
    , actionNew              (new QAction(this))
    , actionOpen             (new QAction(this))
    , actionSave             (new QAction(this))
    , actionSaveAs           (new QAction(this))
    , actionExit             (new QAction(this))
    , actionObjAdd           (new QAction(this))
    , actionObjEdit          (new QAction(this))
    , actionObjRemove        (new QAction(this))
    , actionAbout            (new QAction(this))
    , actionDefaults         (new QAction(this))
    , objectTree             (new QTreeView(this))
    , modelList              (new QTreeView(this))
    , propertyList           (new QTreeView(this))
    , editName               (new QLineEdit(this))
    , editHost               (new QLineEdit(this))
    , editModIndex           (new QLineEdit(this))
    , editSnmpPort           (new QLineEdit(this))
    , editSnmpVersion        (new QLineEdit(this))
    , editSnmpCommunity      (new QLineEdit(this))
    , editSnmpTimeout        (new QLineEdit(this))
    , editSnmpRetries        (new QLineEdit(this))
    , editSysName            (new QLineEdit(this))
    , editSysDescr           (new QLineEdit(this))
    , editSysLocation        (new QLineEdit(this))
    , editSysContact         (new QLineEdit(this))
    , editSysType            (new QLineEdit(this))
    , editSysParentObjectURI (new QLineEdit(this))
    , editStatStatus         (new QLineEdit(this))
    , editStatStatusDescr    (new QLineEdit(this))
    , editStatLastChangeDate (new QLineEdit(this))
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
    modelList->setModel(new SnmpModuleModel());
    propertyList->setModel(new SnmpParamModel());
    QObject::connect(objectTree->selectionModel(), &QItemSelectionModel::currentChanged,
                     this, &MainWindow::updateInfo);
    QObject::connect(modelList->selectionModel(), &QItemSelectionModel::currentChanged,
                     this, &MainWindow::updateParams);
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

    setLineEditValue(editHost, node->getHost(), node->isHostValid());
    setLineEditValue(editSnmpPort, QString::number(node->getPort()), node->isPortValid());
    setLineEditValue(editSnmpVersion, QString::number(node->getVersion()), node->isVersionValid());
    setLineEditValue(editSnmpCommunity, node->getCommunity(), node->isCommunityValid());
    setLineEditValue(editSnmpTimeout, QString::number(node->getTimeout()), node->isTimeoutValid());
    setLineEditValue(editSnmpRetries, QString::number(node->getRetries()), node->isRetriesValid());

    editSysName->setText(node->snmpSystem()->sysName);
    editSysDescr->setText(node->snmpSystem()->sysDescr);
    editSysLocation->setText(node->snmpSystem()->sysLocation);
    editSysContact->setText(node->snmpSystem()->sysContact);
    editSysType->setText(QString::number(node->snmpSystem()->sysType));
    editSysParentObjectURI->setText(node->snmpSystem()->sysParentObjectURI);

    editStatStatus->setText(QString::number(node->snmpStatus()->statStatus));
    editStatStatusDescr->setText(node->snmpStatus()->statStatusDesc);
    editStatLastChangeDate->setText(node->snmpStatus()->statLastChangeDate);

    SnmpModuleModel *modModel = qobject_cast<SnmpModuleModel *>(modelList->model());
    modModel->setObject(node);
    SnmpParamModel *paramModel = qobject_cast<SnmpParamModel *>(propertyList->model());
    if (node->getModIdx()) {
        paramModel->setObject(node, node->getModIdx());
    } else {
        paramModel->setObject(Q_NULLPTR, 0);
    }
}

/*************************************************************/

void MainWindow::updateParams(const QModelIndex &index)
{
    SnmpParamModel *paramModel = qobject_cast<SnmpParamModel *>(propertyList->model());
    if (!index.isValid()) {
        paramModel->setObject(Q_NULLPTR, 0);
        return;
    }
    SnmpModuleModel *modModel = qobject_cast<SnmpModuleModel *>(modelList->model());
    QModelIndex modelIndex = modModel->index(index.row(), 7);
    QVariant data = modModel->data(modelIndex);
    paramModel->setObject(modModel->getObject(), data.toString().toLong());
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

    QString style =
        "QTreeView::item:!selected { "
        "border: 1px solid gainsboro; "
        "border-left: none; "
        "border-top: none; "
        "} "
        "QTreeView::item:selected {}";

    modelList->setStyleSheet(style);
    modelList->setAlternatingRowColors(true);
    modelList->setIndentation(0);
    modelList->setFont(font);
    modelList->header()->setFont(font);

    propertyList->setStyleSheet(style);
    propertyList->setAlternatingRowColors(true);
    propertyList->setIndentation(0);
    propertyList->setFont(font);
    propertyList->header()->setFont(font);

    QFormLayout *objectForm = new QFormLayout();
    objectForm->setHorizontalSpacing(10);
    objectForm->setVerticalSpacing(2);
    objectForm->addRow(new QLabel(tr("Object Info"), this));
    objectForm->addRow(tr("name"), editName);
    objectForm->addRow(tr("host"), editHost);
    objectForm->addRow(tr("module"), editModIndex);
    objectForm->addRow(tr("snmp_port"), editSnmpPort);
    objectForm->addRow(tr("snmp_version"), editSnmpVersion);
    objectForm->addRow(tr("snmp_community"), editSnmpCommunity);
    objectForm->addRow(tr("snmp_timeout"), editSnmpTimeout);
    objectForm->addRow(tr("snmp_retries"), editSnmpRetries);

    QFormLayout *sysForm = new QFormLayout();
    sysForm->setHorizontalSpacing(10);
    sysForm->setVerticalSpacing(2);
    sysForm->addRow(new QLabel(tr("System Info"), this));
    sysForm->addRow(tr("Name"), editSysName);
    sysForm->addRow(tr("Description"), editSysDescr);
    sysForm->addRow(tr("Location"), editSysLocation);
    sysForm->addRow(tr("Contact"), editSysContact);
    sysForm->addRow(tr("Type"), editSysType);
    sysForm->addRow(tr("Parent URI"), editSysParentObjectURI);

    QFormLayout *statForm = new QFormLayout();
    statForm->setHorizontalSpacing(10);
    statForm->setVerticalSpacing(2);
    statForm->addRow(new QLabel(tr("Status Info"), this));
    statForm->addRow(tr("Status"), editStatStatus);
    statForm->addRow(tr("Status Description"), editStatStatusDescr);
    statForm->addRow(tr("Last Change Date"), editStatLastChangeDate);

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->setObjectName(QStringLiteral("leftLayout"));
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->addWidget(objectTree);
    leftLayout->addLayout(objectForm);

    QWidget *leftWidget = new QWidget(this);
    leftWidget->setLayout(leftLayout);

    QHBoxLayout *sysStatLayout = new QHBoxLayout();
    sysStatLayout->addLayout(sysForm);
    sysStatLayout->addLayout(statForm);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->setObjectName(QStringLiteral("rightLayout"));
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->addLayout(sysStatLayout);
    rightLayout->addWidget(modelList);
    rightLayout->addWidget(propertyList);

    QWidget *rightWidget = new QWidget(this);
    rightWidget->setLayout(rightLayout);

    QSplitter *splitter = new QSplitter(this);
    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);

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

void MainWindow::setLineEditValue(QLineEdit *widget, const QString &value, bool isValid)
{
    widget->setText(value);
    QPalette palette = widget->palette();
    palette.setColor(QPalette::Base, isValid? Qt::white : Qt::yellow);
    widget->setPalette(palette);
}

/*************************************************************/
