#ifndef QPAGERSOPTIONSWIDGET_H
#define QPAGERSOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class PagersOptionsWidget;
}

namespace SDPO {

class PagersOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit PagersOptionsWidget(QWidget *parent = 0);
    ~PagersOptionsWidget();

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);

private:
    Ui::PagersOptionsWidget *ui;
};

} // namespace SDPO

#endif // QPAGERSOPTIONSWIDGET_H
