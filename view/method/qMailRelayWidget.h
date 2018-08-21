#ifndef QMAILRELAYWIDGET_H
#define QMAILRELAYWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class MailRelayWidget;
}

namespace SDPO {

class MailRelayWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit MailRelayWidget(QWidget *parent = 0);
    ~MailRelayWidget();

private slots:
    void openPropertiesDlg();

private:
    Ui::MailRelayWidget *ui;
};

} // namespace SDPO

#endif // QMAILRELAYWIDGET_H
