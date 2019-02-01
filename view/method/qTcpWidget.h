#ifndef QTCPWIDGET_H
#define QTCPWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class TcpWidget;
}

namespace SDPO {

class TcpWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit TcpWidget(QWidget *parent = 0);
    ~TcpWidget();

signals:

private:
    Ui::TcpWidget *ui;
};

} // namespace SDPO

#endif // QTCPWIDGET_H
