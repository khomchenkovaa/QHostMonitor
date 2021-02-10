#include "qMibGetValueDlg.h"
#include "ui_qMibGetValueDlg.h"

#include "qSnmpCredentialsDlg.h"

#include <QInputDialog>

#include <QDebug>

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
    } else if (cmd == CMD_SNMP_BULK_GET) {
        cmdBulkGet();
    } else if (cmd == CMD_SNMP_BULK_WALK) {
        cmdBulkWalk();
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
    QString sysDescr;
    QString upTimeStr;
    int     ipin = 0, ipout = 0, ipackets = 0, opackets = 0;

    MibOid objid_SysDescr        = MibOid::parse(".1.3.6.1.2.1.1.1.0");
    MibOid objid_SysUpTime       = MibOid::parse(".1.3.6.1.2.1.1.3.0");
    MibOid objid_ifOperStatus    = MibOid::parse(".1.3.6.1.2.1.2.2.1.8");
    MibOid objid_ifInUCastPkts   = MibOid::parse(".1.3.6.1.2.1.2.2.1.11");
    MibOid objid_ifInNUCastPkts  = MibOid::parse(".1.3.6.1.2.1.2.2.1.12");
    MibOid objid_ifOutUCastPkts  = MibOid::parse(".1.3.6.1.2.1.2.2.1.17");
    MibOid objid_ifOutNUCastPkts = MibOid::parse(".1.3.6.1.2.1.2.2.1.18");
    MibOid objid_ipInReceives    = MibOid::parse(".1.3.6.1.2.1.4.3.0");
    MibOid objid_ipOutRequests   = MibOid::parse(".1.3.6.1.2.1.4.10.0");

    // get values
    QString snmpProfile = ui->cmbProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    long timeout = ui->spinTimeout->value() * 1000000L; // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161

    Q_UNUSED(timeout)

    ss.setProfile(profile);
    ss.setTimeout(timeout);
    ss.setRetries(retries);
    ss.setDestHost(host);

    QList<MibOid> oids;
    oids.append(objid_SysDescr);      // System: get .1.3.6.1.2.1.1.1.0 (SNMPv2-MIB::sysDescr)
    oids.append(objid_SysUpTime);     // Uptime: get .1.3.6.1.2.1.1.3.0 (DISMAN-EVENT-MIB::sysUpTimeInstance)
    oids.append(objid_ipInReceives);
    oids.append(objid_ipOutRequests);

    SnmpValueList valueList = ss.get(oids);
    foreach(const SnmpValue& value, valueList) {
        if (objid_SysDescr.equals(value.name)) {
            sysDescr = value.val;
        }
        if (objid_SysUpTime.equals(value.name)) {
            u_long uptime = value.val.toULong();
            char buf[40];
            upTimeStr = uptime_string(uptime, buf);
        }
        if (objid_ipInReceives.equals(value.name)) {
            ipin = value.val.toInt();
        }
        if (objid_ipOutRequests.equals(value.name)) {
            ipout = value.val.toInt();
        }
    }

    ui->textResult->appendPlainText(QString("[%1]=>[%2] Up: %3").arg(ss.addrString(), sysDescr, upTimeStr));
    ui->textResult->appendPlainText(QString("In receives: %1").arg(ipin));
    ui->textResult->appendPlainText(QString("Out requests: %1").arg(ipout));

    oids.clear();
    oids.append(objid_ifOperStatus);
    oids.append(objid_ifInUCastPkts);
    oids.append(objid_ifInNUCastPkts);
    oids.append(objid_ifOutUCastPkts);
    oids.append(objid_ifOutNUCastPkts);

    SnmpValueTable interfaces;
    while(oids.size() == 5) {
        SnmpValueList row = ss.getNext(oids);
        if (row.size() < 5) break;
        oids.clear();
        if (row.at(0).name.isPartOfSubtree(objid_ifOperStatus)) {
            oids.append(row.at(0).name);
        }
        if (row.at(1).name.isPartOfSubtree(objid_ifInUCastPkts)) {
            oids.append(row.at(1).name);
        }
        if (row.at(2).name.isPartOfSubtree(objid_ifInNUCastPkts)) {
            oids.append(row.at(2).name);
        }
        if (row.at(3).name.isPartOfSubtree(objid_ifOutUCastPkts)) {
            oids.append(row.at(3).name);
        }
        if (row.at(4).name.isPartOfSubtree(objid_ifOutNUCastPkts)) {
            oids.append(row.at(4).name);
        }
        if (oids.size() == 5) {
            interfaces.append(row);
        }
    }

    QStringList ifStatus = QStringList() << "Unknown" << "Up" << "Down" << "Testing";

    int downInterfaces = 0;
    foreach(const SnmpValueList& row, interfaces) {
        int ifOperStatus = row.at(0).val.toInt();
        if (ifOperStatus != MIB_IFSTATUS_UP) downInterfaces++;
        int ifInUCastPkts = row.at(1).val.toInt();
        ipackets += ifInUCastPkts;
        int ifInNUCastPkts = row.at(2).val.toInt();
        ipackets += ifInNUCastPkts;
        int ifOutUCastPkts = row.at(3).val.toInt();
        opackets += ifOutUCastPkts;
        int ifOutNUCastPkts = row.at(4).val.toInt();
        opackets += ifOutNUCastPkts;
        QString rowStr = QString("%1 %2 %3 %4 %5").arg(ifStatus.at(ifOperStatus),
                                                       QString::number(ifInUCastPkts),
                                                       QString::number(ifInNUCastPkts),
                                                       QString::number(ifOutUCastPkts),
                                                       QString::number(ifOutNUCastPkts));
        ui->textResult->appendPlainText(rowStr);
    }
    QString ifSummary = QString("Interfaces: %1, Recv/Trans packets: %2/%3 | IP: %4/%5")
            .arg(QString::number(interfaces.size()), QString::number(ipackets), QString::number(opackets), QString::number(ipin), QString::number(ipout));
    ui->textResult->appendPlainText(ifSummary);
    if (downInterfaces > 0) {
        QString idDown = QString("%1 interface%2 down!\n")
                .arg(QString::number(downInterfaces), downInterfaces > 1 ? "s are" : " is");
        ui->textResult->appendPlainText(idDown);
    }
}

