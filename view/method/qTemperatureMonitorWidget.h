#ifndef QTEMPERATUREMONITORWIDGET_H
#define QTEMPERATUREMONITORWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class TemperatureMonitorWidget;
}

namespace SDPO {

class TemperatureMonitorWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit TemperatureMonitorWidget(QWidget *parent = 0);
    ~TemperatureMonitorWidget();

private:
    Ui::TemperatureMonitorWidget *ui;
};

} // namespace SDPO
#endif // QTEMPERATUREMONITORWIDGET_H
