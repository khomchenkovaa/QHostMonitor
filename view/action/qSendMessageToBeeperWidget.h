#ifndef QSENDMESSAGETOBEEPERWIDGET_H
#define QSENDMESSAGETOBEEPERWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SendMessageToBeeperWidget;
}

namespace SDPO {

class SendMessageToBeeperWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SendMessageToBeeperWidget(QWidget *parent = 0);
    ~SendMessageToBeeperWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private:
    Ui::SendMessageToBeeperWidget *ui;
};

} // namespace SDPO

#endif // QSENDMESSAGETOBEEPERWIDGET_H
