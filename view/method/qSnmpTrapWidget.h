#ifndef QSNMPTRAPWIDGET_H
#define QSNMPTRAPWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class SnmpTrapWidget;
}

namespace SDPO {

class SnmpTrapWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit SnmpTrapWidget(QWidget *parent = 0);
    ~SnmpTrapWidget();

private slots:
    void onSnmpTrapFilterCall();

private:
    Ui::SnmpTrapWidget *ui;
};

} // namespace SDPO

#endif // QSNMPTRAPWIDGET_H
