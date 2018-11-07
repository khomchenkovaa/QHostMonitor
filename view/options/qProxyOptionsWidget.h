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

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);

private:
    Ui::ProxyOptionsWidget *ui;
};

} // namespace SDPO

#endif // QPROXYOPTIONSWIDGET_H
