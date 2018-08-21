#ifndef QPERFORMANCECOUNTERWIDGET_H
#define QPERFORMANCECOUNTERWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class PerformanceCounterWidget;
}

namespace SDPO {

class PerformanceCounterWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit PerformanceCounterWidget(QWidget *parent = 0);
    ~PerformanceCounterWidget();

private:
    Ui::PerformanceCounterWidget *ui;
};

} // namespace SDPO
#endif // QPERFORMANCECOUNTERWIDGET_H
