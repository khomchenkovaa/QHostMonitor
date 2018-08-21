#ifndef QUDPTESTWIDGET_H
#define QUDPTESTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class UdpTestWidget;
}

namespace SDPO {

class UdpTestWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit UdpTestWidget(QWidget *parent = 0);
    ~UdpTestWidget();

private:
    Ui::UdpTestWidget *ui;
};

} // namespace SDPO

#endif // QUDPTESTWIDGET_H
