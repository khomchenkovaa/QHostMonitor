#include "qMainForm.h"
#include "ui_qMainForm.h"

#include <QtWidgets>

#include "tRoot.h"
#include "qPauseMonitoringDlg.h"
#include "qTestPauseDialog.h"
#include "qTestPlannedPauseDlg.h"
#include "qTestInfoDlg.h"
#include "qTestHistoryChartsDlg.h"
#include "qAckDlg.h"
#include "qPatternsDlg.h"
#include "qOptionsForm.h"
#include "qPalettesWin.h"
#include "qMailProfilesDlg.h"
#include "qReportProfilesDlg.h"
#include "qGlobalUserVariables.h"
#include "qActionProfiles.h"
#include "qConnectionManagerDlg.h"
#include "qUserPreferencesDlg.h"
#include "qOperatorsDlg.h"
#include "qLoginAsDlg.h"
#include "qHostMonDlg.h"
#include "qLinksList.h"
#include "qShellMng.h"
#include "qAboutDlg.h"
#include "qTestListProperties.h"
#include "qFolderDlg.h"
#include "qCommonViewPropertiesDlg.h"
#include "qDynamicViewPropertiesDlg.h"
#include "qFolderPropertiesDlg.h"
#include "qExportToTxtDlg.h"
#include "qImportFromTxtFileDlg.h"
#include "viewmodel/mFoldersAndViewsModel.h"
#include "viewmodel/mTestListModel.h"
#include "viewmodel/mTestListSortingModel.h"
#include "gSettings.h"
#include "io/ioTextFile.h"
#include "hIOShellScripts.h"
#include "io/ioUserVarsLoader.h"
#include "io/ioMailProfileLoader.h"
#include "io/ioColorProfileLoader.h"
#include "io/ioActionProfileLoader.h"
#include "hmScriptRunner.h"
#include "actionService.h"
#include "monitoringService.h"
#include "qActionPopupEvent.h"

#include "utils.h"

namespace SDPO {

/******************************************************************/

MainForm::MainForm(HMListService *hml, ActionService *act, MonitoringService *monitoring, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm),
    m_HML(hml),
    m_ActionService(act),
    m_MonitoringService(monitoring),
    hostMonDlg(new HostMonDlg(m_HML,this))
{
    ui->setupUi(this);
    this -> setTrayIconActions();
    this -> showTrayIcon();

    m_folders = 0;
    m_views = 0;
    m_model = 0;

    connect(m_ActionService, SIGNAL(actionWinPopup(TTest*)), this, SLOT(onActionWinPopup(TTest*)), Qt::QueuedConnection);
    connect(ui->trvTestList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTestListContextMenu(QPoint)));

    ui->btnToolbarAdd->setMenu(ui->mnuTestAdd);
    ui->btnToolbarRefresh->setMenu(ui->mnuTestRefresh);
    ui->btnToolbarReset->setMenu(ui->mnuTestReset);
}

/******************************************************************/

void MainForm::init() {
    setupFolders();

    ui->pnlFoldersTree->setHidden(!ui->actFoldersTree->isChecked());
    ui->pnlFoldersLine->setHidden(!ui->actFolderLine->isChecked());
    ui->statusBar->setHidden(!ui->actStatusBar->isChecked());
    if (ui->actQuickLog->isChecked()) {
        ui->actInfoPane->setChecked(false);
    }
    ui->pnlInfoPane->setHidden(!ui->actInfoPane->isChecked());
    ui->tblQuickLogView->setHidden(!ui->actQuickLog->isChecked());
    ui->lvTestList->setHidden(true);

    resetScriptMenu();
}

/******************************************************************/

MainForm::~MainForm() {
    Utils::DestructorMsg(this);
    delete m_folders;
    delete m_views;
    delete hostMonDlg;
    delete ui;
}

/******************************************************************/

void MainForm::setupFolders()
{
    // model
    resetModel();
    connect(m_HML, SIGNAL(modelChanged()), this, SLOT(resetModel()));
    // HostMonDlg
    connect(hostMonDlg, SIGNAL(testAdded(TTest*)), this, SLOT(onTestAdded(TTest*)));
    connect(hostMonDlg, SIGNAL(testChanged(TTest*)), this, SLOT(onTestChanged(TTest*)));
    // alerts
    connect(m_HML, SIGNAL(alertsEnabled(bool)), this, SLOT(onAlertsEnabled(bool)));
    connect(ui->actEnableAlerts, SIGNAL(triggered()), m_HML, SLOT(cmdAlertsEnable()));
    connect(ui->btnToolbarAlert, SIGNAL(clicked()), m_HML, SLOT(cmdAlertsEnable()));
    connect(ui->actDisableAlerts, SIGNAL(triggered()),m_HML, SLOT(cmdAlertsDisable()));
    m_HML->cmdAlertsEnable();
    // monitoring
    connect(m_HML, SIGNAL(monitoringStarted(bool)), this, SLOT(onMonitoringStarted(bool)));
    connect(ui->actStartMonitoring, SIGNAL(triggered()), m_HML, SLOT(cmdMonitoringStart()));
    connect(ui->btnToobarStart, SIGNAL(clicked()), m_HML, SLOT(cmdMonitoringStart()));
    connect(ui->actStopMonitoring, SIGNAL(triggered()), m_HML, SLOT(cmdMonitoringStop()));
    m_HML->cmdMonitoringStart();
}

/******************************************************************/

