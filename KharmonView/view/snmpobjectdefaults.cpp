#include "snmpobjectdefaults.h"

#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

using namespace KharmonView;

/*************************************************************/

SnmpObjectDefaults::SnmpObjectDefaults(QWidget *parent)
    : QDialog(parent)
    , uiSystem (new QLineEdit(this))
    , uiSubsystem (new QLineEdit(this))
    , uiDlgTimeout (new QSpinBox(this))
    , uiHost (new QLineEdit(this))
    , uiPort (new QLineEdit(this))
    , uiVersion (new QComboBox(this))
    , uiCommunity (new QLineEdit(this))
    , uiTimeout (new QLineEdit(this))
    , uiRetries (new QLineEdit(this))
{
    setupUI();
    init();
}

/*************************************************************/

void SnmpObjectDefaults::onAccepted()
{
    QString err;
    if (!validate(&err)) {
        QMessageBox::critical(this, "Ошибка создания записи", err);
        return;
    }
    save();
    accept();
}

/*************************************************************/

void SnmpObjectDefaults::setupUI()
{
    QFont font;
    font.setPointSize(9);
    setFont(font);
    resize(600, 500);
    setWindowTitle(tr("Edit Defaults"));

    uiDlgTimeout->setRange(1, 60);

    uiHost->setPlaceholderText(QString("default: %1").arg(DFLT_HOST));
    uiPort->setPlaceholderText(QString("default: %1").arg(DFLT_SNMP_PORT));
    uiCommunity->setPlaceholderText(QString("default: %1").arg(DFLT_SNMP_COMMUNITY));
    uiTimeout->setPlaceholderText(QString("default: %1").arg(DFLT_SNMP_TIMEOUT));
    uiRetries->setPlaceholderText(QString("default: %1").arg(DFLT_SNMP_RETRIES));

    uiVersion->addItem(tr("default"), SDPO::SNMPvDefault);
    uiVersion->addItem(tr("version 1"), SDPO::SNMPv1);
    uiVersion->addItem(tr("version 2c"), SDPO::SNMPv2c);
    uiVersion->addItem(tr("version 3"), SDPO::SNMPv3);

    QDialogButtonBox *uiButtonBox = new QDialogButtonBox(this);
    uiButtonBox->setOrientation(Qt::Vertical);
    uiButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(tr("System"), uiSystem);
    formLayout->addRow(tr("Subystem"), uiSubsystem);
    formLayout->addRow(tr("Dialog Timeout"), uiDlgTimeout);
    formLayout->addRow(tr("Default Host"), uiHost);
    formLayout->addRow(tr("Default SNMP Port"), uiPort);
    formLayout->addRow(tr("Default SNMP Version"), uiVersion);
    formLayout->addRow(tr("Default SNMP Community"), uiCommunity);
    formLayout->addRow(tr("Default SNMP Timeout"), uiTimeout);
    formLayout->addRow(tr("Default SNMP Retries"), uiRetries);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(uiButtonBox);

    connect(uiButtonBox, &QDialogButtonBox::accepted, this, &SnmpObjectDefaults::onAccepted);
    connect(uiButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

/*************************************************************/

void SnmpObjectDefaults::init()
{
    uiSystem->setText(SnmpObject::SYSTEM);
    uiSubsystem->setText(SnmpObject::SUBSYSTEM);
    uiDlgTimeout->setValue(SnmpObject::DLG_TIMEOUT);
    if (SnmpObject::root == Q_NULLPTR) {
        return;
    }
    if (SnmpObject::root->isHostValid()) uiHost->setText(SnmpObject::root->getHost());
    if (SnmpObject::root->isPortValid()) uiPort->setText(QString::number(SnmpObject::root->getPort()));
    if (SnmpObject::root->isVersionValid()) {
        int idx = uiVersion->findData(SnmpObject::root->getVersion());
        uiVersion->setCurrentIndex(idx);
    }
    if (SnmpObject::root->isCommunityValid()) uiCommunity->setText(SnmpObject::root->getCommunity());
    if (SnmpObject::root->isTimeoutValid()) uiTimeout->setText(QString::number(SnmpObject::root->getTimeout()));
    if (SnmpObject::root->isRetriesValid()) uiRetries->setText(QString::number(SnmpObject::root->getRetries()));
}

/*************************************************************/

void SnmpObjectDefaults::save()
{
    SnmpObject::SYSTEM = uiSystem->text();
    SnmpObject::SUBSYSTEM = uiSubsystem->text();
    SnmpObject::DLG_TIMEOUT = uiDlgTimeout->value();

    if (SnmpObject::root == Q_NULLPTR) {
        SnmpObject::root = new SnmpObject();
    }

    SnmpObject::root->clearVars();
    SnmpObject::root->setHostIfNotEmpty(uiHost->text());
    SnmpObject::root->setPortIfNotEmpty(uiPort->text());
    if (uiVersion->currentData().toInt() != SDPO::SNMPvDefault) {
        SnmpObject::root->setVersion(uiVersion->currentData().toInt());
    }
    SnmpObject::root->setCommunityIfNotEmpty(uiCommunity->text());
    SnmpObject::root->setTimeoutIfNotEmpty(uiTimeout->text());
    SnmpObject::root->setRetriesIfNotEmpty(uiRetries->text());
}

/*************************************************************/

bool SnmpObjectDefaults::validate(QString *err)
{
    if (uiSystem->text().isEmpty()) {
        err->append("[Error!] Наименование не может быть пустым");
        uiSystem->setFocus();
        return false;
    }
    return true;
}

/*************************************************************/

