#ifndef QREBOOTREMOTESYSTEMWIDGET_H
#define QREBOOTREMOTESYSTEMWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class RebootRemoteSystemWidget;
}

namespace SDPO {

class RebootRemoteSystemWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit RebootRemoteSystemWidget(QWidget *parent = 0);
    ~RebootRemoteSystemWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private:
    Ui::RebootRemoteSystemWidget *ui;
};

} // namespace SDPO

#endif // QREBOOTREMOTESYSTEMWIDGET_H


