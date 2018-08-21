#ifndef QACTIONPROFILESADDMENU_H
#define QACTIONPROFILESADDMENU_H

#include <QDialog>

namespace Ui {
class ActionProfilesAddMenu;
}

namespace SDPO {

class ActionProfilesAddMenu : public QDialog
{
    Q_OBJECT

    int m_result;
public:
    explicit ActionProfilesAddMenu(QWidget *parent = 0);
    ~ActionProfilesAddMenu();

    int getResult();
private slots:
    // 1-st column
    void on_btnShowPopupWindow_clicked();
    void on_btnPlaySound_clicked();
    void on_btnSendMessageToPagerTap_clicked();
    void on_btnSendMessageToPagerSnpp_clicked();
    void on_btnSendMessageToBeeper_clicked();
    void on_btnSendSmsGsm_clicked();
    void on_btnSendSmsSmpp_clicked();
    void on_btnSendEmailSmtp_clicked();
    void on_btnSendMessageIcq_clicked();
    void on_btnSendMessageToJabber_clicked();
    // 2-nd column
    void on_btnRecordSdpoLog_clicked();
    void on_btnGenerateReports_clicked();
    void on_btnStopService_clicked();
    void on_btnStartService_clicked();
    void on_btnRestartService_clicked();
    void on_btnRebootRemoteSystem_clicked();
    void on_btnRebootLocalMachine_clicked();
    void on_btnDilaupToTheNetwork_clicked();
    void on_btnDisconnectDialUp_clicked();
    void on_btnExecuteExternalProgram_clicked();
    // 3-rd column
    void on_btnLogEvent_clicked();
    void on_btnSqlQuery_clicked();
    void on_btnHttpRequest_clicked();
    void on_btnSendDataToPort_clicked();
    void on_btnSyslog_clicked();
    void on_btnSnmpSet_clicked();
    void on_btnSnmpTrap_clicked();
    void on_btnRepeatTest_clicked();
    void on_btnChangeTestInterval_clicked();
    void on_btnRunHmsScript_clicked();

private:
    Ui::ActionProfilesAddMenu *ui;
};

} // namespace SDPO

#endif // QACTIONPROFILESADDMENU_H
