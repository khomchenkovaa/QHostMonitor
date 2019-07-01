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
    explicit SendMessageToBeeperWidget(QWidget *parent = nullptr);
    ~SendMessageToBeeperWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private:
    Ui::SendMessageToBeeperWidget *ui;
};

} // namespace SDPO

#endif // QSENDMESSAGETOBEEPERWIDGET_H
