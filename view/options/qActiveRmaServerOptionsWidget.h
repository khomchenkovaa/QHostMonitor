#ifndef QACTIVERMASERVEROPTIONSWIDGET_H
#define QACTIVERMASERVEROPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class ActiveRmaServerOptionsWidget;
}

namespace SDPO {

class ActiveRmaServerOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit ActiveRmaServerOptionsWidget(QWidget *parent = 0);
    ~ActiveRmaServerOptionsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

private:
    Ui::ActiveRmaServerOptionsWidget *ui;
};

} // namespace SDPO

#endif // QACTIVERMASERVEROPTIONSWIDGET_H
