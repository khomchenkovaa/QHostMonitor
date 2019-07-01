#ifndef QSENDMESSAGETOICQWIDGET_H
#define QSENDMESSAGETOICQWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SendMessageToIcqWidget;
}

namespace SDPO {

class SendMessageToIcqWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SendMessageToIcqWidget(QWidget *parent = nullptr);
    ~SendMessageToIcqWidget();

    virtual void init(TestAction *item = nullptr);
    virtual void reset();
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnSetupIcqAccounts_clicked();

    void on_btnMessageTemplate_clicked();

private:
    Ui::SendMessageToIcqWidget *ui;
};

} // namespace SDPO

#endif // QSENDMESSAGETOICQWIDGET_H
