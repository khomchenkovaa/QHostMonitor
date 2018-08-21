#ifndef QSENDSMSGSMMODEMWIDGET_H
#define QSENDSMSGSMMODEMWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SendSmsGsmModemWidget;
}

namespace SDPO {

class SendSmsGsmModemWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SendSmsGsmModemWidget(QWidget *parent = 0);
    ~SendSmsGsmModemWidget();

    virtual void init(TestAction *item = 0);
    virtual void reset();
    virtual TestAction *save(TestAction *item);


private slots:
    void on_btnGsmSettings_clicked();
    void on_btnMsgTemplate_clicked();

private:
    Ui::SendSmsGsmModemWidget *ui;
};

} // namespace SDPO

#endif // QSENDSMSGSMMODEMWIDGET_H
