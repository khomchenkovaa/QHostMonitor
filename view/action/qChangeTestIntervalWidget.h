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
    explicit ChangeTestIntervalWidget(QWidget *parent = nullptr);
    ~ChangeTestIntervalWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private:
    Ui::ChangeTestIntervalWidget *ui;
};

} // namespace SDPO

#endif // QCHANGETESTINTERVALWIDGET_H
