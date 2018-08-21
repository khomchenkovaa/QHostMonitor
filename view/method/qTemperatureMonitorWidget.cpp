#include "qTemperatureMonitorWidget.h"
#include "ui_qTemperatureMonitorWidget.h"

namespace SDPO {

TemperatureMonitorWidget::TemperatureMonitorWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::TemperatureMonitorWidget)
{
    ui->setupUi(this);
}

TemperatureMonitorWidget::~TemperatureMonitorWidget()
{
    delete ui;
}

} // namespace SDPO
