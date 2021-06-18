#ifndef QSERVICEWIDGET_H
#define QSERVICEWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class ServiceWidget;
}

namespace SDPO {

class ServiceWidget : public TestMethodWidget
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
