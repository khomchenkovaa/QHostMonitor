#ifndef QPAUSEMONITORINGDLG_H
#define QPAUSEMONITORINGDLG_H

#include <QDialog>
#include <QDateTime>
#include <QComboBox>

namespace Ui {
class PauseMonitoringDlg;
}

namespace SDPO {

class MonitoringService;
class ActionService;

class PauseMonitoringDlg : public QDialog
{
    Q_OBJECT

    Ui::PauseMonitoringDlg *ui;

    MonitoringService *m_MonitoringService;
    ActionService     *m_ActionService;
public:
    explicit PauseMonitoringDlg(MonitoringService * monitoring, ActionService * alerts, QWidget *parent = 0);
    ~PauseMonitoringDlg();

private slots:
    void on_btnMonitoringStarted_clicked();
    void on_btnMonitoringStopped_clicked();
    void on_btnAlertingStarted_clicked();
    void on_btnAlertingStopped_clicked();
    void on_btnBoxPauseMonitoring_accepted();

private:
    void reset();
    void loadMonitoringData();
    void loadAlertsData();
    void saveMonitoringData();
    void saveAlertsData();
    void btnActionsClick(QComboBox *cmb);
};

} // namespace SDPO

#endif // QPAUSEMONITORINGDLG_H
