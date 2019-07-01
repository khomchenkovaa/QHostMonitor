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
    explicit RebootRemoteSystemWidget(QWidget *parent = nullptr);
    ~RebootRemoteSystemWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private:
    Ui::RebootRemoteSystemWidget *ui;
};

} // namespace SDPO

#endif // QREBOOTREMOTESYSTEMWIDGET_H


