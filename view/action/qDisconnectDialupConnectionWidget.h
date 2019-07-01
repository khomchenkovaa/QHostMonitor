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
    explicit DisconnectDialupConnectionWidget(QWidget *parent = nullptr);
    ~DisconnectDialupConnectionWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private:
    Ui::DisconnectDialupConnectionWidget *ui;
};

} // namespace SDPO

#endif // QDISCONNECTDIALUPCONNECTIONWIDGET_H
