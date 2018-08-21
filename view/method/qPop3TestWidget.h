#ifndef QPOP3TESTWIDGET_H
#define QPOP3TESTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class Pop3TestWidget;
}

namespace SDPO {

class Pop3TestWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit Pop3TestWidget(QWidget *parent = 0);
    ~Pop3TestWidget();

private:
    Ui::Pop3TestWidget *ui;
};

} // namespace SDPO

#endif // QPOP3TESTWIDGET_H
