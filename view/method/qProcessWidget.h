#ifndef QPROCESSWIDGET_H
#define QPROCESSWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class ProcessWidget;
}

namespace SDPO {

class ProcessWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit ProcessWidget(QWidget *parent = 0);
    ~ProcessWidget();

private:
    Ui::ProcessWidget *ui;
};

} // namespace SDPO

#endif // QPROCESSWIDGET_H
