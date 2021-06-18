#ifndef QTRAFFICMONITORWIDGET_H
#define QTRAFFICMONITORWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class TrafficMonitorWidget;
}

namespace SDPO {

class TrafficMonitorWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit TrafficMonitorWidget(QWidget *parent = 0);
    ~TrafficMonitorWidget();

private slots:
    void on_btnSnmpCredentials_clicked();

    void on_btnNetworkInterface_clicked();

    void on_cmbAlertSelect_currentIndexChanged(int index);

private:
    Ui::TrafficMonitorWidget *ui;
};

} // namespace SDPO
#endif // QTRAFFICMONITORWIDGET_H
