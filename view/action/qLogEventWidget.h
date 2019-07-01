#ifndef QLOGEVENTWIDGET_H
#define QLOGEVENTWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class LogEventWidget;
}

namespace SDPO {

class LogEventWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit LogEventWidget(QWidget *parent = nullptr);
    ~LogEventWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnDescription_clicked();

private:
    Ui::LogEventWidget *ui;
};

} // namespace SDPO

#endif // QLOGEVENTWIDGET_H
