#ifndef QSENDDATATOTCPUDPPORTWIDGET_H
#define QSENDDATATOTCPUDPPORTWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SendDataToTcpUdpPortWidget;
}

namespace SDPO {

class SendDataToTcpUdpPortWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SendDataToTcpUdpPortWidget(QWidget *parent = 0);
    ~SendDataToTcpUdpPortWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnInitPacket_clicked();
    void on_btnFinalPacket_clicked();

private:
    Ui::SendDataToTcpUdpPortWidget *ui;
};

} // namespace SDPO

#endif // QSENDDATATOTCPUDPPORTWIDGET_H
