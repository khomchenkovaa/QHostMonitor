#ifndef QSNMPTRAPWIDGET_H
#define QSNMPTRAPWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class SnmpTrapWidget;
}

namespace SDPO {

class SnmpTrapWidget : public TestMethodWidget
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
