#ifndef QIMAPTESTWIDGET_H
#define QIMAPTESTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class ImapTestWidget;
}

namespace SDPO {

class ImapTestWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit ImapTestWidget(QWidget *parent = 0);
    ~ImapTestWidget();

private:
    Ui::ImapTestWidget *ui;
};

} // namespace SDPO

#endif // QIMAPTESTWIDGET_H
