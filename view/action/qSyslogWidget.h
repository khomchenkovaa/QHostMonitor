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
    explicit SyslogWidget(QWidget *parent = nullptr);
    ~SyslogWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnMessage_clicked();

private:
    Ui::SyslogWidget *ui;
};

} // namespace SDPO

#endif // QSYSLOGWIDGET_H
