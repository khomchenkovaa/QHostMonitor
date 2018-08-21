#ifndef QSMSSMPPOPTIONSWIDGET_H
#define QSMSSMPPOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class SmsSmppOptionsWidget;
}

namespace SDPO {

class SmsSmppOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit SmsSmppOptionsWidget(QWidget *parent = 0);
    ~SmsSmppOptionsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

private:
    Ui::SmsSmppOptionsWidget *ui;
};

} // namespace SDPO

#endif // QSMSSMPPOPTIONSWIDGET_H
