#include "qMibGetTableDlg.h"
#include "ui_qMibGetTableDlg.h"

#include "snmp.h"
#include "netsnmpsession.h"
#include "snmptablemodel.h"
#include "qSnmpCredentialsDlg.h"

using namespace SDPO;

/*****************************************************************/

QMibGetTableDlg::QMibGetTableDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMibGetTableDlg),
    model(new SnmpTableModel)
{
    ui->setupUi(this);
    ui->cmbProfile->clear();
    ui->cmbProfile->addItems(SnmpProfile::names());
    ui->tableView->setModel(model);
    ui->lblError->clear();
    ui->lblError->setHidden(true);
}

/*****************************************************************/

QMibGetTableDlg::~QMibGetTableDlg()
{
    model->deleteLater();
    delete ui;
}

/*****************************************************************/

void QMibGetTableDlg::setOid(const QString &oid)
{
    ui->cmbOid->setCurrentText(oid);
}

/*****************************************************************/

void SDPO::QMibGetTableDlg::on_btnGet_clicked()
{
    // get values
    QString snmpProfile = ui->cmbProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    long timeout = ui->spinTimeout->value() * 1000000L; // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();

    model->clear();
    ui->lblError->clear();
    ui->lblError->setHidden(true);

    NetSnmpSession ss;
    ss.setProfile(profile);
    ss.setTimeout(timeout);
    ss.setRetries(retries);
    ss.setDestHost(host);
    connect(&ss, &NetSnmpSession::error, this, [this](const QString& msg){
        ui->lblError->setHidden(false);
        ui->lblError->setText(msg);
    });

    QList<MibNode> columns = ss.readColumns(oid);
    model->setHeaders(columns);
    if (model->columnCount()) {
        QList<MibOid> columnOids;
        foreach(const MibNode& mNode, columns) {
            columnOids.append(mNode.mibOid());
        }
        model->setValues(ss.getTableRows(columnOids));
    }
}

/*****************************************************************/

void SDPO::QMibGetTableDlg::on_btnProfile_clicked()
{
    QSnmpCredentialsDlg dlg;
    dlg.init(ui->cmbProfile->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbProfile->clear();
        ui->cmbProfile->addItems(SnmpProfile::names());
        ui->cmbProfile->setCurrentIndex(dlg.getSelected());
    }
}

/*****************************************************************/
