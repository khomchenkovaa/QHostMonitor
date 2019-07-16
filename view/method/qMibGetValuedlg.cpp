#include "qMibGetValuedlg.h"
#include "ui_qMibGetValuedlg.h"

#include "netsnmpget.h"

using namespace SDPO;

/*****************************************************************/

QMibGetValueDlg::QMibGetValueDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMibGetValueDlg)
{
    ui->setupUi(this);
}

/*****************************************************************/

QMibGetValueDlg::~QMibGetValueDlg()
{
    delete ui;
}

/*****************************************************************/

void QMibGetValueDlg::setOid(const QString &oid)
{
    ui->cmbOid->setCurrentText(oid);
}

/*****************************************************************/

void SDPO::QMibGetValueDlg::on_btnSysInfo_clicked()
{

}

/*****************************************************************/

void SDPO::QMibGetValueDlg::on_btnGet_clicked()
{
    // get values
    QString version = "v2c"; // from profile
    QString community = "public"; // from profile
    int timeout = ui->spinTimeout->value(); // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();

    Q_UNUSED(timeout)

    NetSnmpGet snmpGet;
    snmpGet.setCommunity(community);
    snmpGet.setRetries(retries);
    snmpGet.setVersion(SnmpVersion::SNMPv2c);
    snmpGet.setPeername(host);
    SnmpValue value = snmpGet.get(oid);
    ui->textResult->appendPlainText(value.toString());
}

/*****************************************************************/

void SDPO::QMibGetValueDlg::on_btnGetRow_clicked()
{
    // get values
    QString version = "v2c"; // from profile
    QString community = "public"; // from profile
    int timeout = ui->spinTimeout->value(); // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();

    Q_UNUSED(timeout)

    NetSnmpGet snmpGet;
    snmpGet.setCommunity(community);
    snmpGet.setRetries(retries);
    snmpGet.setVersion(SnmpVersion::SNMPv2c);
    snmpGet.setPeername(host);
    QList<SDPO::SnmpValue> values = snmpGet.getRow(oid);
    foreach (const SnmpValue& val, values) {
        ui->textResult->appendPlainText(val.toString());
        ui->cmbOid->setCurrentText(val.nameAsStr());
    }

}

/*****************************************************************/

void SDPO::QMibGetValueDlg::on_btnGetNext_clicked()
{
    // get values
    QString version = "v2c"; // from profile
    QString community = "public"; // from profile
    int timeout = ui->spinTimeout->value(); // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();
    int cnt = ui->spinGetNext->value();

    Q_UNUSED(timeout)

    NetSnmpGet snmpGet;
    snmpGet.setCommunity(community);
    snmpGet.setRetries(retries);
    snmpGet.setVersion(SnmpVersion::SNMPv2c);
    snmpGet.setPeername(host);
    QList<SDPO::SnmpValue> values = snmpGet.getNext(oid, cnt);
    foreach (const SnmpValue& val, values) {
        ui->textResult->appendPlainText(val.toString());
        ui->cmbOid->setCurrentText(val.nameAsStr());
    }
}

/*****************************************************************/