/*****************************************************************/

void QMibGetValueDlg::cmdGetValue()
{
    // get values
    QString snmpProfile = ui->cmbProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    long timeout = ui->spinTimeout->value() * 1000000L; // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();

    Q_UNUSED(timeout)

    ss.setProfile(profile);
    ss.setTimeout(timeout);
    ss.setRetries(retries);
    ss.setDestHost(host);

    SnmpValue value = ss.get(oid);
    ui->textResult->appendPlainText(QString("GET: %1").arg(ss.addrString()));
    ui->textResult->appendPlainText(NetSNMP::translateObj(oid));
    ui->textResult->appendPlainText(value.toString());
}

/*****************************************************************/

void QMibGetValueDlg::cmdBulkGet()
{
    // get values
    QString snmpProfile = ui->cmbProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    long timeout = ui->spinTimeout->value() * 1000000L; // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oidStr = ui->cmbOid->currentText();
    int maxRepetitions = ui->spinMaxRepetitions->value();

    Q_UNUSED(timeout)

    ss.setProfile(profile);
    ss.setTimeout(timeout);
    ss.setRetries(retries);
    ss.setDestHost(host);

    ui->textResult->appendPlainText(QString("SnmpGetBulk: %1").arg(NetSNMP::translateObj(oidStr)));

    MibOid anOid = MibOid::parse(oidStr);
    if (anOid.hasError()) {
        ui->textResult->appendPlainText(QString("%1: %2").arg(oidStr, anOid.errString()));
        return;
    }

    QList<MibOid> mibOids;
    mibOids.append(anOid);

    QList<SnmpValue> values = ss.bulkGet(mibOids, 0, maxRepetitions);
    foreach(const SnmpValue& value, values) {
        ui->textResult->appendPlainText(value.toString());
    }
}

/*****************************************************************/

void QMibGetValueDlg::cmdBulkWalk()
{
    // get values
    QString snmpProfile = ui->cmbProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    long timeout = ui->spinTimeout->value() * 1000000L; // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oidStr = ui->cmbOid->currentText();
    int maxRepetitions = ui->spinMaxRepetitions->value();

    Q_UNUSED(timeout)

    ss.setProfile(profile);
    ss.setTimeout(timeout);
    ss.setRetries(retries);
    ss.setDestHost(host);

    ui->textResult->appendPlainText(QString("SnmpBulkWalk: %1").arg(NetSNMP::translateObj(oidStr)));

    MibOid anOid = MibOid::parse(oidStr);
    if (anOid.hasError()) {
        ui->textResult->appendPlainText(QString("%1: %2").arg(oidStr, anOid.errString()));
        return;
    }

    QList<SnmpValue> values = ss.bulkWalk(anOid, 0, maxRepetitions);
    foreach(const SnmpValue& value, values) {
        ui->textResult->appendPlainText(value.toString());
    }
}

/*****************************************************************/

void QMibGetValueDlg::cmdGetRow()
{
    // get values
    QString snmpProfile = ui->cmbProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    long timeout = ui->spinTimeout->value() * 1000000L; // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();

    Q_UNUSED(timeout)

    ss.setProfile(profile);
    ss.setTimeout(timeout);
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
    long timeout = ui->spinTimeout->value() * 1000000L; // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHost->currentText(); // port = 161
    QString oidStr = ui->cmbOid->currentText();

    Q_UNUSED(timeout)

    ss.setProfile(profile);
    ss.setTimeout(timeout);
    ss.setRetries(retries);
    ss.setDestHost(host);

    ui->textResult->appendPlainText(QString("SnmpGetNext: %1").arg(NetSNMP::translateObj(oidStr)));

    MibOid anOid = MibOid::parse(oidStr);
    if (anOid.hasError()) {
        ui->textResult->appendPlainText(QString("%1: %2").arg(oidStr, anOid.errString()));
        return;
    }

    QList<MibOid> mibOids;
    mibOids.append(anOid);

    QList<SDPO::SnmpValue> values = ss.getNext(mibOids);
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
    long timeout = ui->spinTimeout->value() * 1000000L; // "2" / "1"
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
    ss.setTimeout(timeout);
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
    connect(ui->btnBulkGet, &QPushButton::clicked, this, &QMibGetValueDlg::cmdBulkGet);
    connect(ui->btnBulkWalk, &QPushButton::clicked, this, &QMibGetValueDlg::cmdBulkWalk);
    connect(ui->btnGetRow, &QPushButton::clicked, this, &QMibGetValueDlg::cmdGetRow);
    connect(ui->btnGetNext, &QPushButton::clicked, this, &QMibGetValueDlg::cmdGetNext);
    connect(ui->btnSet, &QPushButton::clicked, this, &QMibGetValueDlg::cmdSetValue);
    connect(ui->btnProfile, &QPushButton::clicked, this, &QMibGetValueDlg::openSnmpCredentialsDlg);
    connect(&ss, &NetSnmpSession::error, this, [this](const QString& msg){ ui->textResult->appendPlainText(msg); });
}

/*****************************************************************/
