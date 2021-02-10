#include "mibbrowserwidget.h"
#include "mibtreemodel.h"
#include "qMibGetValueDlg.h"
#include "qMibGetTableDlg.h"

#include <QtWidgets>

using namespace SDPO;

/******************************************************************/

MibBrowserWidget::MibBrowserWidget(QWidget *parent) :
    QWidget(parent),
    m_Model       (new MibTreeModel(this)),
    m_Proxy       (new MibTreeProxyModel(this)),
    treeMibs      (new QTreeView(this)),
    editMib       (new QLineEdit(this)),
    editOid       (new QLineEdit(this)),
    editType      (new QLineEdit(this)),
    editAccess    (new QLineEdit(this)),
    editStatus    (new QLineEdit(this)),
    editEnums     (new QLineEdit(this)),
    editIndexes   (new QLineEdit(this)),
    editAugments  (new QLineEdit(this)),
    editVarbinds  (new QLineEdit(this)),
    editHint      (new QLineEdit(this)),
    editUnits     (new QLineEdit(this)),
    txtDescription(new QPlainTextEdit(this)),
    editReference (new QLineEdit(this)),
    editDefault   (new QLineEdit(this))
{
    setupUI();
    init();
}

/******************************************************************/

QString MibBrowserWidget::getOid() const
{
    return editOid->text();
}

/******************************************************************/

void MibBrowserWidget::setOid(const QString &oid)
{
    QModelIndex idxSource = m_Model->indexFromOid(oid);
    if (idxSource.isValid()) {
        QModelIndex idxProxy = m_Proxy->mapFromSource(idxSource);
        treeMibs->setCurrentIndex(idxProxy);
        updateFields(idxProxy);
    }
}

/******************************************************************/

void MibBrowserWidget::findByName(const QString &name)
{
    QModelIndex idxSource = m_Model->findByName(name, m_Model->index(0,0));
    if (idxSource.isValid()) {
        QModelIndex idxProxy = m_Proxy->mapFromSource(idxSource);
        treeMibs->setCurrentIndex(idxProxy);
        updateFields(idxProxy);
    }
}

/******************************************************************/

void MibBrowserWidget::updateFields(const QModelIndex &proxyIndex)
{
    if (!proxyIndex.isValid()) return;

    QModelIndex index = m_Proxy->mapToSource(proxyIndex);
    MibNode item = index.internalPointer();

    editMib->setText(item.name());
    editOid->setText(item.objectID());
    editType->setText(item.syntax());
    editAccess->setText(item.accessName());
    editStatus->setText(item.statusName());
    editEnums->setText(item.enums());
    editIndexes->setText(item.indexes());
    editAugments->setText(item.augments());
    editVarbinds->setText(item.varbinds());
    editHint->setText(item.hint());
    editUnits->setText(item.units());
    txtDescription->setPlainText(item.description());
    editReference->setText(item.reference());
    editDefault->setText(item.defaultValue());

    disableEmpty();
}

/******************************************************************/

void MibBrowserWidget::updateActions(const QModelIndex &proxyIndex)
{
    if (!proxyIndex.isValid()) return;
    QModelIndex index = m_Proxy->mapToSource(proxyIndex);
    MibNode item = index.internalPointer();
    actChart->setDisabled(true);
    actGetValue->setDisabled(true);
    actGetRow->setDisabled(true);
    actGetTable->setDisabled(true);

    if (item.childList().isValid()) {
        actGetTable->setEnabled( item.childList().node->indexes );
    } else {
        actChart->setEnabled(true);
        if (item.access() == MibAccessReadOnly ||
            item.access() == MibAccessReadWrite) {
            actGetValue->setEnabled(true);
        }
        if (item.parent().parent().childList().node->indexes) {
            actGetRow->setEnabled(true);
        }
    }
}

/******************************************************************/

void MibBrowserWidget::getValueDld(const QString &cmd)
{
    QMibGetValueDlg dlg;
    dlg.setOid(getOid());
    dlg.runCmd(cmd);
    dlg.exec();
}

/******************************************************************/

void MibBrowserWidget::getTableDlg()
{
    QMibGetTableDlg dlg;
    dlg.setOid(getOid());
    dlg.exec();
}

/******************************************************************/

void MibBrowserWidget::findNameDlg()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Find Name"),tr("Name (e.g. sysUptime)"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        findByName(name);
    }
}

/******************************************************************/

