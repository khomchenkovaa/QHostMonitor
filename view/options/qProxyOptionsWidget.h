#ifndef QPROXYOPTIONSWIDGET_H
#define QPROXYOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class ProxyOptionsWidget;
}

namespace SDPO {

class ProxyOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit ProxyOptionsWidget(QWidget *parent = 0);
    ~ProxyOptionsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

private:
    Ui::ProxyOptionsWidget *ui;
};

} // namespace SDPO

#endif // QPROXYOPTIONSWIDGET_H
