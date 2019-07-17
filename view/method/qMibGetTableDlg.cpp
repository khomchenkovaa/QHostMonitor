#include "qMibGetTableDlg.h"
#include "ui_qMibGetTableDlg.h"

#include "netsnmptable.h"

using namespace SDPO;

/*****************************************************************/

QMibGetTableDlg::QMibGetTableDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMibGetTableDlg)
{
    ui->setupUi(this);
}

/*****************************************************************/

QMibGetTableDlg::~QMibGetTableDlg()
{
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
    SnmpProfile profile;
    profile.community = "public";
    int timeout = ui->spinTimeout->value(); // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();

    Q_UNUSED(timeout)
    ui->tableWidget->clear();

    NetSnmpTable snmpGet;
    snmpGet.setProfile(profile);
    snmpGet.setRetries(retries);
    snmpGet.setHost(host);
    QList<SDPO::SnmpColumn*> columns = snmpGet.readColumns(oid);
    if (columns.size()) {
        ui->tableWidget->setColumnCount(columns.size());
        for(int i=0; i<columns.size(); ++i) {
            QTableWidgetItem *item = new QTableWidgetItem(columns.at(i)->label);
            ui->tableWidget->setHorizontalHeaderItem(i, item);
        }
        QList<QList<SnmpValue>> values = snmpGet.getTableEntries();
        ui->tableWidget->setRowCount(values.size());
        for(int i=0; i<values.size(); ++i ) {
            QList<SnmpValue> row = values.at(i);
            for (int j=0; j<row.size(); ++j) {
                QTableWidgetItem *item = new QTableWidgetItem(row.at(j).val);
                ui->tableWidget->setItem(i,j,item);
            }
        }
    }


}

/*****************************************************************/
