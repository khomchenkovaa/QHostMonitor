#ifndef QSENDMESSAGETOPAGERTAPWIDGET_H
#define QSENDMESSAGETOPAGERTAPWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SendMessageToPagerTapWidget;
}

namespace SDPO {

class SendMessageToPagerTapWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SendMessageToPagerTapWidget(QWidget *parent = 0);
    ~SendMessageToPagerTapWidget();

    virtual void init(TestAction *item = 0);
    virtual void reset();
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnPagingSettings_clicked();
    void on_btnMsgTemplate_clicked();

private:
    Ui::SendMessageToPagerTapWidget *ui;
};

} // namespace SDPO

#endif // QSENDMESSAGETOPAGERTAPWIDGET_H
