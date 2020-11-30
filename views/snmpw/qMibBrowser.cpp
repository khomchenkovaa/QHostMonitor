#include "qMibBrowser.h"
#include "ui_qMibBrowser.h"
#include "qMibGetValueDlg.h"
#include "qMibGetTableDlg.h"

#include <QtWidgets>

using namespace SDPO;

/******************************************************************/

MibBrowser::MibBrowser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MibBrowser)
{
    ui->setupUi(this);
}

/******************************************************************/

MibBrowser::~MibBrowser()
{
    delete ui;
}

/******************************************************************/

QString MibBrowser::getOid() const
{
    return ui->MibBrowserWidget->getOid();
}

/******************************************************************/

void MibBrowser::setOid(const QString oid)
{
    ui->MibBrowserWidget->setOid(oid);
}

/******************************************************************/

void MibBrowser::on_btnGet_clicked()
{
    QMibGetValueDlg dlg;
    dlg.setOid(ui->MibBrowserWidget->getOid());
    dlg.exec();
}

/******************************************************************/

void MibBrowser::on_btnGetTable_clicked()
{
    QMibGetTableDlg dlg;
    dlg.setOid(ui->MibBrowserWidget->getOid());
    dlg.exec();
}

/******************************************************************/

void MibBrowser::on_btnFindName_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Find Name"),tr("Name (e.g. sysUptime)"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        ui->MibBrowserWidget->findByName(name);
    }
}

/******************************************************************/

void MibBrowser::on_btnFindOid_clicked()
{
    bool ok;
    QString oid = QInputDialog::getText(this, tr("Find OID"),tr("OID (e.g. 1.3.6.1.2.1.1.1)"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        ui->MibBrowserWidget->setOid(oid);
    }
}

/******************************************************************/
