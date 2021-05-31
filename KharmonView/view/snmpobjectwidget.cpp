#include "snmpobjectwidget.h"

#include <QHeaderView>

using namespace KharmonView;

/*************************************************************/

SnmpObjectWidget::SnmpObjectWidget(QWidget *parent) : QTreeWidget(parent)
{
    setupUI();
}

/*************************************************************/

void SnmpObjectWidget::setSnmpObject(SnmpObject *node)
{
    QString lblName      = tr("Name");
    QString lblHost      = node->isHostValid() ? tr("Host") : tr ("Default Host");
    QString lblModule    = tr("Module");
    QString lblPort      = node->isPortValid() ? tr("SNMP Port") : tr ("Default SNMP Port");
    QString lblVersion   = node->isVersionValid() ? tr("SNMP Version") : tr ("Default SNMP Version");
    QString lblCommunity = node->isCommunityValid() ? tr("SNMP Community") : tr ("Default SNMP Community");
    QString lblTimeout   = node->isTimeoutValid() ? tr("SNMP Timeout") : tr ("Default SNMP Timeout");
    QString lblRetries   = node->isRetriesValid() ? tr("SNMP Retries") : tr ("Default SNMP Retries");

    clear();

    QString name = (node == nullptr)? SnmpObject::objectTitle() : node->getName();

    addTopLevelItem(new QTreeWidgetItem(QStringList() << lblName << name));
    addTopLevelItem(new QTreeWidgetItem(QStringList() << lblHost << node->getHost()));
    if (node->getModIdx()) {
        addTopLevelItem(new QTreeWidgetItem(QStringList() << lblModule << QString::number(node->getModIdx())));
    }
    addTopLevelItem(new QTreeWidgetItem(QStringList() << lblPort << QString::number(node->getPort())));
    addTopLevelItem(new QTreeWidgetItem(QStringList() << lblVersion << QString::number(node->getVersion())));
    addTopLevelItem(new QTreeWidgetItem(QStringList() << lblCommunity << node->getCommunity()));
    addTopLevelItem(new QTreeWidgetItem(QStringList() << lblTimeout << QString::number(node->getTimeout())));
    addTopLevelItem(new QTreeWidgetItem(QStringList() << lblRetries << QString::number(node->getRetries())));
}

/*************************************************************/

void SnmpObjectWidget::setupUI()
{
    setObjectName(QStringLiteral("ObjectInfo"));

    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);

    QFont font;
    font.setPointSize(9);

    QString styleSheet =
        "QTreeWidget::item:!selected { "
        "border: 1px solid gainsboro; "
        "border-left: none; "
        "border-top: none; "
        "} "
        "QTreeView::item:selected {}";

    setStyleSheet(styleSheet);
    setAlternatingRowColors(true);
    setIndentation(0);
    setColumnCount(2);
    setColumnWidth(0, 150);
    setMinimumWidth(250);
    setHeaderLabels(QStringList() << "Атрибут" << "Значение");
    setFont(font);
    header()->setFont(font);
}

/*************************************************************/
