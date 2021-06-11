#ifndef TESTSCHEDULEWIDGET_H
#define TESTSCHEDULEWIDGET_H

#include <QWidget>

namespace Ui {
class TestScheduleWidget;
}

namespace SDPO {

class TTest;

class TestScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestScheduleWidget(QWidget *parent = nullptr);
    ~TestScheduleWidget();

    void reset();
    void init(TTest *item);
    void save(TTest *item);

private slots:
    void onBtnSchedulesDlg();
    void onBtnRegular();
    void onBtnIrregular();
    void onBtnByExpression();
    void onCmbIrregularModeChanged(int index);

private:
    void setupUI();

private:
    Ui::TestScheduleWidget *ui;
};

} // namespace SDPO

#endif // TESTSCHEDULEWIDGET_H
