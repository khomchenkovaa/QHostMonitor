#ifndef SNMPRESULTLOG_H
#define SNMPRESULTLOG_H

#include "snmpobject.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

namespace KharmonView {

class SnmpResultLog : public QDialog
{
    Q_OBJECT
public:
    explicit SnmpResultLog(SnmpObject *node, QWidget *parent = nullptr);

private:
    void setupUI();
    void init(SnmpObject *node);
    QString logPriority(int priority);
    void setColorByPriority(QTreeWidgetItem *item, int priority);
    QIcon iconByPriority(int priority);

private:
    QTreeWidget *uiMessages;
};

} // namespace KharmonView

#endif // SNMPRESULTLOG_H