void MainForm::resetModel()
{    
    if (m_folders) delete m_folders;
    m_folders = new FoldersAndViewsModel(m_HML, FoldersAndViewsModel::FOLDERS);
    ui->treeFolders->setModel(m_folders);
    ui->treeFolders->setCurrentIndex(m_folders->index(0,0));
    connect(ui->treeFolders->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(onTreeFolderChanged()));

    GColorProfile fProfile = GData::getColorProfile(m_HML->rootFolder()->getColorScheme());
    QString fStyle = QString("color: %1; background-color: %2; font: 9pt \"DejaVu Sans\";").arg(fProfile.htmlText.at(0).name(),fProfile.htmlText.at(1).name());
    ui->treeFolders->setStyleSheet(fStyle);

    if (m_views) delete m_views;
    m_views = new FoldersAndViewsModel(m_HML, FoldersAndViewsModel::VIEWS);
    ui->treeView->setModel(m_views);
    ui->treeView->setCurrentIndex(m_views->index(0,0));
    connect(ui->treeView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(onTreeViewChanged()));

    GColorProfile vProfile = GData::getColorProfile(m_HML->rootView()->getColorScheme());
    QString vStyle = QString("color: %1; background-color: %2; font: 9pt \"DejaVu Sans\";").arg(vProfile.htmlText.at(0).name(),vProfile.htmlText.at(1).name());
    ui->treeView->setStyleSheet(vStyle);

    if (m_model) delete m_model;
    m_model = new TestListModel();
    connect(m_HML, SIGNAL(testAdded(TNode*)), m_model, SLOT(addTest(TNode*)));
    connect(m_HML, SIGNAL(linkAdded(TNode*)), m_model, SLOT(addTest(TNode*)));
    connect(m_HML->rootItem(), SIGNAL(pasteTest(TNode*)), m_model, SLOT(addTest(TNode*)));
    connect(m_HML->rootItem(), SIGNAL(delTest(TNode*)), m_model, SLOT(removeTest(TNode*)));
    connect(m_HML->rootItem(), SIGNAL(cutTest(TNode*)), m_model, SLOT(removeTest(TNode*)));
    connect(m_HML->rootItem(), SIGNAL(delLink(TNode*)), m_model, SLOT(removeTest(TNode*)));
    connect(m_HML, SIGNAL(testUpdated(TNode*)), m_model, SLOT(updateTest(TNode*)));
    m_model->setCurrent(m_HML->rootFolder());
    m_filterModel = new TestListSortingModel(this);
    m_filterModel->setSourceModel(m_model);
    ui->trvTestList->setModel(m_filterModel);
    ui->lvTestList->setModel(m_filterModel);
    connect(ui->trvTestList->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(onTestListSelectionChanged()));

    onTreeViewChanged();
    onTreeFolderChanged();
    activateActions(false);
}

/******************************************************************/

void MainForm::resetScriptMenu()
{
    QList<QAction *> actions = ui->mnuTestAddShellScript->actions();
    QMutableListIterator<QAction*> i(actions);
    while(i.hasNext()) {
        QAction *act = i.next();
        if (act->data().isValid()) {
            qDebug() << act->data().toString();
            disconnect(act,SIGNAL(triggered()),this,SLOT(onShellScript()));
            ui->mnuTestAddShellScript->removeAction(act);
            delete act;
        }
    }
    IOShellScripts loader;
    QList<ShellScript*> scripts = loader.load(QCoreApplication::applicationDirPath() + "/scripts");
    foreach(ShellScript* script, scripts) {
        QAction *action = new QAction(script->getName(), ui->mnuTestAddShellScript);
        action->setIcon(*new QIcon(":/img/action/shScript.png"));
        action->setData(script->getFileName());
        ui->mnuTestAddShellScript->addAction(action);
        connect(action,SIGNAL(triggered()),this,SLOT(onShellScript()));
    }
    qDeleteAll(scripts);
}

/******************************************************************/

void MainForm::onTestAdded(TTest *test)
{
    TNode *item = m_folders->itemFromIndex(ui->treeFolders->currentIndex());
    m_HML->addNode(item, test);
}

/******************************************************************/

void MainForm::onTestChanged(TTest *test)
{
    m_model->updateTest(test);
}

/******************************************************************/

void MainForm::onTreeFolderChanged()
{
    QModelIndex idx = ui->treeFolders->currentIndex();
    TNode *item = m_folders->itemFromIndex(idx);
    m_HML->setCurrentFolder(item);

    ui->btnNewFolder->setEnabled(m_folders->parent(idx).isValid());
    ui->btnDelFolder->setEnabled(m_folders->parent(idx).isValid());
    ui->editFoldersLine->setText(item->getPath());
//    ui->trvTestList->repaint();
//    ui->lvTestList->repaint();
    // update style
    GColorProfile profile = GData::getColorProfile(item->getColorScheme());
    QString style = QString("color: %1; background-color: %2; font: 8pt \"DejaVu Sans\";").arg(profile.htmlText.at(0).name(),profile.htmlText.at(1).name());
    ui->trvTestList->setStyleSheet(style);
    ui->lvTestList->setStyleSheet(style);
    ui->wMainInfoPane->setStyleSheet(style);
    // update test list
    GUserProfile userProfile = GData::getCurrentUserProfile();
    m_model->setRecursive(userProfile.showTestsInSubfolders);
    m_model->setCurrent(item);
    // update Info pane
    //int testVisible = m_filterModel->rowCount();
    int testVisible = m_model->rowCount(idx);
    ui->wMainInfoPane->folderInfo(m_HML, testVisible, 0);
}

/******************************************************************/

void MainForm::onTreeViewChanged()
{
    QModelIndex idx = ui->treeView->currentIndex();
    TNode *item = m_views->itemFromIndex(idx);

    ui->btnViewCopy->setEnabled(m_views->parent(idx).isValid());
    ui->btnViewDel->setEnabled(m_views->parent(idx).isValid());
    ui->editFoldersLine->setText(item->getPath());
    // update style
    GColorProfile profile = GData::getColorProfile(item->getColorScheme());
    QString style = QString("color: %1; background-color: %2; font: 8pt \"DejaVu Sans\";").arg(profile.htmlText.at(0).name(),profile.htmlText.at(1).name());
    ui->trvTestList->setStyleSheet(style);
    ui->lvTestList->setStyleSheet(style);
    ui->wMainInfoPane->setStyleSheet(style);
    // update test list
    m_model->setRecursive(false);
    m_model->setCurrent(item);
    // update Info pane
    int testVisible = m_model->rowCount(idx);
    ui->wMainInfoPane->folderInfo(m_HML, testVisible, 0);
}

