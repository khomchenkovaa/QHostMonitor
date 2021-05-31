#include "snmpobjectedit.h"

#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

using namespace KharmonView;

/*************************************************************/

SnmpObjectEdit::SnmpObjectEdit(SnmpObject *item, QWidget *parent)
    : QDialog(parent)
    , m_Item(item)
    , uiName (new QLineEdit(this))
    , uiHost (new QLineEdit(this))
    , uiModule (new QLineEdit(this))
    , uiPort (new QLineEdit(this))
    , uiVersion (new QComboBox(this))
    , uiCommunity (new QLineEdit(this))
    , uiTimeout (new QLineEdit(this))
    , uiRetries (new QLineEdit(this))
{
    setupUI();
    if (m_Item) {
        init();
    }
}

/*************************************************************/

SnmpObject *SnmpObjectEdit::getObject()
{
    return m_Item;
}

/*************************************************************/

void SnmpObjectEdit::onAccepted()
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

void SnmpObjectEdit::onNameChanged(const QString &text)
{
    QString title = m_Item ? tr("Edit Object") : tr("New Object");
    if (!text.isEmpty()) {
        title.append(" - ").append(text);
    }
    setWindowTitle(title);
}

/*************************************************************/

void SnmpObjectEdit::setupUI()
{
    QFont font;
    font.setPointSize(9);
    setFont(font);
    resize(600, 500);
    setWindowTitle(m_Item ? tr("Edit Object") : tr("New Object"));

    uiHost->setPlaceholderText(QString("default: %1").arg(SnmpObject::root->getHost()));
    uiPort->setPlaceholderText(QString("default: %1").arg(SnmpObject::root->getPort()));
    uiCommunity->setPlaceholderText(QString("default: %1").arg(SnmpObject::root->getCommunity()));
    uiTimeout->setPlaceholderText(QString("default: %1").arg(SnmpObject::root->getTimeout()));
    uiRetries->setPlaceholderText(QString("default: %1").arg(SnmpObject::root->getRetries()));

    uiVersion->addItem(tr("default"), SDPO::SNMPvDefault);
    uiVersion->addItem(tr("version 1"), SDPO::SNMPv1);
    uiVersion->addItem(tr("version 2c"), SDPO::SNMPv2c);
    uiVersion->addItem(tr("version 3"), SDPO::SNMPv3);

    QDialogButtonBox *uiButtonBox = new QDialogButtonBox(this);
    uiButtonBox->setOrientation(Qt::Vertical);
    uiButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(tr("Name"), uiName);
    formLayout->addRow(tr("Host"), uiHost);
    formLayout->addRow(tr("Module"), uiModule);
    formLayout->addRow(tr("SNMP Port"), uiPort);
    formLayout->addRow(tr("SNMP Version"), uiVersion);
    formLayout->addRow(tr("SNMP Community"), uiCommunity);
    formLayout->addRow(tr("SNMP Timeout"), uiTimeout);
    formLayout->addRow(tr("SNMP Retries"), uiRetries);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(uiButtonBox);


    connect(uiButtonBox, &QDialogButtonBox::accepted, this, &SnmpObjectEdit::onAccepted);
    connect(uiButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(uiName, &QLineEdit::textChanged, this, &SnmpObjectEdit::onNameChanged);
}

/*************************************************************/

void SnmpObjectEdit::init()
{
    if (m_Item == Q_NULLPTR) {
        return;
    }
    uiName->setText(m_Item->getName());
    if (m_Item->isHostValid()) uiHost->setText(m_Item->getHost());
    if (m_Item->getModIdx()) uiModule->setText(QString::number(m_Item->getModIdx()));
    if (m_Item->isPortValid()) uiPort->setText(QString::number(m_Item->getPort()));
    if (m_Item->isVersionValid()) {
        int idx = uiVersion->findData(m_Item->getVersion());
        uiVersion->setCurrentIndex(idx);
    }
    if (m_Item->isCommunityValid()) uiCommunity->setText(m_Item->getCommunity());
    if (m_Item->isTimeoutValid()) uiTimeout->setText(QString::number(m_Item->getTimeout()));
    if (m_Item->isRetriesValid()) uiRetries->setText(QString::number(m_Item->getRetries()));
}

/*************************************************************/

void SnmpObjectEdit::save()
{
    if (m_Item == Q_NULLPTR) {
        m_Item = new SnmpObject();
    }
    m_Item->clearVars();
    m_Item->setName(uiName->text());
    m_Item->setHostIfNotEmpty(uiHost->text());
    m_Item->setModuleIfNotEmpty(uiModule->text());
    m_Item->setPortIfNotEmpty(uiPort->text());
    if (uiVersion->currentData().toInt() != SDPO::SNMPvDefault) {
        m_Item->setVersion(uiVersion->currentData().toInt());
    }
    m_Item->setCommunityIfNotEmpty(uiCommunity->text());
    m_Item->setTimeoutIfNotEmpty(uiTimeout->text());
    m_Item->setRetriesIfNotEmpty(uiRetries->text());
}

/*************************************************************/

bool SnmpObjectEdit::validate(QString *err)
{
    if (uiName->text().isEmpty()) {
        err->append("[Error!] Наименование не может быть пустым");
        uiName->setFocus();
        return false;
    }
    return true;
}

/*************************************************************/
