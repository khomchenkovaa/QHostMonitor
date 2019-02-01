#ifndef QSDPOMONITORWIDGET_H
#define QSDPOMONITORWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class SdpoMonitorWidget;
}

namespace SDPO {

class SdpoMonitorWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit SdpoMonitorWidget(QWidget *parent = 0);
    ~SdpoMonitorWidget();

private:
    Ui::SdpoMonitorWidget *ui;
};

} // namespace SDPO

#endif // QSDPOMONITORWIDGET_H