/******************************************************************/

void MainForm::onActionWinPopup(TTest *test)
{
    ActionPopupEvent dlg(test,this);
    QSettings s;
    if (s.value(SKEY_HOSTMON_MsgWinConstPos, 0).toInt()) {
        int x = s.value(SKEY_HOSTMON_MsgWinXPos, 200).toInt();
        int y = s.value(SKEY_HOSTMON_MsgWinYPos, 100).toInt();
        dlg.move(x,y);
    }
    dlg.exec();
}

/******************************************************************/

void MainForm::onMonitoringStarted(bool value)
{
    ui->actStartMonitoring->setDisabled(value);
    ui->actStopMonitoring->setEnabled(value);
    ui->btnToobarStart->setHidden(value);
    ui->lineToolbarStart->setHidden(value);
}

/******************************************************************/

void MainForm::onAlertsEnabled(bool value)
{
    ui->actEnableAlerts->setDisabled(value);
    ui->actDisableAlerts->setEnabled(value);
    ui->btnToolbarAlert->setHidden(value);
    ui->lineToolbarAlerts->setHidden(value);
}

/******************************************************************/

void MainForm::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if (event -> type() == QEvent::WindowStateChange) {
        if (isMinimized()) {
            this -> hide();
        }
    }
}

/******************************************************************/

void MainForm::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        this -> trayActionExecute();
        break;
    default:
        break;
    }
}

/******************************************************************/

void MainForm::trayActionExecute()
{
    this->showNormal();
}

/******************************************************************/

void MainForm::setTrayIconActions()
{
    // Setting actions...
     showAction = new QAction("Show", this);
     quitAction = new QAction("Exit", this);

     // Connecting actions to slots...
     connect (showAction, SIGNAL(triggered()), this, SLOT(showNormal()));
     connect (quitAction, SIGNAL(triggered()), this, SLOT(on_actExit_triggered()));

     // Setting system tray's icon menu...
     trayIconMenu = new QMenu(this);
     trayIconMenu -> addAction (showAction);
     trayIconMenu -> addAction (ui->actStartMonitoring);
     trayIconMenu -> addAction (ui->actStopMonitoring);
     trayIconMenu -> addAction (quitAction);
}

/******************************************************************/

void MainForm::showTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/img/hostMonitor.png");
    trayIcon -> setIcon(trayImage);
    trayIcon -> setContextMenu(trayIconMenu);

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    trayIcon -> show();
}
/******************************************************************/

void MainForm::onTestListContextMenu(const QPoint &pos)
{
    QMenu menu(this);
    QMenu menuRefresh(tr("Refresh"),&menu);
    QIcon icon(":/img/action/refresh.png");
    menuRefresh.setIcon(icon);
    menuRefresh.addAction(ui->actRefreshFolderOnly);
    menuRefresh.addAction(ui->actRefreshFolderWithChilds);
    menuRefresh.addAction(ui->actRefreshAll);

    menu.addAction(ui->actAcknowledge);
    menu.addSeparator();
    menu.addAction(ui->actTestEdit);
    menu.addAction(ui->actTestAdd);
    menu.addAction(ui->actTestCopy);
    menu.addAction(ui->actLink);
    menu.addAction(ui->actLinkInfo);
    menu.addAction(ui->actTestRemove);
    menu.addSeparator();
    menu.addMenu(&menuRefresh);
    menu.addAction(ui->actTestPause);
    menu.addAction(ui->actTestResume);
    menu.addSeparator();
    menu.addAction(ui->actDisableSelectedTests);
    menu.addAction(ui->actEnableSelectedTests);
    menu.addAction(ui->actDisableThisFolder);
    menu.addAction(ui->actEnableThisFolder);
    menu.addSeparator();
    menu.addAction(ui->actTestInfo);
    menu.addAction(ui->actHistoryCharts);
    menu.addAction(ui->Realtimechart1);
    menu.addAction(ui->Systeminfo1);
    menu.addSeparator();
    menu.addAction(ui->actLogAnalizer);
    menu.addAction(ui->actViewPrivateLog);
    menu.addSeparator();
    menu.addAction(ui->RelatedURL1);
    menu.addAction(ui->Trace2);
    menu.addAction(ui->Telnet2);
    menu.addAction(ui->ExploreWMI1);
    menu.addAction(ui->ProcessMeter1);
    menu.addSeparator();
    menu.addAction(ui->actionCustom);
    menu.exec(ui->trvTestList->mapToGlobal(pos));
}

/******************************************************************/

void MainForm::onTestListSelectionChanged()
{
    activateActions(ui->trvTestList->selectionModel()->hasSelection());
    QModelIndexList indexList = ui->trvTestList->selectionModel()->selectedRows();
    int testSelected = indexList.count();

    if (testSelected == 1) { // show test info
        QModelIndex index = ui->trvTestList->currentIndex();
        TNode* item = m_model->itemFromIndex(m_filterModel->mapToSource(index));
        if (item->getType() == TNode::TEST || item->getType() == TNode::LINK) {
            ui->wMainInfoPane->testInfo(item);
        } else {
            int testVisible = item->testsCount();
            ui->wMainInfoPane->folderInfo(m_HML, testVisible, testSelected);
        }
    } else { // show folder and selection info
//        QStandardItem *item;
//        if (ui->tabFoldersTree->currentIndex() == 0) { // folders
//            item = m_folders->itemFromIndex(ui->treeFolders->currentIndex());
//        } else {
//            item = m_views->itemFromIndex(ui->treeView->currentIndex());
//        }
//        QString path = getQStandardItemPath(item);
//        TNode* node = m_nodes->findByPath(path);
        int testVisible = ui->trvTestList->model()->rowCount();
        ui->wMainInfoPane->folderInfo(m_HML, testVisible, testSelected);
    }
}

