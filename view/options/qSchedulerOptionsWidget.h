#ifndef QSCHEDULEROPTIONSWIDGET_H
#define QSCHEDULEROPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class SchedulerOptionsWidget;
}

namespace SDPO {

class SchedulerOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit SchedulerOptionsWidget(QWidget *parent = 0);
    ~SchedulerOptionsWidget();

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);
    void reset_AlertProfiles();

    private slots:
        void on_SchedulerSelect();
        void on_btnAlertSelect_1_clicked();
        void on_btnAlertSelect_2_clicked();
        void on_btnAlertSelect_3_clicked();
        void on_btnAlertSelect_4_clicked();
        void on_btnAlertSelect_5_clicked();

private:
    Ui::SchedulerOptionsWidget *ui;
};

} // namespace SDPO

#endif // QSCHEDULEROPTIONSWIDGET_H
