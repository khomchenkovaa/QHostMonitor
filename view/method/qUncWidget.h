#ifndef QUNCWIDGET_H
#define QUNCWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class UncWidget;
}

namespace SDPO {

class UncWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit UncWidget(QWidget *parent = 0);
    ~UncWidget();

private:
    Ui::UncWidget *ui;
};

} //namespace SDPO {

#endif // QUNCWIDGET_H
