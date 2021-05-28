#ifndef SNMPRESULTWIDGET_H
#define SNMPRESULTWIDGET_H

#include "snmpobject.h"

#include <QTreeWidget>

namespace KharmonView {

class SnmpResultWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit SnmpResultWidget(QWidget *parent = nullptr);

signals:

public slots:
    void setSnmpObject(SnmpObject *node);
    void updateSnmpObject(SnmpObject *node);

private:
    void setupUI();
    void setSysInfo(const SnmpSystem *info);
    void setStatInfo(const SnmpStatus *info);
    void setModuleInfo(const SnmpModule *info);
    void setModuleList(const SnmpModList *modList, const SnmpParamList *paramList);
    void setParamInfo(QTreeWidgetItem *parent, const SnmpParameter *info);
    void setParamList(QTreeWidgetItem *parent, const SnmpParamList *paramList, int modIdx);
    QIcon iconByModStatus(const int status) const;
    QIcon iconByParamStatus(const int status) const;
    QString statusAsText(const int status) const;
    void setColorByStatus(QTreeWidgetItem *item, const int column, const int status);

};

} // namespace KharmonView

#endif // SNMPRESULTWIDGET_H
