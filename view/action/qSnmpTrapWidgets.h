#ifndef QSNMPTRAPWIDGETS_H
#define QSNMPTRAPWIDGETS_H

#include "qActionWidget.h"

namespace Ui {
class SnmpTrapWidgets;
}

namespace SDPO {

class SnmpTrapWidgets : public ActionWidget
{
    Q_OBJECT

public:
    explicit SnmpTrapWidgets(QWidget *parent = 0);
    ~SnmpTrapWidgets();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private:
    Ui::SnmpTrapWidgets *ui;
};

} // namespace SDPO

#endif // QSNMPTRAPWIDGET_H