/******************************************************************/

TNode *MainForm::getItemFromFolderPath(QString path) {
    QModelIndex idx = m_folders->indexFromPath(path);
    return m_folders->itemFromIndex(idx);
}

/******************************************************************/

TNode *MainForm::getItemFromViewsPath(QString path) {
    QModelIndex idx = m_views->indexFromPath(path);
    return m_views->itemFromIndex(idx);
}

/******************************************************************/

void MainForm::activateActions(const bool actionEnabled)
{
    ui->actTestEdit->setEnabled(actionEnabled);
    ui->actTestCopy->setEnabled(actionEnabled);
    ui->actLink->setEnabled(actionEnabled);
    ui->actLinkInfo->setEnabled(actionEnabled);
    ui->actTestRemove->setEnabled(actionEnabled);
    ui->actTestRemoveWithLinks->setEnabled(actionEnabled);
    ui->actTestEnable->setEnabled(actionEnabled); //! TODO
    ui->actTestDisable->setEnabled(actionEnabled); //! TODO
    ui->actTestPause->setEnabled(actionEnabled); //! TODO
    ui->actTestResume->setEnabled(actionEnabled); //! TODO
    ui->actPlannedPause->setEnabled(actionEnabled);
    ui->actRefreshSelectedTests->setEnabled(actionEnabled);
    ui->actResetSelectedTests->setEnabled(actionEnabled);
    ui->actAcknowledge->setEnabled(actionEnabled);
    ui->actTestInfo->setEnabled(actionEnabled);
    ui->actHistoryCharts->setEnabled(actionEnabled);
    ui->actLogAnalizer->setEnabled(actionEnabled);
    ui->actViewPrivateLog->setEnabled(actionEnabled);
    ui->btnToolbarEdit->setEnabled(actionEnabled);
    ui->btnToolbarDel->setEnabled(actionEnabled);
}

/******************************************************************/
// File menu
/******************************************************************/

void MainForm::on_actNewTestList_triggered()
{
    if (m_HML->isModelModified()) {
        int ret = QMessageBox::question(this,tr("Confirm"),
                                        tr("Changes in the TestList have not been saved. Save now?"),
                                        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                        QMessageBox::Yes);
        switch (ret) {
            case QMessageBox::Yes: on_actSave_triggered(); break;
            case QMessageBox::No: break;
            case QMessageBox::Cancel: return;
            default: return;
        }
    }
    m_HML->cmdNewTestList();
}

/******************************************************************/

void MainForm::on_actLoadTestList_triggered()
{
    if (m_HML->isModelModified()) {
        QMessageBox msgBox;
        msgBox.setText(tr("Changes in the TestList have not been saved."));
        msgBox.setInformativeText(tr("Save now?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        switch (ret) {
            case QMessageBox::Yes: on_actSave_triggered(); break;
            case QMessageBox::No: break;
            case QMessageBox::Cancel: return;
            default: return;
        }
    }
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load test list"),QString(),"HostMonitorList(*.hml)");
    if (!fileName.isEmpty()) {
        m_HML->cmdLoadTestList(fileName);
    }
}

/******************************************************************/

void MainForm::on_actAppendFromHML_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Append test list"),QString(),"HostMonitorList(*.hml)");
    if (!fileName.isEmpty()) {
        m_HML->cmdAppendTestList(fileName);
    }
}

/******************************************************************/

void MainForm::on_actImportFromTxtFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Import from text file"),QString(),"ImportFiles(*.hmi *.txt)");
    if (fileName.isEmpty()) return;
    int foldersCnt = 0;
    int testsCnt = 0;
    QString errorMsg;
    IOTextFile importer(m_HML, fileName);
    bool validateResult = importer.validateImportTextFile(errorMsg, foldersCnt, testsCnt);
    if (!validateResult) {
        //! TODO print some errors here
        return;
    }
    int confirm = QMessageBox::question(this, "Confirm",
                                    QString("%1 test(s) will be imported into %2 folder(s). Proceed?").arg(testsCnt).arg(foldersCnt));
    if(QMessageBox::Yes != confirm)  {
        return;
    }
    ImportFromTxtFileDlg importDlg(&importer);
    importDlg.exec();
    // importer.importTextFile();
}

/******************************************************************/

void MainForm::on_actExportToTxtFile_triggered()
{
    ExportToTxtDlg dlg;
    dlg.setSelectedTests(false); //! TODO check tests selection
    int result = dlg.exec();
    if (result != QDialog::Accepted) {
        return;
    }

    QString fileName = dlg.targetFile();
    bool incFolder = dlg.isFolderIncluded();
    bool incLinks = dlg.isLinksIncluded();
    int expType = dlg.exportType();
    if (!fileName.isEmpty()) {
        IOTextFile exporter(m_HML, fileName);
        exporter.exportTextFile(incFolder, incLinks, expType);
    }
}

/******************************************************************/

void MainForm::on_actExecuteScript_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Execute script"),QString(),"HMScript(*.hms)");
    if (fileName.isEmpty()) return;
    HMScriptRunner runner(m_HML,fileName);
    if(!runner.run()) {
        qDebug() << runner.scriptErrors();
    }
}

/******************************************************************/

