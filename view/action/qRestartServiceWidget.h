#ifndef QRESTARTSERVICEWIDGET_H
#define QRESTARTSERVICEWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class RestartServiceWidget;
}

namespace SDPO {

class RestartServiceWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit RestartServiceWidget(QWidget *parent = 0);
    ~RestartServiceWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_chkConnectStatus();

private:
    Ui::RestartServiceWidget *ui;
};

} // namespace SDPO

#endif // QRESTARTSERVICEWIDGET_H
