#include "qMibBrowser.h"
#include "ui_qMibBrowser.h"
#include "qMibGetValuedlg.h"

#include <QtWidgets>

using namespace SDPO;

/******************************************************************/

MibBrowser::MibBrowser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MibBrowser),
    m_Model(new MibTreeModel),
    m_Proxy(new MibTreeProxyModel)
{
    ui->setupUi(this);
    SnmpMibTree *root = NetSNMP::instance()->allMibs();
    m_Proxy->setSourceModel(m_Model);
    m_Model->setRoot(root);
    ui->treeMibs->setModel(m_Proxy);
    ui->treeMibs->setHeaderHidden(true);
    ui->treeMibs->setSortingEnabled(true);
    ui->treeMibs->sortByColumn(0, Qt::AscendingOrder);
    QObject::connect(ui->treeMibs,
        SIGNAL(clicked(const QModelIndex&)),
        this, SLOT(updateFields(const QModelIndex&)));
}

/******************************************************************/

MibBrowser::~MibBrowser()
{
    delete ui;
}

/******************************************************************/

QString MibBrowser::getOid() const
{
    return ui->editOid->text();
}

/******************************************************************/

void MibBrowser::setOid(const QString oid)
{
//#define qqq_setoid
#ifdef qqq_setoid
    QStringList lstOid = oid.split(".",QString::SkipEmptyParts);
    QModelIndex idx = m_Proxy->index(0,0); // iso(1)
    lstOid.removeFirst();
    foreach(QString oidNum, lstOid ) {
        u_long subId = oidNum.toULong();
        int childCount = m_Proxy->rowCount(idx);
        if (!childCount) break;
        bool found = false;
        for (int i=0; i< childCount; i++) {
            QModelIndex tmpIdx = m_Proxy->index(i,0,idx);
            QModelIndex nodeIdx = m_Proxy->mapToSource(tmpIdx);
            SnmpMibTree *node = static_cast<SnmpMibTree *>(nodeIdx.internalPointer());
            if (subId == node->subid) {
                idx = tmpIdx;
                found = true;
                break;
            }
        }
        if (!found) break;
    }
    ui->treeMibs->setCurrentIndex(idx);
    updateFields(idx);
#endif
#define qqq_indexFromOid
#ifdef qqq_indexFromOid
    QModelIndex idxSource = m_Model->indexFromOid(oid);
    QModelIndex idxProxy = m_Proxy->mapFromSource(idxSource);
    ui->treeMibs->setCurrentIndex(idxProxy);
    updateFields(idxProxy);
#endif
}

/******************************************************************/

void MibBrowser::updateFields(const QModelIndex &proxyIndex)
{
    if (!proxyIndex.isValid()) return;
    ui->editSyntax->clear();
    ui->editAccess->clear();
    ui->editStatus->clear();
    ui->txtDescription->clear();

    QModelIndex index = m_Proxy->mapToSource(proxyIndex);
    SnmpMibTree *node = static_cast<SnmpMibTree *>(index.internalPointer());

    // build name
    QString name = QString("%1::%2").arg(NetSNMP::instance()->moduleName(node->modid)).arg(node->label);
    ui->editMib->setText(name);

    // build oid
    QString oid = QString(".%1").arg(node->subid);
    bool has_children = node->child_list != nullptr;
    SnmpMibTree *oidNode = node;
    while ((oidNode = oidNode->parent)) {
        oid = QString(".%1").arg(oidNode->subid) + oid;
    }
    if (!has_children) {
        oid += ".0";
    }
    ui->editOid->setText(oid);

    // build syntax
    QString syntax = NetSNMP::instance()->mibTypeName(static_cast<MibType>(node->type));
    if (node->ranges) {
        struct range_list *rp = node->ranges;
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
            case MibTypeUInreger:
                ranges.append( rp->low == rp->high ? QString::number(static_cast<unsigned>(rp->low)) :
                                                     QString("%1..%2").arg(static_cast<unsigned>(rp->low)).arg(static_cast<unsigned>(rp->high)) );
                break;
            }
            rp = rp->next;
        }
        syntax.append( QString(" (%1)").arg(ranges.join(" | ")) );
    }
    if (node->enums) {
        struct enum_list *ep = node->enums;
        QStringList enums;
        while (ep) {
            enums.append( QString("%1(%2)").arg(ep->label).arg(ep->value) );
            ep = ep->next;
        }
        syntax.append( QString(" {%1}").arg(enums.join(", ")) );
    }
    ui->editSyntax->setText(syntax);

    // build access
    QString access = NetSNMP::instance()->mibAccessName(static_cast<MibAccess>(node->access));
    ui->editAccess->setText(access);

    // build status
    if (node->status) {
        QString status = NetSNMP::instance()->mibStatusName(static_cast<MibStatus>(node->status));
        ui->editStatus->setText(status);
    }

    // build description
    QString description(node->description);
    QRegExp sp("\\s+");
    ui->txtDescription->setPlainText(description.replace(sp," "));
}

/******************************************************************/

void MibBrowser::on_btnGet_clicked()
{
    QMibGetValueDlg dlg;
    dlg.setOid(ui->editOid->text());
    dlg.exec();
}

/******************************************************************/

void MibBrowser::on_btnGetTable_clicked()
{

}

/******************************************************************/

void MibBrowser::on_btnFindName_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Find Name"),tr("Name (e.g. sysUptime)"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        QModelIndex idxSource = m_Model->findByName(name, m_Model->index(0,0));
        if (idxSource.isValid()) {
            QModelIndex idxProxy = m_Proxy->mapFromSource(idxSource);
            ui->treeMibs->setCurrentIndex(idxProxy);
            updateFields(idxProxy);
        }
    }
}

/******************************************************************/

void MibBrowser::on_btnFindOid_clicked()
{
    bool ok;
    QString oid = QInputDialog::getText(this, tr("Find OID"),tr("OID (e.g. 1.3.6.1.2.1.1.1)"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        setOid(oid);
    }
}

/******************************************************************/
