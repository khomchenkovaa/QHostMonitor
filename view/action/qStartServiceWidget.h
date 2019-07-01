#ifndef QSTARTSERVICEWIDGET_H
#define QSTARTSERVICEWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class StartServiceWidget;
}

namespace SDPO {

class StartServiceWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit StartServiceWidget(QWidget *parent = nullptr);
    ~StartServiceWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_chkConnectStatus();

private:
    Ui::StartServiceWidget *ui;
};

} // namespace SDPO

#endif // QSTARTSERVICEWIDGET_H
