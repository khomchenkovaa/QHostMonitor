#ifndef QCHANGETESTINTERVALWIDGET_H
#define QCHANGETESTINTERVALWIDGET_H

#include "qActionWidget.h"
#include <QTime>

namespace Ui {
class ChangeTestIntervalWidget;
}

namespace SDPO {

class ChangeTestIntervalWidget : public ActionWidget
{
    Q_OBJECT

public:
    //QTime t;
    explicit ChangeTestIntervalWidget(QWidget *parent = 0);
    ~ChangeTestIntervalWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private:
    Ui::ChangeTestIntervalWidget *ui;
};

} // namespace SDPO

#endif // QCHANGETESTINTERVALWIDGET_H
