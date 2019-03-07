#include "hmTelnetServiceDialog.h"
#include "ui_hmTelnetServiceDialog.h"

#include <QDebug>

using namespace SDPO;

/******************************************************************/

HMTelnetServiceDialog::HMTelnetServiceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HMTelnetServiceDialog)
{
    ui->setupUi(this);
}

/******************************************************************/

HMTelnetServiceDialog::~HMTelnetServiceDialog()
{
    delete ui;
}

/******************************************************************/

void HMTelnetServiceDialog::on_btnApply_clicked()
{
//    RciSettings settings;
//    settings.address = ui->cmbRciAddress->currentText();
//    settings.port = static_cast<quint16>(ui->spinRciPort->value());
//    settings.timeout = ui->spinTimeout->value();
//    m_Server.setRciSettings(settings);
//    quint16 port = static_cast<quint16>(ui->spinPort->value());
//    if (ui->cmbApp->currentIndex()) { // Active
//        if (!m_Server.listen(port)) {
//            qDebug() << "Cannot start";
//        }
//    } else {
//        m_Server.close();
//    }

}

/******************************************************************/

void SDPO::HMTelnetServiceDialog::on_btnInstall_clicked()
{

}

/******************************************************************/

void SDPO::HMTelnetServiceDialog::on_btnStart_clicked()
{

}

/******************************************************************/
