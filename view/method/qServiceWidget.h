#ifndef QSERVICEWIDGET_H
#define QSERVICEWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class ServiceWidget;
}

namespace SDPO {

class ServiceWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit ServiceWidget(QWidget *parent = 0);
    ~ServiceWidget();

private slots:
    void on_btnServiceToMonitor_clicked();

private:
    Ui::ServiceWidget *ui;
};

} // namespace SDPO

#endif // QSERVICEWIDGET_H
