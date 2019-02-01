#ifndef QSTOPSERVICEWIDGET_H
#define QSTOPSERVICEWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class StopServiceWidget;
}

namespace SDPO {

class StopServiceWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit StopServiceWidget(QWidget *parent = 0);
    ~StopServiceWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_chkConnectStatus();

private:
    Ui::StopServiceWidget *ui;
};

} // namespace SDPO

#endif // QSTOPSERVICEWIDGET_H
