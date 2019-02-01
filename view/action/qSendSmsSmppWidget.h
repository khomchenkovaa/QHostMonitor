#ifndef QSENDSMSSMPPWIDGET_H
#define QSENDSMSSMPPWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SendSmsSmppWidget;
}

namespace SDPO {

class SendSmsSmppWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SendSmsSmppWidget(QWidget *parent = 0);
    ~SendSmsSmppWidget();

    virtual void init(TestAction *item = 0);
    virtual void reset();
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnMessageTemplateSelect_clicked();
    void on_btnSetupSmpp_clicked();

private:
    Ui::SendSmsSmppWidget *ui;
};

} // namespace SDPO

#endif // QSENDSMSSMPPWIDGET_H
