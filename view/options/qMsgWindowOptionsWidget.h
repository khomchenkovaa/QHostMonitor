#ifndef QMSGWINDOWOPTIONSWIDGET_H
#define QMSGWINDOWOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class MsgWindowOptionsWidget;
}

namespace SDPO {

class MsgWindowOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit MsgWindowOptionsWidget(QWidget *parent = 0);
    ~MsgWindowOptionsWidget();

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);

private:
    Ui::MsgWindowOptionsWidget *ui;
};

} // namespace SDPO

#endif // QMSGWINDOWOPTIONSWIDGET_H
