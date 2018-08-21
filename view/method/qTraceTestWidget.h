#ifndef QTRACETESTWIDGET_H
#define QTRACETESTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class TraceTestWidget;
}

namespace SDPO {

class TraceTestWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit TraceTestWidget(QWidget *parent = 0);
    ~TraceTestWidget();

private:
    Ui::TraceTestWidget *ui;
};

} // namespace SDPO
#endif // QTRACETESTWIDGET_H
