#ifndef QSYBASEWIDGET_H
#define QSYBASEWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class SybaseWidget;
}

namespace SDPO {

class SybaseWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit SybaseWidget(QWidget *parent = 0);
    ~SybaseWidget();

private:
    Ui::SybaseWidget *ui;
};

} // namespace SDPO

#endif // QSYBASEWIDGET_H
