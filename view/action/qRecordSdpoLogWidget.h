#ifndef QRECORDSDPOLOGWIDGET_H
#define QRECORDSDPOLOGWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class RecordSdpoLogWidget;
}

namespace SDPO {

class RecordSdpoLogWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit RecordSdpoLogWidget(QWidget *parent = nullptr);
    ~RecordSdpoLogWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnSpecificLog_clicked();

private:
    Ui::RecordSdpoLogWidget *ui;
};

} // namespace SDPO

#endif // QRECORDSDPOLOGWIDGET_H