void MibBrowserWidget::findOidDlg()
{
    bool ok;
    QString oid = QInputDialog::getText(this, tr("Find OID"),tr("OID (e.g. 1.3.6.1.2.1.1.1)"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        setOid(oid);
    }
}

/******************************************************************/

void MibBrowserWidget::contextMenu(QPoint pos)
{
    ctxMenu->popup(treeMibs->viewport()->mapToGlobal(pos));
}

/******************************************************************/

void MibBrowserWidget::setupUI()
{
    treeMibs->setHeaderHidden(true);
    treeMibs->setSortingEnabled(true);
    treeMibs->sortByColumn(0, Qt::AscendingOrder);
    treeMibs->setAlternatingRowColors(true);
    treeMibs->setContextMenuPolicy(Qt::CustomContextMenu);

    setupActions();

    editType->setReadOnly(true);
    editAccess->setReadOnly(true);
    editStatus->setReadOnly(true);
    txtDescription->setReadOnly(true);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->setHorizontalSpacing(10);
    formLayout->addRow(tr("MIB"), editMib);
    formLayout->addRow(tr("OID"), editOid);
    formLayout->addRow(tr("TYPE"), editType);
    formLayout->addRow(tr("ACCESS"), editAccess);
    formLayout->addRow(tr("STATUS"), editStatus);
    formLayout->addRow(tr("ENUMS"), editEnums);
    formLayout->addRow(tr("INDEXES"), editIndexes);
    formLayout->addRow(tr("AUGMENTS"), editAugments);
    formLayout->addRow(tr("VARBINDS"), editVarbinds);
    formLayout->addRow(tr("HINT"), editHint);
    formLayout->addRow(tr("UNITS"), editUnits);
    formLayout->addRow(txtDescription);
    formLayout->addRow(tr("REFERENCE"), editReference);
    formLayout->addRow(tr("DEFAULT VALUE"), editDefault);

    QWidget *formWidget = new QWidget(this);
    formWidget->setLayout(formLayout);

    // splitter
    QSplitter *splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(treeMibs);
    splitter->addWidget(formWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(splitter);
}

/******************************************************************/

void MibBrowserWidget::setupActions()
{
    actSysInfo  = new QAction(tr("System &info..."),this);
    actGetValue = new QAction(QIcon(":/img/test/snmp_get.png"),tr("Get Value..."),this);
    actGetNext  = new QAction(tr("Get Next..."),this);
    actGetRow   = new QAction(tr("Get Row..."),this);
    actGetTable = new QAction(QIcon(":/img/test/snmp_table.png"), tr("&Table..."),this);
    actChart    = new QAction(tr("C&hart"),this);
    actFindName = new QAction(QIcon(":/img/action/find.png"),tr("Find name..."),this);
    actFindNext = new QAction(QIcon(":/img/action/findNext.png"),tr("Search next"),this);
    actFindOid  = new QAction(QIcon(":/img/action/findBad.png"),tr("Find OID..."),this);

    actFindName->setShortcuts(QKeySequence::Find);
    actFindNext->setShortcuts(QKeySequence::FindNext);

    ctxMenu = new QMenu(this);
    ctxMenu->addAction(actGetValue);
    ctxMenu->addAction(actGetNext);
    ctxMenu->addSeparator();
    ctxMenu->addAction(actGetRow);
    ctxMenu->addAction(actGetTable);
    ctxMenu->addAction(actChart);
    ctxMenu->addSeparator();
    ctxMenu->addAction(actFindName);
    ctxMenu->addAction(actFindOid);

    connect(actSysInfo,  &QAction::triggered, this, [this](){
        getValueDld(CMD_SNMP_SYS_INFO);
    });
    connect(actGetValue, &QAction::triggered, this, [this](){
        getValueDld(CMD_SNMP_GET_VALUE);
    });
    connect(actGetNext,  &QAction::triggered, this, [this](){
        getValueDld(CMD_SNMP_GET_NEXT);
    });
    connect(actGetRow,  &QAction::triggered, this, [this](){
        getValueDld(CMD_SNMP_GET_ROW);
    });
    connect(actGetTable, &QAction::triggered, this, &MibBrowserWidget::getTableDlg);
    connect(actFindName, &QAction::triggered, this, &MibBrowserWidget::findNameDlg);
    connect(actFindOid,  &QAction::triggered, this, &MibBrowserWidget::findOidDlg);
}

/******************************************************************/

void MibBrowserWidget::init()
{
    m_Proxy->setSourceModel(m_Model);
    m_Model->setRoot(MibNode::getRoot());
    treeMibs->setModel(m_Proxy);

    QObject::connect(treeMibs, &QTreeView::clicked,
                     this, &MibBrowserWidget::updateFields);
    QObject::connect(treeMibs, &QTreeView::clicked,
                     this, &MibBrowserWidget::updateActions);
    QObject::connect(treeMibs, &QTreeView::customContextMenuRequested,
                     this, &MibBrowserWidget::contextMenu);

    disableEmpty();
}

/******************************************************************/

void MibBrowserWidget::disableEmpty()
{
    editType->setDisabled(editType->text().isEmpty());
    editAccess->setDisabled(editAccess->text().isEmpty());
    editStatus->setDisabled(editStatus->text().isEmpty());
    editEnums->setDisabled(editEnums->text().isEmpty());
    editIndexes->setDisabled(editIndexes->text().isEmpty());
    editAugments->setDisabled(editAugments->text().isEmpty());
    editVarbinds->setDisabled(editVarbinds->text().isEmpty());
    editHint->setDisabled(editHint->text().isEmpty());
    editUnits->setDisabled(editUnits->text().isEmpty());
    txtDescription->setDisabled(txtDescription->toPlainText().isEmpty());
    editReference->setDisabled(editReference->text().isEmpty());
    editDefault->setDisabled(editDefault->text().isEmpty());
}

/******************************************************************/
