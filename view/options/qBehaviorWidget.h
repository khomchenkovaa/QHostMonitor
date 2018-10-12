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

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);

private:
    Ui::BehaviorWidget *ui;
};

} // namespace SDPO

#endif // QBEHAVIORWIDGET_H
