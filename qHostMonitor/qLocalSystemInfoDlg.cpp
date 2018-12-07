/**
  https://www.tecmint.com/commands-to-collect-system-and-hardware-information-in-linux/
 */


#include "qLocalSystemInfoDlg.h"
#include "ui_qLocalSystemInfoDlg.h"

#include "method/tDhcp.h"

#include <QtWidgets>
#include <QSysInfo>
#include <QHostInfo>
#include <QUdpSocket>

// Linux specific
#include <sys/sysinfo.h>

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

    QUdpSocket udpSocket;
    ui->valUdpSize->setText(QString::number(udpSocket.readBufferSize()));

    // Memory status
    ui->valTotalPhysical->setText("???");
    ui->valAvailPhysical->setText("???");
    ui->piePhysical->clear();
    ui->valTotalPageFile->setText("???");
    ui->valAvailPageFile->setText("???");
    ui->piePageFile->clear();
    ui->valTotalVirtual->setText("???");
    ui->valAvailVirtual->setText("???");
    ui->pieVirtual->clear();

    struct sysinfo sInfo;
    int res = sysinfo(&sInfo);
    if (!res) {
        ui->valTotalPhysical->setText(QString("%1 MB").arg(sInfo.totalram/1024/1024));
        ui->valAvailPhysical->setText(QString("%1 MB").arg(sInfo.freeram/1024/1024));
        ui->piePhysical->setPicture(pie(sInfo.totalram,sInfo.freeram));
        ui->valTotalPageFile->setText(QString("%1 MB").arg(sInfo.totalswap/1024/1024));
        ui->valAvailPageFile->setText(QString("%1 MB").arg(sInfo.freeswap/1024/1024));
        ui->piePageFile->setPicture(pie(sInfo.totalswap,sInfo.freeswap));
        ui->valTotalVirtual->setText(QString("%1 MB").arg(sInfo.totalhigh/1024/1024));
        ui->valAvailVirtual->setText(QString("%1 MB").arg(sInfo.freehigh/1024/1024));
        ui->pieVirtual->setPicture(pie(sInfo.totalhigh,sInfo.freehigh));
    }
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
