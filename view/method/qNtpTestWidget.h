#ifndef QNTPTESTWIDGET_H
#define QNTPTESTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class NtpTestWidget;
}

namespace SDPO {

class NtpTestWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit NtpTestWidget(QWidget *parent = 0);
    ~NtpTestWidget();

private:
    Ui::NtpTestWidget *ui;
};

} // namespace SDPO
#endif // QNTPTESTWIDGET_H
