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
    explicit SendMessageToJabberWidget(QWidget *parent = nullptr);
    ~SendMessageToJabberWidget();

    virtual void init(TestAction *item = nullptr);
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
