#ifndef QSYSLOGWIDGET_H
#define QSYSLOGWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SyslogWidget;
}

namespace SDPO {

class SyslogWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SyslogWidget(QWidget *parent = 0);
    ~SyslogWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnMessage_clicked();

private:
    Ui::SyslogWidget *ui;
};

} // namespace SDPO

#endif // QSYSLOGWIDGET_H
