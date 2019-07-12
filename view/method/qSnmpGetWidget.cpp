#include "qSnmpGetWidget.h"
#include "ui_qSnmpGetWidget.h"
#include "method/tSnmpGet.h"
#include "qMibBrowser.h"

#include "nsnmpget.h"

#include <QProcess>
#include <QDebug>

namespace SDPO {

/******************************************************************/

SnmpGetWidget::SnmpGetWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::SnmpGetWidget),
    m_process(nullptr)
{
    ui->setupUi(this);
    connect(ui->cmbHostPort, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
    connect(ui->cmbOid, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/******************************************************************/

SnmpGetWidget::~SnmpGetWidget()
{
    delete ui;
}

/******************************************************************/

void SnmpGetWidget::init(TTestMethod *item)
{
    if (!item && (item->getTMethodID() != TMethodID::SNMP) ) {
        reset();
        return;
    }
    TSnmpGet *t = qobject_cast<TSnmpGet*>(item);
    ui->cmbHostPort->setCurrentText(t->getHost());
    ui->cmbSnmpProfile->setCurrentText(t->getCommunity());
    ui->spinTimeout->setValue(t->getTimeout());
    ui->spinRetries->setValue(t->getRetries());
    ui->cmbOid->setCurrentText(t->getMibOid());
    ui->cmbCriteria->setCurrentIndex(static_cast<int>(t->getCondition()));
    ui->cmbValue->setCurrentText(t->getValue());
}

/******************************************************************/

TTestMethod *SnmpGetWidget::save(TTestMethod *item)
{
    TSnmpGet *t;
    if (item && (item->getTMethodID() == TMethodID::SNMP)) {
        t = qobject_cast<TSnmpGet*>(item);
    } else {
        t = new TSnmpGet();
    }
    t->setHost(ui->cmbHostPort->currentText());
    t->setCommunity(ui->cmbSnmpProfile->currentText());
    t->setTimeout(ui->spinTimeout->value());
    t->setRetries(ui->spinRetries->value());
    t->setMibOid(ui->cmbOid->currentText());
    t->setCondition(static_cast<TSnmpGet::Condition>(ui->cmbCriteria->currentIndex()));
    t->setValue(ui->cmbValue->currentText());
    return t;
}

/******************************************************************/

void SnmpGetWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at(static_cast<int>(TMethodID::SNMP));
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbHostPort->setCurrentText("localhost");
    ui->cmbSnmpProfile->setCurrentText("public");
    ui->spinTimeout->setValue(2);
    ui->spinRetries->setValue(1);
    ui->cmbOid->setCurrentText(".1.3.6.1.2.1.1.3.0");
    ui->cmbCriteria->setCurrentIndex(0);
    ui->cmbValue->setCurrentText("");
}

/******************************************************************/

QStringList SnmpGetWidget::validate()
{
    QStringList errors;
    return errors;
}

/******************************************************************/

QString SnmpGetWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number(static_cast<int>(TMethodID::SNMP));
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::SNMP);
    case Macro::Host :
    case Macro::HostAddr : return ui->cmbHostPort->currentText();
    case Macro::MibOid :
    case Macro::MibName :
    case Macro::MibNameShort : return ui->cmbOid->currentText();
    default: return QString();
    }

}

/******************************************************************/

void SnmpGetWidget::on_btnSnmpCredentials_clicked()
{

}

/******************************************************************/

void SnmpGetWidget::on_btnMibBrowser_clicked()
{
    MibBrowser dlg;
    dlg.setOid(ui->cmbOid->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbOid->setCurrentText(dlg.getOid());
    }
}

/******************************************************************/

void SnmpGetWidget::on_btnGetValue_clicked()
{
#define IFD_use_lib_method
    ui->btnGetValue->setDisabled(true);

    // get values
    QString version = "v2c"; // from profile
    QString community = ui->cmbSnmpProfile->currentText(); // "public"
    int timeout = ui->spinTimeout->value(); // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHostPort->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();

    Q_UNUSED(timeout)

#ifdef IFD_use_lib_method
    NSnmpGet snmpGet;
    snmpGet.setCommunity(community);
    snmpGet.setRetries(retries);
    snmpGet.setVersion(SnmpVersion::SNMPv2c);
    snmpGet.setPeername(host);
    if (snmpGet.request(oid)) {
        ui->cmbValue->setCurrentText(snmpGet.response().first());
    }
#endif

#ifdef IFD_use_process_comand
    // build command
    QString cmd = "snmpget -m ALL ";
    cmd += QString("-%1 ").arg(version);
    cmd += QString("-c %1 ").arg(community);
    cmd += QString("-t %1 ").arg(timeout);
    cmd += QString("-r %1 ").arg(retries);
    cmd += host + " ";
    cmd += oid;

    // debug
    qDebug() << cmd;

    // execute command
    m_process = new QProcess();
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_process, SIGNAL(finished(int)), this, SLOT(onRunFinished(int)));
    connect(m_process, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    m_process->start(cmd);
    if (!m_process->waitForStarted()) {
        qDebug() << "SNMP Get process cannot start";
        return;
    }
    if (!m_process->waitForFinished()) {
        qDebug() << "SNMP Get process cannot finished";
        return;
    }
#endif

    ui->btnGetValue->setEnabled(true);
    ui->btnGetValue->setFocus();
}

/******************************************************************/

void SnmpGetWidget::onReadyRead()
{
    QString data;
    data.append(m_process->readAll());
    qDebug() << "SNMP Get data:" << data;
    int idx = data.indexOf(" = ");
    if (idx != -1) {
        data = data.mid(idx + 3);
        data = data.mid(data.indexOf(": ") + 2);
    }
    ui->cmbValue->setCurrentText(data);
}

/******************************************************************/

void SnmpGetWidget::onRunFinished(int exitCode)
{
    qDebug() << "SNMP Get process finished:" << exitCode;
    if( exitCode ) {
        ui->cmbValue->setCurrentText(m_process->errorString());
    }
    disconnect(m_process, SIGNAL(finished(int)), this, SLOT(onRunFinished(int)));
    disconnect(m_process, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    delete m_process;
    m_process=nullptr;
}

/******************************************************************/

} // namespace SDPO


