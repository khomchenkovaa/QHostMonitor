#include "qHmlMain.h"
#include "ui_qHmlMain.h"
#include "qAboutDlg.h"

namespace SDPO {

HMLMain::HMLMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HMLMain)
{
    ui->setupUi(this);
}

HMLMain::~HMLMain()
{
    delete ui;
}

void HMLMain::on_actHelpAbout_triggered()
{
    AboutDlg aboutDlg;
    aboutDlg.exec();
}


void HMLMain::on_actExit_triggered()
{
    close();
}


} // namespace SDPO

