#ifndef QREPEATTESTWIDGET_H
#define QREPEATTESTWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class RepeatTestWidget;
}

namespace SDPO {

class RepeatTestWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit RepeatTestWidget(QWidget *parent = 0);
    ~RepeatTestWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private:
    Ui::RepeatTestWidget *ui;
};

} // namespace SDPO

#endif // QREPEATTESTWIDGET_H
