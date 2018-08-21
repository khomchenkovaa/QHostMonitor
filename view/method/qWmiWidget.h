#ifndef QWMIWIDGET_H
#define QWMIWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class WmiWidget;
}

namespace SDPO {

class WmiWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit WmiWidget(QWidget *parent = 0);
    ~WmiWidget();

private:
    Ui::WmiWidget *ui;
};

} // namespace SDPO

#endif // QWMIWIDGET_H
