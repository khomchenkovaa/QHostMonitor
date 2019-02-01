#include "qActionProfilesAddMenu.h"
#include "ui_qActionProfilesAddMenu.h"

namespace SDPO {

/******************************************************************/

ActionProfilesAddMenu::ActionProfilesAddMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActionProfilesAddMenu)
{
    ui->setupUi(this);
    m_result = -1; // Cancel
}

/******************************************************************/

ActionProfilesAddMenu::~ActionProfilesAddMenu()
{
    delete ui;
}

/******************************************************************/

int ActionProfilesAddMenu::getResult()
{
    return m_result;
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnShowPopupWindow_clicked()
{
    m_result = 0;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnPlaySound_clicked()
{
    m_result = 1;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSendMessageToPagerTap_clicked()
{
    m_result = 2;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSendMessageToPagerSnpp_clicked()
{
    m_result = 3;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSendMessageToBeeper_clicked()
{
    m_result = 4;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSendSmsGsm_clicked()
{
    m_result = 5;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSendSmsSmpp_clicked()
{
    m_result = 6;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSendEmailSmtp_clicked()
{
    m_result = 7;
    this->accept();

}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSendMessageIcq_clicked()
{
    m_result = 8;
    this->accept();

}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSendMessageToJabber_clicked()
{
    m_result = 9;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnRecordSdpoLog_clicked()
{
    m_result = 10;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnGenerateReports_clicked()
{
    m_result = 11;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnStopService_clicked()
{
    m_result = 12;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnStartService_clicked()
{
    m_result = 13;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnRestartService_clicked()
{
    m_result = 14;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnRebootRemoteSystem_clicked()
{
    m_result = 15;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnRebootLocalMachine_clicked()
{
    m_result = 16;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnDilaupToTheNetwork_clicked()
{
    m_result = 17;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnDisconnectDialUp_clicked()
{
    m_result = 18;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnExecuteExternalProgram_clicked()
{
    m_result = 19;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnLogEvent_clicked()
{
    m_result = 20;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSqlQuery_clicked()
{
    m_result = 21;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnHttpRequest_clicked()
{
    m_result = 22;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSendDataToPort_clicked()
{
    m_result = 23;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSyslog_clicked()
{
    m_result = 24;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSnmpSet_clicked()
{
    m_result = 25;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnSnmpTrap_clicked()
{
    m_result = 26;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnRepeatTest_clicked()
{
    m_result = 27;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnChangeTestInterval_clicked()
{
    m_result = 28;
    this->accept();
}

/******************************************************************/

void ActionProfilesAddMenu::on_btnRunHmsScript_clicked()
{
    m_result = 29;
    this->accept();
}

/******************************************************************/

} // namespace SDPO

