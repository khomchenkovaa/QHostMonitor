#include "qMibGetValuedlg.h"
#include "ui_qMibGetValuedlg.h"

#include "nsnmpget.h"

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

    NSnmpGet snmpGet;
    snmpGet.setCommunity(community);
    snmpGet.setRetries(retries);
    snmpGet.setVersion(SnmpVersion::SNMPv2c);
    snmpGet.setPeername(host);
    if (snmpGet.request(oid)) {
        ui->textResult->appendPlainText(snmpGet.response().first());
    }
}

/*****************************************************************/

void SDPO::QMibGetValueDlg::on_btnGetRow_clicked()
{

}

/*****************************************************************/

void SDPO::QMibGetValueDlg::on_btnGetNext_clicked()
{

}

/*****************************************************************/
