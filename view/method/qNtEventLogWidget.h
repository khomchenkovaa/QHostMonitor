#ifndef QNTEVENTLOGWIDGET_H
#define QNTEVENTLOGWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class NtEventLogWidget;
}

namespace SDPO {

class NtEventLogWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit NtEventLogWidget(QWidget *parent = 0);
    ~NtEventLogWidget();

private:
    Ui::NtEventLogWidget *ui;
};

} // namespace SDPO

#endif // QNTEVENTLOGWIDGET_H
