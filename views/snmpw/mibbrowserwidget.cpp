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
    editSyntax    (new QLineEdit(this)),
    editAccess    (new QLineEdit(this)),
    editStatus    (new QLineEdit(this)),
    txtDescription(new QPlainTextEdit(this))
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

    editSyntax->clear();
    editAccess->clear();
    editStatus->clear();
    txtDescription->clear();

    QModelIndex index = m_Proxy->mapToSource(proxyIndex);
    MibTree *node = static_cast<MibTree *>(index.internalPointer());

    // build name
    QString name = QString("%1::%2").arg(NetSNMP::instance()->moduleName(node->modid)).arg(node->label);
    editMib->setText(name);

    // build oid
    QString oid = QString(".%1").arg(node->subid);
    bool has_children = node->child_list != nullptr;
    MibTree *oidNode = node;
    while ((oidNode = oidNode->parent)) {
        oid = QString(".%1").arg(oidNode->subid) + oid;
    }
    if (!has_children) {
        oid += ".0";
    }
    editOid->setText(oid);

    // build syntax
    QString syntax = NetSNMP::mibTypeName(node->type);
    if (node->ranges) {
        range_list *rp = node->ranges;
        QStringList ranges;
        while(rp) {
            switch (node->type) {
            case MibTypeInteger:
            case MibTypeInteger32:
                ranges.append( rp->low == rp->high ? QString::number(rp->low) :
                                                  QString("%1..%2").arg(rp->low).arg(rp->high) );
                break;
            case MibTypeUnsigned32:
            case MibTypeOctetStr:
            case MibTypeGauge:
            case MibTypeUInteger:
                ranges.append( rp->low == rp->high ? QString::number(static_cast<unsigned>(rp->low)) :
                                                  QString("%1..%2").arg(static_cast<unsigned>(rp->low)).arg(static_cast<unsigned>(rp->high)) );
                break;
            }
            rp = rp->next;
        }
        syntax.append( QString(" (%1)").arg(ranges.join(" | ")) );
    }
    if (node->enums) {
        enum_list *ep = node->enums;
        QStringList enums;
        while (ep) {
            enums.append( QString("%1(%2)").arg(ep->label).arg(ep->value) );
            ep = ep->next;
        }
        syntax.append( QString(" {%1}").arg(enums.join(", ")) );
    }
    editSyntax->setText(syntax);

    // build access
    QString access = NetSNMP::mibAccessName(node->access);
    editAccess->setText(access);

    // build status
    if (node->status) {
        QString status = NetSNMP::mibStatusName(node->status);
        editStatus->setText(status);
    }

    // build description
    QString description(node->description);
    QRegExp sp("\\s+");
    txtDescription->setPlainText(description.replace(sp," "));
}

/******************************************************************/

void MibBrowserWidget::updateActions(const QModelIndex &proxyIndex)
{
    if (!proxyIndex.isValid()) return;
    QModelIndex index = m_Proxy->mapToSource(proxyIndex);
    MibTree *node = static_cast<MibTree *>(index.internalPointer());
    actChart->setDisabled(true);
    actGetValue->setDisabled(true);
    actGetRow->setDisabled(true);
    actGetTable->setDisabled(true);

    if (node->child_list) {
        actGetTable->setEnabled( node->child_list->indexes );
    } else {
        actChart->setEnabled(true);
        if (node->access == MibAccessReadOnly ||
            node->access == MibAccessReadWrite) {
            actGetValue->setEnabled(true);
        }
        if (node->parent->parent->child_list->indexes) {
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
    treeMibs->setContextMenuPolicy(Qt::CustomContextMenu);
    setupActions();

    editSyntax->setReadOnly(true);
    editAccess->setReadOnly(true);
    editStatus->setReadOnly(true);
    txtDescription->setReadOnly(true);

    QLabel *lblMIB    = new QLabel(tr("MIB"), this);
    QLabel *lblOID    = new QLabel(tr("OID"), this);
    QLabel *lblSyntax = new QLabel(tr("SINTAX"), this);
    QLabel *lblAccess = new QLabel(tr("ACCESS"), this);
    QLabel *lblStatus = new QLabel(tr("STATUS"), this);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(10);
    gridLayout->addWidget(lblMIB, 0, 0, 1, 1);
    gridLayout->addWidget(lblOID, 1, 0, 1, 1);
    gridLayout->addWidget(lblSyntax, 2, 0, 1, 1);
    gridLayout->addWidget(lblAccess, 3, 0, 1, 1);
    gridLayout->addWidget(lblStatus, 4, 0, 1, 1);
    gridLayout->addWidget(editMib, 0, 1, 1, 3);
    gridLayout->addWidget(editOid, 1, 1, 1, 3);
    gridLayout->addWidget(editSyntax, 2, 1, 1, 1);
    gridLayout->addWidget(editAccess, 3, 1, 1, 1);
    gridLayout->addWidget(editStatus, 4, 1, 1, 1);
    gridLayout->addWidget(txtDescription, 2, 2, 3, 2);
    gridLayout->setColumnStretch(1, 1);
    gridLayout->setColumnStretch(2, 3);

#ifndef QT_NO_SHORTCUT
    lblMIB->setBuddy(editMib);
    lblOID->setBuddy(editOid);
    lblSyntax->setBuddy(editSyntax);
    lblAccess->setBuddy(editAccess);
    lblStatus->setBuddy(editStatus);
#endif // QT_NO_SHORTCUT

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(treeMibs);
    mainLayout->addLayout(gridLayout);
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
    MibTree *root = NetSNMP::instance()->allMibs();
    m_Proxy->setSourceModel(m_Model);
    m_Model->setRoot(root);
    treeMibs->setModel(m_Proxy);
    QObject::connect(treeMibs, &QTreeView::clicked,
                     this, &MibBrowserWidget::updateFields);
    QObject::connect(treeMibs, &QTreeView::clicked,
                     this, &MibBrowserWidget::updateActions);
    QObject::connect(treeMibs, &QTreeView::customContextMenuRequested,
                     this, &MibBrowserWidget::contextMenu);
}

/******************************************************************/
