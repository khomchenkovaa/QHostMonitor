#ifndef SNMPOBJECTWIDGET_H
#define SNMPOBJECTWIDGET_H

#include "snmpobject.h"

#include <QTreeWidget>

namespace KharmonView {

class SnmpObjectWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit SnmpObjectWidget(QWidget *parent = nullptr);

signals:

public slots:
    void setSnmpObject(SnmpObject *node);

private:
    void setupUI();

};

} // namespace KharmonView

#endif // SNMPOBJECTWIDGET_H
