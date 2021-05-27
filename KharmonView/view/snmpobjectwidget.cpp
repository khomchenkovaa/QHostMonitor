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
    QString lblName      = tr("name");
    QString lblHost      = node->isHostValid() ? tr("host") : tr ("default_host");
    QString lblModule    = tr("module");
    QString lblPort      = node->isPortValid() ? tr("port") : tr ("default_snmp_port");
    QString lblVersion   = node->isVersionValid() ? tr("snmp_version") : tr ("default_snmp_version");
    QString lblCommunity = node->isCommunityValid() ? tr("snmp_community") : tr ("default_snmp_community");
    QString lblTimeout   = node->isTimeoutValid() ? tr("snmp_timeout") : tr ("default_snmp_timeout");
    QString lblRetries   = node->isRetriesValid() ? tr("snmp_retries") : tr ("default_snmp_retries");

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
