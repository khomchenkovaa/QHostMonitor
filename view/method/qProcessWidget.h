#ifndef QPROCESSWIDGET_H
#define QPROCESSWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class ProcessWidget;
}

namespace SDPO {

class ProcessWidget : public TestMethodWidget
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
