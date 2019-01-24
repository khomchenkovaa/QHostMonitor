#ifndef QSNMPSETWIDGET_H
#define QSNMPSETWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SnmpSetWidget;
}

namespace SDPO {

class SnmpSetWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SnmpSetWidget(QWidget *parent = 0);
    ~SnmpSetWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private:
    Ui::SnmpSetWidget *ui;
};

} // namespace SDPO

#endif // QSNMPSETWIDGET_H
