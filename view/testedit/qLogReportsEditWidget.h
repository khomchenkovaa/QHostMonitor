#ifndef QLOGREPORTSEDITWIDGET_H
#define QLOGREPORTSEDITWIDGET_H

#include <QWidget>

namespace Ui {
class LogReportsEditWidget;
}

namespace SDPO {

class TTest;

class LogReportsEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogReportsEditWidget(QWidget *parent = 0);
    ~LogReportsEditWidget();

    void init(TTest *item = 0);
    void save(TTest *item);
    void reset();

private slots:
    void on_btnPrivateLogFile_clicked();

private:
    Ui::LogReportsEditWidget *ui;
};

} // namespace SDPO

#endif // QLOGREPORTSEDITWIDGET_H
