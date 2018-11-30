#include "qLocalSystemInfoDlg.h"
#include "ui_qLocalSystemInfoDlg.h"

#include "method/tDhcp.h"

#include <QtWidgets>
#include <QSysInfo>
#include <QHostInfo>

namespace SDPO {

/******************************************************************/

LocalSystemInfoDlg::LocalSystemInfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocalSystemInfoDlg)
{
    ui->setupUi(this);
    sizeX = 100;
    sizeY = 40;
    height = 15;

    init();
    connect(ui->btnRefresh, SIGNAL(clicked()), this, SLOT(init()));
    connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(reject()));
}

/******************************************************************/

LocalSystemInfoDlg::~LocalSystemInfoDlg()
{
    delete ui;
}

/******************************************************************/

void LocalSystemInfoDlg::init()
{
    QString osVersion = QSysInfo::prettyProductName()
        .append(" ").append(QSysInfo::kernelType())
        .append(" ").append(QSysInfo::kernelVersion());
    ui->valOsVersion->setText(osVersion);
    // CPU
    ui->valProcNum->setText(QString::number(sysconf(_SC_NPROCESSORS_ONLN)));
    ui->valProcType->setText(QSysInfo::currentCpuArchitecture()); // system("cat /proc/cpuinfo | grep \"model name\"");
    ui->valPageSize->setText(QString::number(sysconf(_SC_PAGESIZE)));
    ui->valAllocationGranularity->setText(QString::number(sysconf(_SC_PAGESIZE))); // nearest equivalent of VirtualAlloc on Linux is mmap (the mapping will be created at a nearby page boundary).
    ui->valAppAdrMin->setText("???");
    ui->valAppAdrMax->setText("???");
    // Socket
    ui->valHostName->setText(QHostInfo::localHostName());
    ui->valHostAdr->setText(TDhcp::currentLocalIP());
    ui->valSocketVer->setText(qVersion());
    ui->valDescription->setText("???");
    ui->valSysStatus->setText("???");
    ui->valIcmpImpl->setText("???");
    ui->valSocketMax->setText("???");
    ui->valUdpSize->setText("???");
    // Memory status
    ui->valTotalPhysical->setText("???");
    ui->valAvailPhysical->setText("???");
    ui->piePhysical->clear();
    ui->piePhysical->setPicture(pie(2038,1534));
    int pagesTotal = sysconf(_SC_PHYS_PAGES);
    int pagesAvail = sysconf(_SC_AVPHYS_PAGES);
    ui->valTotalPageFile->setText(QString::number(pagesTotal));
    ui->valAvailPageFile->setText(QString::number(pagesAvail));
    ui->piePageFile->clear();
    ui->piePageFile->setPicture(pie(pagesTotal,pagesAvail));
    ui->valTotalVirtual->setText("???");
    ui->valAvailVirtual->setText("???");
    ui->pieVirtual->clear();
    ui->pieVirtual->setPicture(pie(2048,1984));
    // Internet connection status
    ui->valConnection->setText("Unknown");
    ui->valUsesLan->setText("Unknown");
    ui->valUsesModem->setText("Unknown");
    ui->valUsesProxy->setText("Unknown");
    // IP v6
    ui->valIPv6->setText("Unknown");
}

/******************************************************************/

QPicture LocalSystemInfoDlg::pie(double total, double value)
{
    QPicture pi;
    QPainter p(&pi);

    p.setRenderHint(QPainter::Antialiasing);

    if (value > total) {
        value = total;
    }
    double angle = 360.0 * (total - value) / total;

    p.setPen(QPen(Qt::red, Qt::SolidLine));
    p.drawLine(0, sizeY / 2, 0, sizeY/2 + height);
    if (angle > 180.0) {
        p.drawLine(sizeX, sizeY / 2, sizeX, sizeY/2 + height);
        p.setPen(QPen(Qt::gray, Qt::SolidLine));
        p.setBrush(QBrush(Qt::red, Qt::SolidPattern));
        p.drawEllipse(0, height, sizeX, sizeY);
    } else {
        p.setPen(QPen(Qt::green, Qt::SolidLine));
        p.drawLine(sizeX, sizeY / 2, sizeX, sizeY/2 + height);
        p.setPen(QPen(Qt::gray, Qt::SolidLine));
        p.setBrush(QBrush(Qt::green, Qt::SolidPattern));
        p.drawEllipse(0, height, sizeX, sizeY);
        p.setBrush(QBrush(Qt::red, Qt::SolidPattern));
        p.drawChord(0, height, sizeX, sizeY, int((180 - angle) * 16), int(angle * 2 * 16));
    }

    p.setPen(QPen(Qt::gray, Qt::SolidLine));
    p.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    p.drawEllipse(0, 0, sizeX, sizeY);
    p.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    p.drawPie(0, 0, sizeX, sizeY, int(180 * 16), int(angle * 16));

    p.end();

    return pi;
}

/******************************************************************/

} // namespace SDPO
