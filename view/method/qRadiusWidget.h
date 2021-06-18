#ifndef QRADIUSWIDGET_H
#define QRADIUSWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class RadiusWidget;
}

namespace SDPO {

class RadiusWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit RadiusWidget(QWidget *parent = 0);
    ~RadiusWidget();

private:
    Ui::RadiusWidget *ui;
};

} // namespace SDPO
#endif // QRADIUSWIDGET_H
