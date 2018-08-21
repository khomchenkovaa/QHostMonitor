#ifndef QBEHAVIORWIDGET_H
#define QBEHAVIORWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class BehaviorWidget;
}

namespace SDPO {

class BehaviorWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit BehaviorWidget(QWidget *parent = 0);
    ~BehaviorWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

private:
    Ui::BehaviorWidget *ui;
};

} // namespace SDPO

#endif // QBEHAVIORWIDGET_H
