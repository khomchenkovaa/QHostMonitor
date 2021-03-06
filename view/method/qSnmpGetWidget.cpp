#include "qSnmpGetWidget.h"
#include "ui_qSnmpGetWidget.h"
#include "method/tSnmpGet.h"
#include "mibbrowserdlg.h"
#include "qSnmpCredentialsDlg.h"
#include "gData.h"

#include "netsnmpsession.h"

#include <QDebug>

namespace SDPO {

/******************************************************************/

SnmpGetWidget::SnmpGetWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::SnmpGetWidget)
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

void SnmpGetWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::SNMP) ) {
        reset();
        return;
    }
    TSnmpGet *t = qobject_cast<TSnmpGet*>(item);
    ui->cmbHostPort->setCurrentText(t->getHost());
    ui->cmbSnmpProfile->setCurrentText(t->getSnmpProfile());
    ui->spinTimeout->setValue(t->getTimeout());
    ui->spinRetries->setValue(t->getRetries());
    ui->cmbOid->setCurrentText(t->getMibOid());
    ui->cmbCriteria->setCurrentIndex(static_cast<int>(t->getCondition()));
    ui->cmbValue->setCurrentText(t->getValue());
}

/******************************************************************/

TestMethod *SnmpGetWidget::save(TestMethod *item)
{
    TSnmpGet *t;
    if (item && (item->getTMethodID() == TMethodID::SNMP)) {
        t = qobject_cast<TSnmpGet*>(item);
    } else {
        t = new TSnmpGet();
    }
    t->setHost(ui->cmbHostPort->currentText());
    t->setSnmpProfile(ui->cmbSnmpProfile->currentText());
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
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::SNMP);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbSnmpProfile->clear();
    ui->cmbSnmpProfile->addItems(SnmpProfile::names());
    ui->cmbHostPort->setCurrentText("localhost");
    ui->cmbSnmpProfile->setCurrentIndex(0);
    ui->spinTimeout->setValue(2);
    ui->spinRetries->setValue(1);
    ui->cmbOid->setCurrentText(".1.3.6.1.2.1.1.1.0");
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
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number(static_cast<int>(TMethodID::SNMP));
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::SNMP);
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
    QSnmpCredentialsDlg dlg;
    dlg.init(ui->cmbSnmpProfile->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbSnmpProfile->clear();
        ui->cmbSnmpProfile->addItems(SnmpProfile::names());
        ui->cmbSnmpProfile->setCurrentIndex(dlg.getSelected());
    }
}

/******************************************************************/

void SnmpGetWidget::on_btnMibBrowser_clicked()
{
    MibBrowserDlg dlg;
    dlg.setOid(ui->cmbOid->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbOid->setCurrentText(dlg.getOid());
    }
}

/******************************************************************/

void SnmpGetWidget::on_btnGetValue_clicked()
{
    ui->btnGetValue->setDisabled(true);

    // get values
    QString snmpProfile = ui->cmbSnmpProfile->currentText();
    SnmpProfile profile = SnmpProfile::findByName(snmpProfile);
    int timeout = ui->spinTimeout->value(); // "2" / "1"
    int retries = ui->spinRetries->value(); // "1" / "5"
    QString host = ui->cmbHostPort->currentText(); // port = 161
    QString oid = ui->cmbOid->currentText();

    Q_UNUSED(timeout)

    NetSnmpSession ss;
    ss.setProfile(profile);
    ss.setRetries(retries);
    ss.setDestHost(host);
    SnmpValue value = ss.get(oid);
    ui->cmbValue->setCurrentText(value.val);

    ui->btnGetValue->setEnabled(true);
    ui->btnGetValue->setFocus();
}

/******************************************************************/

} // namespace SDPO


