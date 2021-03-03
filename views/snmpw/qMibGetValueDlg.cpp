#include "qMibGetValueDlg.h"
#include "ui_qMibGetValueDlg.h"

#include "qSnmpCredentialsDlg.h"

#include <QInputDialog>
#include <QTextTable>

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

    printTitle("## SysInfo");
    printText(QString("[%1]=>[%2] Up: %3").arg(ss.addrString(), sysDescr, upTimeStr));
    printText(QString("In receives: %1").arg(ipin));
    printText(QString("Out requests: %1").arg(ipout));

    oids.clear();
    oids.append(objid_ifOperStatus);
    oids.append(objid_ifInUCastPkts);
    oids.append(objid_ifInNUCastPkts);
    oids.append(objid_ifOutUCastPkts);
    oids.append(objid_ifOutNUCastPkts);

    SnmpValueTable interfaces = ss.getTableRows(oids);

    QStringList ifStatus = QStringList() << "Unknown" << "Up" << "Down" << "Testing";

    QTextTableFormat tableFormat;
    tableFormat.setHeaderRowCount(1);
    QTextTable *ifTable = ui->textResult->textCursor().insertTable(interfaces.size() + 1, 5, tableFormat);
    for(int i=0; i < oids.size(); ++i) {
        ifTable->cellAt(0,i).firstCursorPosition().insertText(NetSNMP::translateObj(oids.at(i).toString()));
    }

    int downInterfaces = 0;
    for(int i=0; i < interfaces.size(); ++i) {
        const SnmpValueList& row = interfaces.at(i);
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
        ifTable->cellAt(i+1,0).firstCursorPosition().insertText(ifStatus.at(ifOperStatus));
        ifTable->cellAt(i+1,1).firstCursorPosition().insertText(QString::number(ifInUCastPkts));
        ifTable->cellAt(i+1,2).firstCursorPosition().insertText(QString::number(ifInNUCastPkts));
        ifTable->cellAt(i+1,3).firstCursorPosition().insertText(QString::number(ifOutUCastPkts));
        ifTable->cellAt(i+1,4).firstCursorPosition().insertText(QString::number(ifOutNUCastPkts));
    }
    QString ifSummary = QString("Interfaces: %1, Recv/Trans packets: %2/%3 | IP: %4/%5")
            .arg(QString::number(interfaces.size()), QString::number(ipackets), QString::number(opackets), QString::number(ipin), QString::number(ipout));
    printText(ifSummary);
    if (downInterfaces > 0) {
        QString idDown = QString("%1 interface%2 down!")
                .arg(QString::number(downInterfaces), downInterfaces > 1 ? "s are" : " is");
        printText(idDown);
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
    printTitle(QString("## SnmpGet: %1").arg(NetSNMP::translateObj(oid)));
    printText(value.toString());
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

    printTitle("SnmpGetBulk",oidStr);

    MibOid anOid = MibOid::parse(oidStr);
    if (anOid.hasError()) {
        printError(QString("%1: %2").arg(oidStr, anOid.errString()));
        return;
    }

    QList<MibOid> mibOids;
    mibOids.append(anOid);

    QList<SnmpValue> values = ss.bulkGet(mibOids, 0, maxRepetitions);
    foreach(const SnmpValue& value, values) {
        printText(value.toString());
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

    printTitle("SnmpBulkWalk", oidStr);

    MibOid anOid = MibOid::parse(oidStr);
    if (anOid.hasError()) {
        printError(QString("%1: %2").arg(oidStr, anOid.errString()));
        return;
    }

    QList<SnmpValue> values = ss.bulkWalk(anOid, 0, maxRepetitions);
    foreach(const SnmpValue& value, values) {
        printText(value.toString());
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
    QString oidStr = ui->cmbOid->currentText();

    Q_UNUSED(timeout)

    ss.setProfile(profile);
    ss.setTimeout(timeout);
    ss.setRetries(retries);
    ss.setDestHost(host);

    printTitle("SnmpGetRow", oidStr);

    QList<SDPO::SnmpValue> values = ss.getRow(oidStr);
    foreach (const SnmpValue& value, values) {
        printText(value.toString());
        ui->cmbOid->setCurrentText(value.nameAsStr());
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

    printTitle("SnmpGetNext", oidStr);

    MibOid anOid = MibOid::parse(oidStr);
    if (anOid.hasError()) {
        printError(QString("%1: %2").arg(oidStr, anOid.errString()));
        return;
    }

    QList<MibOid> mibOids;
    mibOids.append(anOid);

    QList<SDPO::SnmpValue> values = ss.getNext(mibOids);
    foreach (const SnmpValue& value, values) {
        printText(value.toString());
        ui->cmbOid->setCurrentText(value.nameAsStr());
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

    printTitle(QString("## SnmpSet: %1 = %2").arg(NetSNMP::translateObj(oid), newValue));

    ss.setProfile(profile);
    ss.setTimeout(timeout);
    ss.setRetries(retries);
    ss.setDestHost(host);
    SnmpValue value = ss.set(oid, newValue);
    printText(value.toString());
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
    connect(&ss, &NetSnmpSession::error, this, [this](const QString& msg){ printError(msg); });
}

/*****************************************************************/

void QMibGetValueDlg::printTitle(const QString &cmd, const QString &oidStr)
{
    printTitle(QString("## %1: %2").arg(cmd, NetSNMP::translateObj(oidStr)));
}

/*****************************************************************/

void QMibGetValueDlg::printTitle(const QString &title)
{
    QTextBlockFormat format;
    format.setNonBreakableLines(true);
    QTextCursor cursor(ui->textResult->textCursor());
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock(format);
    cursor.insertHtml(QString("<b>%1</b> ").arg(title));
}

/*****************************************************************/

void QMibGetValueDlg::printError(const QString &error)
{
    QTextBlockFormat format;
    format.setNonBreakableLines(false);
    QTextCursor cursor(ui->textResult->textCursor());
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock(format);
    cursor.insertHtml(QString("<font color='red'>%1</font> ").arg(error));
}

/*****************************************************************/

void QMibGetValueDlg::printText(const QString &text)
{
    QTextBlockFormat format;
    format.setNonBreakableLines(true);
    QTextCursor cursor(ui->textResult->textCursor());
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock(format);
    cursor.insertText(text);
}

/*****************************************************************/
