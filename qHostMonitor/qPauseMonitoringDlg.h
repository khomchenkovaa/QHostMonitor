#ifndef QPAUSEMONITORINGDLG_H
#define QPAUSEMONITORINGDLG_H

#include <QDialog>

namespace Ui {
class PauseMonitoringDlg;
}

namespace SDPO {

class PauseMonitoringDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PauseMonitoringDlg(QWidget *parent = 0);
    ~PauseMonitoringDlg();

private:
    Ui::PauseMonitoringDlg *ui;
};

} // namespace SDPO

#endif // QPAUSEMONITORINGDLG_H
