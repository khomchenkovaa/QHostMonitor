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
    explicit SnmpSetWidget(QWidget *parent = nullptr);
    ~SnmpSetWidget();

    virtual void init(TestAction *item = nullptr);
    virtual void reset();
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnGetCurrentValue_clicked();

private:
    Ui::SnmpSetWidget *ui;
};

} // namespace SDPO

#endif // QSNMPSETWIDGET_H
