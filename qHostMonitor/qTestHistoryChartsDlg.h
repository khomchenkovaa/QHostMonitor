#ifndef QTESTHISTORYCHARTSDLG_H
#define QTESTHISTORYCHARTSDLG_H

#include <QDialog>

namespace Ui {
class TestHistoryChartsDlg;
}

namespace SDPO {

class TestHistoryChartsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TestHistoryChartsDlg(QWidget *parent = 0);
    ~TestHistoryChartsDlg();

private:
    Ui::TestHistoryChartsDlg *ui;
};

} // namespace SDPO

#endif // QTESTHISTORYCHARTSDLG_H