void MainForm::on_actSave_triggered()
{
    if (m_HML->isCurFileExists()) {
        m_HML->cmdSaveTestList();
    } else {
        on_actSaveAs_triggered();
    }
}

/******************************************************************/

void MainForm::on_actSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save as..."),QString(),"HostMonitorList(*.hml)");
    if (!fileName.isEmpty()) {
        m_HML->cmdSaveTestList(fileName);
    };
}

/******************************************************************/

void MainForm::on_actProperties_triggered()
{
    TestListProperties propertiesDlg;
    propertiesDlg.setFileName(m_HML->currentFileName());
    propertiesDlg.setGuid(m_HML->guid());
    propertiesDlg.setFoldersCnt(m_HML->rootItem()->foldersCnt());
    propertiesDlg.setViewsCnt(m_HML->rootItem()->viewsCnt());
    propertiesDlg.setTestsCnt(m_HML->rootItem()->testsCnt());
    propertiesDlg.setTotalRecords(m_HML->rootItem()->totalCnt());
    propertiesDlg.setFileSize(m_HML->fileSize());
    propertiesDlg.setStoreHistory(m_HML->isStoreHistoricalData());
    if(propertiesDlg.exec() == QDialog::Accepted) {
        m_HML->setStoreHistoricalData(propertiesDlg.storeHistory());
    }
}

/******************************************************************/

void MainForm::on_actExit_triggered()
{
    QApplication::quit();
}

/******************************************************************/
// Monitoring menu
/******************************************************************/

void MainForm::on_actPause_triggered()
{
    PauseMonitoringDlg dlg(m_MonitoringService, m_ActionService);
    dlg.exec();
}

/******************************************************************/
// Test menu (new)
/******************************************************************/

