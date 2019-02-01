#ifndef QSENDMESSAGETOJABBERWIDGET_H
#define QSENDMESSAGETOJABBERWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SendMessageToJabberWidget;
}

namespace SDPO {

class SendMessageToJabberWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SendMessageToJabberWidget(QWidget *parent = 0);
    ~SendMessageToJabberWidget();

    virtual void init(TestAction *item = 0);
    virtual void reset();
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnSetupJabberAccounts_clicked();
    void on_btnMessageTemplate_clicked();

private:
    Ui::SendMessageToJabberWidget *ui;
};

} // namespace SDPO

#endif // QSENDMESSAGETOJABBERWIDGET_H
