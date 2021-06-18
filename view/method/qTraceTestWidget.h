#ifndef QTRACETESTWIDGET_H
#define QTRACETESTWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class TraceTestWidget;
}

namespace SDPO {

class TraceTestWidget : public TestMethodWidget
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
