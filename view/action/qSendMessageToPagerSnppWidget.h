#ifndef QSENDMESSAGETOPAGERSNPPWIDGET_H
#define QSENDMESSAGETOPAGERSNPPWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SendMessageToPagerSnppWidget;
}

namespace SDPO {

class SendMessageToPagerSnppWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SendMessageToPagerSnppWidget(QWidget *parent = nullptr);
    ~SendMessageToPagerSnppWidget();

    virtual void init(TestAction *item = nullptr);
    virtual void reset();
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnMailTemplate_clicked();

private:
    Ui::SendMessageToPagerSnppWidget *ui;
};

} // namespace SDPO

#endif // QSENDMESSAGETOPAGERSNPPWIDGET_H
