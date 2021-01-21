#include "qMibGetValueDlg.h"
#include "ui_qMibGetValueDlg.h"

#include "qSnmpCredentialsDlg.h"

#include <QInputDialog>

using namespace SDPO;

/*****************************************************************/

QMibGetValueDlg::QMibGetValueDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMibGetValueDlg)
{
    setupUI();
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

void QMibGetValueDlg::runCmd(const QString &cmd)
{
    if (cmd == CMD_SNMP_SYS_INFO) {
        cmdSysInfo();
    } else if (cmd == CMD_SNMP_GET_VALUE) {
        cmdGetValue();
    } else if (cmd == CMD_SNMP_GET_ROW) {
        cmdGetRow();
    } else if (cmd == CMD_SNMP_GET_NEXT) {
        cmdGetNext();
    } else if (cmd == CMD_SNMP_SET_VALUE) {
        cmdSetValue();
    }
}

/*****************************************************************/

void QMibGetValueDlg::cmdSysInfo()
{
    QString objid_SysDescr        = ".1.3.6.1.2.1.1.1.0";
    QString objid_SysUpTime       = ".1.3.6.1.2.1.1.3.0";
    QString objid_ifOperStatus    = ".1.3.6.1.2.1.2.2.1.8";
    QString objid_ifInUCastPkts   = ".1.3.6.1.2.1.2.2.1.11";
    QString objid_ifInNUCastPkts  = ".1.3.6.1.2.1.2.2.1.12";
    QString objid_ifOutUCastPkts  = ".1.3.6.1.2.1.2.2.1.17";
    QString objid_ifOutNUCastPkts = ".1.3.6.1.2.1.2.2.1.18";
    QString objid_ipInReceives    = ".1.3.6.1.2.1.4.3.0";
    QString objid_ipOutRequests   = ".1.3.6.1.2.1.4.10.0";

    // get values
    QString snmpProfile = ui->cmbProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    int timeout = ui->spinTimeout->value(); // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161

    Q_UNUSED(timeout)

    ss.setProfile(profile);
    ss.setRetries(retries);
    ss.setDestHost(host);

    ui->textResult->appendPlainText("\n" + host);
    // System: get .1.3.6.1.2.1.1.1.0 (SNMPv2-MIB::sysDescr)
    SnmpValue value = ss.get(objid_SysDescr);
    ui->textResult->appendPlainText("System:\t" + value.val);
    // Uptime: get .1.3.6.1.2.1.1.3.0 (DISMAN-EVENT-MIB::sysUpTimeInstance)
    value = ss.get(objid_SysUpTime);
    ui->textResult->appendPlainText("Uptime:\t" + value.val); // to hh:mm:ss
    // Interfaces: get .1.3.6.1.2.1.2.1.0 (IF-MIB::ifNumber)
    value = ss.get(".1.3.6.1.2.1.2.1.0");
    ui->textResult->appendPlainText(value.val + " interfaces");

    // Int row: getRow .1.3.6.1.2.1.2.2.1.1 (IF-MIB::ifIndex)
    QList<SDPO::SnmpValue> rowVals = ss.getRow(".1.3.6.1.2.1.2.2.1.1");
    // Int name: getRow .1.3.6.1.2.1.2.2.1.2 (IF-MIB::ifDescr)
    QList<SDPO::SnmpValue> descrVals = ss.getRow(".1.3.6.1.2.1.2.2.1.2");
    // IN: getRow .1.3.6.1.2.1.2.2.1.10 (IF-MIB::ifInOctets)
    QList<SDPO::SnmpValue> inVals = ss.getRow(".1.3.6.1.2.1.2.2.1.10");
    // OUT: getRow .1.3.6.1.2.1.2.2.1.16 (IF-MIB::ifOutOctets)
    QList<SDPO::SnmpValue> outVals = ss.getRow(".1.3.6.1.2.1.2.2.1.16");
    for (int i=0; i<rowVals.size(); ++i) {
        QString rowVal   = i < rowVals.size() ? rowVals.at(i).val : QString();
        QString descrVal = i < descrVals.size() ? descrVals.at(i).val : QString();
        QString inVal    = i < inVals.size() ? inVals.at(i).val : QString(); // TODO convert to Kb
        QString outVal   = i < outVals.size() ? outVals.at(i).val : QString(); // TODO convert to Kb
        QString text = QString("%1\t%2\t%3 in %4 out").arg(rowVal, descrVal, inVal, outVal);
        ui->textResult->appendPlainText(text);
    }
}

/*****************************************************************/

void QMibGetValueDlg::cmdGetValue()
{
    // get values
    QString snmpProfile = ui->cmbProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    int timeout = ui->spinTimeout->value(); // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();

    Q_UNUSED(timeout)

    ss.setProfile(profile);
    ss.setRetries(retries);
    ss.setDestHost(host);

    SnmpValue value = ss.get(oid);
    ui->textResult->appendPlainText(NetSNMP::translateObj(oid));
    ui->textResult->appendPlainText(value.toString());
}

/*****************************************************************/

void QMibGetValueDlg::cmdGetRow()
{
    // get values
    QString snmpProfile = ui->cmbProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    int timeout = ui->spinTimeout->value(); // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();

    Q_UNUSED(timeout)

    ss.setProfile(profile);
    ss.setRetries(retries);
    ss.setDestHost(host);
    QList<SDPO::SnmpValue> values = ss.getRow(oid);
    foreach (const SnmpValue& val, values) {
        ui->textResult->appendPlainText(val.toString());
        ui->cmbOid->setCurrentText(val.nameAsStr());
    }

}

/*****************************************************************/

void QMibGetValueDlg::cmdGetNext()
{
    // get values
    QString snmpProfile = ui->cmbProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    int timeout = ui->spinTimeout->value(); // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();
    int cnt = ui->spinGetNext->value();

    Q_UNUSED(timeout)

    ss.setProfile(profile);
    ss.setRetries(retries);
    ss.setDestHost(host);

    QList<SDPO::SnmpValue> values = ss.getNext(oid, cnt);
    foreach (const SnmpValue& val, values) {
        ui->textResult->appendPlainText(val.toString());
        ui->cmbOid->setCurrentText(val.nameAsStr());
    }
}

/*****************************************************************/

void QMibGetValueDlg::cmdSetValue()
{
    // get values
    QString snmpProfile = ui->cmbProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    int timeout = ui->spinTimeout->value(); // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();
    Q_UNUSED(timeout)

    QString newValue = QInputDialog::getText(this,"SNMP Set","Set new value");

    if (newValue.isEmpty()) {
        return;
    }

    ui->textResult->appendPlainText("set " + oid + " = " + newValue);

    ss.setProfile(profile);
    ss.setRetries(retries);
    ss.setDestHost(host);
    SnmpValue value = ss.set(oid, newValue);
    ui->textResult->appendPlainText(value.toString());
}

/*****************************************************************/

void QMibGetValueDlg::openSnmpCredentialsDlg()
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

void QMibGetValueDlg::setupUI()
{
    ui->setupUi(this);
    ui->cmbProfile->clear();
    ui->cmbProfile->addItems(SnmpProfile::names());
    ui->cmbProfile->setCurrentIndex(SnmpProfile::defaultIdx());
    connect(ui->btnSysInfo, &QPushButton::clicked, this, &QMibGetValueDlg::cmdSysInfo);
    connect(ui->btnGet, &QPushButton::clicked, this, &QMibGetValueDlg::cmdGetValue);
    connect(ui->btnGetRow, &QPushButton::clicked, this, &QMibGetValueDlg::cmdGetRow);
    connect(ui->btnGetNext, &QPushButton::clicked, this, &QMibGetValueDlg::cmdGetNext);
    connect(ui->btnSet, &QPushButton::clicked, this, &QMibGetValueDlg::cmdSetValue);
    connect(ui->btnProfile, &QPushButton::clicked, this, &QMibGetValueDlg::openSnmpCredentialsDlg);
    connect(&ss, &NetSnmpSession::error, this, [this](const QString& msg){ ui->textResult->appendPlainText(msg); });
}

/*****************************************************************/
