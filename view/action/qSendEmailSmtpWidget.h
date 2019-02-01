#ifndef QSENDEMAILSMTPWIDGET_H
#define QSENDEMAILSMTPWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SendEmailSmtpWidget;
}

namespace SDPO {

class SendEmailSmtpWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SendEmailSmtpWidget(QWidget *parent = 0);
    ~SendEmailSmtpWidget();

    virtual void init(TestAction *item = 0);
      virtual void reset();
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnToRecipients_clicked();
    void on_btnSubject_clicked();
    void on_btnBodyTemplate_clicked();
    void on_btnAttachFile_clicked();

private:
    Ui::SendEmailSmtpWidget *ui;
};

} // namespace SDPO

#endif // QSENDEMAILSMTPWIDGET_H
