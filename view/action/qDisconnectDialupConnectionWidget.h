#ifndef QDISCONNECTDIALUPCONNECTIONWIDGET_H
#define QDISCONNECTDIALUPCONNECTIONWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class DisconnectDialupConnectionWidget;
}

namespace SDPO {

class DisconnectDialupConnectionWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit DisconnectDialupConnectionWidget(QWidget *parent = 0);
    ~DisconnectDialupConnectionWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private:
    Ui::DisconnectDialupConnectionWidget *ui;
};

} // namespace SDPO

#endif // QDISCONNECTDIALUPCONNECTIONWIDGET_H
