#include "qPerformanceCounterWidget.h"
#include "ui_qPerformanceCounterWidget.h"

namespace SDPO {

PerformanceCounterWidget::PerformanceCounterWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::PerformanceCounterWidget)
{
    ui->setupUi(this);
}

PerformanceCounterWidget::~PerformanceCounterWidget()
{
    delete ui;
}

} // namespace SDPO
