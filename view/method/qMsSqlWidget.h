#ifndef QMSSQLWIDGET_H
#define QMSSQLWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class MsSqlWidget;
}

namespace SDPO {

class MsSqlWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit MsSqlWidget(QWidget *parent = 0);
    ~MsSqlWidget();

private:
    Ui::MsSqlWidget *ui;
};

} // namespace SDPO

#endif // QMSSQLWIDGET_H
