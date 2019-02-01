#ifndef QREBOOTLOCALMACHINEWIDGET_H
#define QREBOOTLOCALMACHINEWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class RebootLocalMachineWidget;
}

namespace SDPO {

class RebootLocalMachineWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit RebootLocalMachineWidget(QWidget *parent = 0);
    ~RebootLocalMachineWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private:
    Ui::RebootLocalMachineWidget *ui;
};

} // namespace SDPO

#endif // QREBOOTLOCALMACHINEWIDGET_H