void MainForm::on_actTestPing_triggered()
{
    hostMonDlg->init(TMethodID::Ping);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestTrace_triggered()
{
    hostMonDlg->init(TMethodID::Trace);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestHTTP_triggered()
{
    hostMonDlg->init(TMethodID::HTTP);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestURL_triggered()
{
    hostMonDlg->init(TMethodID::URL);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestSMTP_triggered()
{
    hostMonDlg->init(TMethodID::SMTP);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestPOP3_triggered()
{
    hostMonDlg->init(TMethodID::POP3);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestIMAP_triggered()
{
    hostMonDlg->init(TMethodID::IMAP);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actMailRelay_triggered()
{
    hostMonDlg->init(TMethodID::MailRelay);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestTCP_triggered()
{
    hostMonDlg->init(TMethodID::TCP);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestUDP_triggered()
{
    hostMonDlg->init(TMethodID::UDP);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestRadius_triggered()
{
    hostMonDlg->init(TMethodID::Radius);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestDNS_triggered()
{
    hostMonDlg->init(TMethodID::DNS);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestDHCP_triggered()
{
    hostMonDlg->init(TMethodID::DHCP);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestNTP_triggered()
{
    hostMonDlg->init(TMethodID::NTP);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestLDAP_triggered()
{
    hostMonDlg->init(TMethodID::Ldap);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestDICOM_triggered()
{
    hostMonDlg->init(TMethodID::DICOM);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestRAS_triggered()
{
    hostMonDlg->init(TMethodID::RAS);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestDriveFreeSpace_triggered()
{
    hostMonDlg->init(TMethodID::DriveSpace);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestCompareFiles_triggered()
{
    hostMonDlg->init(TMethodID::FileCompare);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestNTEventsLog_triggered()
{
    hostMonDlg->init(TMethodID::NTLog);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestService_triggered()
{
    hostMonDlg->init(TMethodID::Service);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestProcess_triggered()
{
    hostMonDlg->init(TMethodID::Process);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestCPUUsage_triggered()
{
    hostMonDlg->init(TMethodID::CPU);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actDominantProcess_triggered()
{
    hostMonDlg->init(TMethodID::DominantProcess);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actPerformanceCounter_triggered()
{
    hostMonDlg->init(TMethodID::PerfCounter);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestWMI_triggered()
{
    hostMonDlg->init(TMethodID::WMI);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestUNC_triggered()
{
    hostMonDlg->init(TMethodID::UNC);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestFolderFileSize_triggered()
{
    hostMonDlg->init(TMethodID::FileSize);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestCountFiles_triggered()
{
    hostMonDlg->init(TMethodID::CountFiles);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestFolderFileAvailability_triggered()
{
    hostMonDlg->init(TMethodID::FileExists);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestFileIntegrity_triggered()
{
    hostMonDlg->init(TMethodID::FileContents);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestTextLog_triggered()
{
    hostMonDlg->init(TMethodID::TextLog);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actInterbase_triggered()
{
    hostMonDlg->init(TMethodID::Interbase);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actMSSQL_triggered()
{
    hostMonDlg->init(TMethodID::MSSQL);/******************************************************************/

    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actMySQL_triggered()
{
    hostMonDlg->init(TMethodID::MySQL);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actOracle_triggered()
{
    hostMonDlg->init(TMethodID::Oracle);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actPostgreSQL_triggered()
{
    hostMonDlg->init(TMethodID::Postgre);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actSybase_triggered()
{
    hostMonDlg->init(TMethodID::Sybase);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestODBCQuery_triggered()
{
    hostMonDlg->init(TMethodID::ODBC);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestSNMPGet_triggered()
{
    hostMonDlg->init(TMethodID::SNMP);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actSNMPTrap_triggered()
{
    hostMonDlg->init(TMethodID::SNMPtrap);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestTrafficMonitor_triggered()
{
    hostMonDlg->init(TMethodID::TrafficMonitor);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestActiveScript_triggered()
{
    hostMonDlg->init(TMethodID::Script);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actScriptManager_triggered()
{
    ShellMng shellMng;
    connect(&shellMng,SIGNAL(shellScriptsChanged()),this,SLOT(resetScriptMenu()));
    shellMng.exec();
}

/******************************************************************/

void MainForm::onShellScript()
{
    QAction *action = qobject_cast<QAction*>(sender());
    hostMonDlg->init(TMethodID::ShellScript, action->data());
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestExternal_triggered()
{
    hostMonDlg->init(TMethodID::Externalprg);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestSSH_triggered()
{
    hostMonDlg->init(TMethodID::SSH);
    hostMonDlg->show();
}

/******************************************************************/

void MainForm::on_actTestITTemperatureMonitor_triggered()
{
    hostMonDlg->init(TMethodID::TempMonitor);
    hostMonDlg->show();

}

/******************************************************************/

void MainForm::on_actTestHMMonitor_triggered()
{
    hostMonDlg->init(TMethodID::HMmonitor);
    hostMonDlg->show();

}

/******************************************************************/
// Test menu (other)
/******************************************************************/

void MainForm::on_actTestEdit_triggered()
{
    QModelIndex index = ui->trvTestList->currentIndex();
    on_trvTestList_doubleClicked(index);
}

/******************************************************************/

void MainForm::on_actTestCopy_triggered()
{
    QModelIndex index = ui->trvTestList->currentIndex();
    TNode* item = m_model->itemFromIndex(m_filterModel->mapToSource(index));
    TTest *test;
    if (item->getType() == TNode::TEST) {
        test = qobject_cast<TTest*>(item);
    } else if (item->getType() == TNode::LINK) {
        TLink *link = qobject_cast<TLink*>(item);
        test = link->getTest();
    } else {
        return;
    }

    FolderDlg folderDlg;
    folderDlg.setWindowTitle(tr("COPY: Select destination folder"));
    FoldersAndViewsModel *model = new FoldersAndViewsModel(m_HML, FoldersAndViewsModel::FOLDERS);
    folderDlg.setModel(model, ui->editFoldersLine->text());
    folderDlg.activateButtons();
    if (QDialog::Accepted != folderDlg.exec()) {
        return;
    }

    QString path = folderDlg.path();
    TNode *node = m_HML->nodeByPath(path);
    QString newName = test->testName() + "-copy";
    TTest *newTest = test->clone(m_HML->nextID(), newName);
    m_HML->addNode(node, newTest);

    if (folderDlg.isDisabled()) {
        newTest->setEnabled(false);
    }
    if (folderDlg.isEdit()) {
        hostMonDlg->init(newTest);
        hostMonDlg->show();
    }
}

/******************************************************************/

void MainForm::on_actLink_triggered()
{
    QModelIndex index = ui->trvTestList->currentIndex();
    TNode* item = m_model->itemFromIndex(m_filterModel->mapToSource(index));
    TTest *test;
    if (item->getType() == TNode::TEST) {
        test = qobject_cast<TTest*>(item);
    } else if (item->getType() == TNode::LINK) {
        TLink *link = qobject_cast<TLink*>(item);
        test = link->getTest();
    } else {
        return;
    }

    FolderDlg folderDlg;
    folderDlg.setWindowTitle(tr("LINK: Select destination folder"));
    FoldersAndViewsModel *model = new FoldersAndViewsModel(m_HML, FoldersAndViewsModel::FOLDERS);
    folderDlg.setModel(model, ui->editFoldersLine->text());
    if (QDialog::Accepted != folderDlg.exec()) {
        return;
    }

    QString path = folderDlg.path();
    TNode *node = m_HML->nodeByPath(path);
    test->addLink(node);
    m_HML->addNode(node, new TLink(m_HML->nextID(), test));
}

/******************************************************************/

void MainForm::on_actLinkInfo_triggered()
{
    QModelIndex index = ui->trvTestList->currentIndex();
    TNode* item = m_model->itemFromIndex(m_filterModel->mapToSource(index));
    TRoot* root = qobject_cast<TRoot*>(item->getRoot());
    TTest *test;
    if (item->getType() == TNode::TEST) {
        test = qobject_cast<TTest*>(item);
    } else if (item->getType() == TNode::LINK) {
        TLink *link = qobject_cast<TLink*>(item);
        test = link->getTest();
    } else {
        return;
    }

    LinksList linksDlg(test);
    if (QDialog::Accepted != linksDlg.exec()) {
        return;
    }
    if (linksDlg.getResult() == LinksList::RemoveLinks) {
        QStringList linksChecked = linksDlg.getChecked();
        for (int i=0; i<linksChecked.count(); ++i) {
            root->removeLink(linksChecked.at(i), test);
        }
    } else if (linksDlg.getResult() == LinksList::RemoveTest) {
        root->removeTestWithLinks(test);
    }
}


/******************************************************************/

void MainForm::on_actTestRemove_triggered()
{
    QModelIndex index = ui->trvTestList->currentIndex();
    if (!index.isValid()) return;
    TNode* item = m_model->itemFromIndex(m_filterModel->mapToSource(index));
    TRoot* root = qobject_cast<TRoot*>(item->getRoot());
    int ret = QMessageBox::question(this,tr("Confirm"),
                                    tr("1 item(s) will be removed. Are you sure?"),
                                    QMessageBox::Yes | QMessageBox::No,
                                    QMessageBox::Yes);
    if (ret == QMessageBox::Yes) {
        //! Если линк - удалить его, если тест - переместить тест  на место первого линка
        if (item->getType() == TNode::LINK) {
            root->removeLink(qobject_cast<TLink*>(item));
        } else if (item->getType() == TNode::TEST) {
            root->removeTest(qobject_cast<TTest*>(item));
        }
    }
}

/******************************************************************/

void MainForm::on_actTestRemoveWithLinks_triggered()
{
    QModelIndex index = ui->trvTestList->currentIndex();
    TNode* item = m_model->itemFromIndex(m_filterModel->mapToSource(index));
    TRoot* root = qobject_cast<TRoot*>(item->getRoot());
    TTest *test;
    if (item->getType() == TNode::TEST) {
        test = qobject_cast<TTest*>(item);
    } else if (item->getType() == TNode::LINK) {
        TLink *link = qobject_cast<TLink*>(item);
        test = link->getTest();
    } else {
        return;
    }
    int ret = QMessageBox::question(this,tr("Confirm"),
                                    tr("1 item(s) with links will be removed. Are you sure?"),
                                    QMessageBox::Yes | QMessageBox::No,
                                    QMessageBox::Yes);
    if (ret == QMessageBox::Yes) {
        root->removeTestWithLinks(test);
    }
}

/******************************************************************/

void MainForm::on_actTestPause_triggered()
{
    TestPauseDialog dlg;
    dlg.exec();
}

/******************************************************************/

void MainForm::on_actPlannedPause_triggered()
{
    TestPlannedPauseDlg dlg;
    dlg.exec();
}

/******************************************************************/

void MainForm::on_actRefreshSelectedTests_triggered()
{
    //! TODO
}

/******************************************************************/

void MainForm::on_actResetSelectedTests_triggered()
{
    //! TODO
}

/******************************************************************/

void MainForm::on_actAcknowledge_triggered()
{
    AckDlg ackDlg;
    ackDlg.exec();
}

/******************************************************************/

void MainForm::on_actTestInfo_triggered()
{
    TestInfoDlg dlg;
    dlg.exec();
}

/******************************************************************/

void MainForm::on_actHistoryCharts_triggered()
{
    TestHistoryChartsDlg dlg;
    dlg.exec();
}

/******************************************************************/
// View menu
/******************************************************************/

void MainForm::on_actFoldersTree_triggered(bool checked)
{
    ui->pnlFoldersTree->setHidden(!checked);
}

/******************************************************************/

void MainForm::on_actFolderLine_triggered(bool checked)
{
    ui->pnlFoldersLine->setHidden(!checked);
}

/******************************************************************/

void MainForm::on_actInfoPane_triggered(bool checked)
{
    ui->pnlInfoPane->setHidden(!checked);
    if (checked) {
        ui->actQuickLog->setChecked(false);
        ui->tblQuickLogView->setHidden(true);
    }
}

/******************************************************************/

void MainForm::on_actQuickLog_triggered(bool checked)
{
    ui->tblQuickLogView->setHidden(!checked);
    if (checked) {
        ui->actInfoPane->setChecked(false);
        ui->pnlInfoPane->setHidden(true);
    }
}

/******************************************************************/

void MainForm::on_actStatusBar_triggered(bool checked)
{
    ui->statusBar->setHidden(!checked);
}

/******************************************************************/
// Profiles menu
/******************************************************************/

void MainForm::on_actPatterns_triggered()
{
    PatternsDlg dlg;
    dlg.exec();
}

/******************************************************************/

void MainForm::on_actProfilesScriptManager_triggered()
{
    ShellMng shellMng;
    connect(&shellMng,SIGNAL(shellScriptsChanged()),this,SLOT(resetScriptMenu()));
    shellMng.exec();
}

/******************************************************************/

void MainForm::on_actColorSchemes_triggered()
{
    IOColorProfileLoader loader;
    PalettesWin dlg;
    dlg.init();
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
    } else {
        loader.load();
    }
}

/******************************************************************/

void MainForm::on_actMailProfiles_triggered()
{
    IOMailProfileLoader loader;
    MailProfilesDlg dlg;
    dlg.init(0);
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
    } else {
        loader.load();
    }
}

/******************************************************************/

void MainForm::on_actReportProfiles_triggered()
{
    ReportProfilesDlg dlg;
    dlg.exec();
}

/******************************************************************/

void MainForm::on_actGlobalMacroVars_triggered()
{
    IOUserVarsLoader loader;
    GlobalUserVariables dlg;
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
    } else {
        loader.load();
    }
}

/******************************************************************/

void MainForm::on_actActionsProfiles_triggered()
{
    IOActionProfileLoader loader;
    ActionProfiles dlg;
    dlg.init(0);
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
    } else {
        loader.load();
    }
}

/******************************************************************/

void MainForm::on_actConnectionManager_triggered()
{
    ConnectionManagerDlg dlg;
    dlg.exec();
}

/******************************************************************/

void MainForm::on_actGuiPreferences_triggered()
{
    UserPreferencesDlg dlg;
    if (dlg.exec() == QDialog::Accepted) {
        //! repaint all
    }
}

/******************************************************************/

void MainForm::on_actOperators_triggered()
{
    OperatorsDlg dlg(m_HML);
    dlg.exec();
}

/******************************************************************/

void MainForm::on_actLoginAs_triggered()
{
    LoginAsDlg actOperator;
    actOperator.exec();
}

/******************************************************************/
// Options menu
/******************************************************************/

void MainForm::on_actOptions_triggered()
{
    OptionsForm dlg;
    dlg.exec();
}

/******************************************************************/
// About menu
/******************************************************************/

void MainForm::on_actAbout_triggered()
{
    AboutDlg aboutDlg;
    aboutDlg.exec();
}

/******************************************************************/
// Folders panel
/******************************************************************/

void MainForm::on_tabFoldersTree_currentChanged(int index)
{
    if (index == 0) {
        onTreeFolderChanged();
    } else {
        onTreeViewChanged();
    }
}

/******************************************************************/

void MainForm::on_btnNewFolder_clicked()
{
    QModelIndex idx = ui->treeFolders->currentIndex();
    if (!idx.parent().isValid())
        return;
    bool ok;
    QString name = QInputDialog::getText(this, tr("New folder"),tr("Folder name"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        idx = m_folders->appendFolder(name, idx.parent());
        ui->treeFolders->setCurrentIndex(idx);
    }
}

/******************************************************************/

void MainForm::on_btnNewSubfolder_clicked()
{
    QModelIndex idx = ui->treeFolders->currentIndex();
    if (!idx.isValid())
        return;
    bool ok;
    QString name = QInputDialog::getText(this, tr("New folder"),tr("Folder name"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        idx = m_folders->appendFolder(name, idx);
        ui->treeFolders->setCurrentIndex(idx);
    }
}

/******************************************************************/

void MainForm::on_btnFolderProperties_clicked()
{
    QModelIndex idx = ui->treeFolders->currentIndex();
    if (!idx.isValid())
        return;
    TNode *node = m_folders->itemFromIndex(idx);
    if (node->getType() != TNode::FOLDER) {
        return;
    }
    TFolder *folder = qobject_cast<TFolder*>(node);
    FolderPropertiesDlg dlg(folder, m_HML);
    dlg.exec();
}

/******************************************************************/

void MainForm::on_btnDelFolder_clicked()
{
    QModelIndex idx = ui->treeFolders->currentIndex();
    if (!idx.parent().isValid()) {
        return;
    }
    TFolder *item = qobject_cast<TFolder*>(m_folders->itemFromIndex(idx));
    int foldersCnt = item->foldersTotal();
    int testsCnt = item->testsTotal();
    if (!(foldersCnt + testsCnt)) {
        idx = m_folders->deleteFolder(idx);
    } else {
        QString msg = QString("Folder containts %1 folders and %2 tests\nDelete this folder and tests?").arg(foldersCnt).arg(testsCnt);
        if (QMessageBox::Yes == QMessageBox::question(this,"Confirm", msg)) {
            idx = m_folders->deleteFolder(idx);
        }
    }
    ui->treeFolders->setCurrentIndex(idx);
}

/******************************************************************/
// Views panel
/******************************************************************/

void MainForm::on_btnViewAdd_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("New View"),tr("View name"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        QModelIndex idx = m_views->appendView(name);
        ui->treeView->setCurrentIndex(idx);
    }
}

/******************************************************************/

void MainForm::on_btnViewProperties_clicked()
{
    QModelIndex idx = ui->treeView->currentIndex();
    if (!idx.isValid()) {
        return;
    }
    TNode *node = m_views->itemFromIndex(idx);

    if (node->getType() == TNode::FOLDER) { // Common view properties
        TFolder *folder = qobject_cast<TFolder*>(node);
        CommonViewPropertiesDlg dlg(folder, m_HML);
        dlg.exec();
    } else if (node->getType() == TNode::VIEW) {
        TView *view = qobject_cast<TView*>(node);
        DynamicViewPropertiesDlg dlg(view, m_HML);
        if(QDialog::Accepted == dlg.exec()) {
            onTreeViewChanged();
        }
    }
}

/******************************************************************/

void MainForm::on_btnViewDel_clicked()
{
    QModelIndex idx = ui->treeView->currentIndex();
    if (!idx.isValid())
        return;
    TNode *item = m_views->itemFromIndex(idx);
    if (QMessageBox::Yes == QMessageBox::question(this,"Confirm", QString("View '%1' will be removed. Are You sure?").arg(item->getName()))) {
        idx = m_views->deleteView(idx);
    }
    ui->treeView->setCurrentIndex(idx);
}

/******************************************************************/
// Test list panel
/******************************************************************/

void MainForm::on_btnFoldersLineTree_clicked()
{
    FolderDlg folderDlg;
    FoldersAndViewsModel *model = new FoldersAndViewsModel(m_HML, FoldersAndViewsModel::FOLDERS_AND_VIEWS);
    folderDlg.setModel(model, ui->editFoldersLine->text());
    if (QDialog::Accepted == folderDlg.exec()) {
        QString path = folderDlg.path();
        if (path.startsWith(QString(PATH_DELIMITER) + QString(ROOT_VIEW_NAME))) {
            ui->tabFoldersTree->setCurrentIndex(1);
            QModelIndex idx = m_views->indexFromPath(path);
            ui->treeView->setCurrentIndex(idx);
            onTreeViewChanged();
        } else {
            ui->tabFoldersTree->setCurrentIndex(0);;
            QModelIndex idx = m_folders->indexFromPath(path);
            ui->treeFolders->setCurrentIndex(idx);
            onTreeFolderChanged();
        }
    }
}

/******************************************************************/

void MainForm::on_btnToolbarAdd_clicked()
{
    on_actTestPing_triggered();
}

/******************************************************************/

void MainForm::on_btnToolbarEdit_clicked()
{
    QModelIndex index = ui->trvTestList->currentIndex();
    if (index.isValid()) {
        on_trvTestList_doubleClicked(index);
    }
}

/******************************************************************/

void MainForm::on_btnToolbarDel_clicked()
{
    on_actTestRemove_triggered();
}

/******************************************************************/

void MainForm::on_btnToolbarRefresh_clicked()
{
    on_actRefreshSelectedTests_triggered();
}

/******************************************************************/

void MainForm::on_btnToolbarReset_clicked()
{
    on_actResetSelectedTests_triggered();
}

/******************************************************************/

void MainForm::on_trvTestList_doubleClicked(const QModelIndex &index)
{
    TNode* item = m_model->itemFromIndex(m_filterModel->mapToSource(index));
    if (item->getType() == TNode::TEST) {
        hostMonDlg->init(qobject_cast<TTest*>(item));
    } else if (item->getType() == TNode::LINK) {
        TLink *link = qobject_cast<TLink*>(item);
        hostMonDlg->init(link->getTest());
    } else {
        return; //! TODO message "Please, select the test"
    }
    hostMonDlg->show();
}

/******************************************************************/

} // namespace SDPO
