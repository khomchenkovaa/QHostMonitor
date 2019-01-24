/**
  https://www.tecmint.com/commands-to-collect-system-and-hardware-information-in-linux/
 */


#include "qLocalSystemInfoDlg.h"
#include "ui_qLocalSystemInfoDlg.h"

#include <QtWidgets>
#include <QSysInfo>
#include <QHostInfo>
#include <QUdpSocket>
#include <QNetworkInterface>

// Linux specific
#include <sys/sysinfo.h>
#include <unistd.h>

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
    ui->valProcNum->setText(QString::number(get_nprocs()));
    ui->valProcType->setText(QSysInfo::currentCpuArchitecture()); // system("cat /proc/cpuinfo | grep \"model name\"");
    ui->valPageSize->setText(QString::number(getpagesize()));
    ui->valAllocationGranularity->setText(QString::number(getpagesize())); // nearest equivalent of VirtualAlloc on Linux is mmap (the mapping will be created at a nearby page boundary).

    // System
    QUdpSocket udpSocket;
    ui->valHostName->setText(QHostInfo::localHostName());
    ui->valHostAdr->setText(localIP());
    ui->valShell->setText(getenv("SHELL"));
    ui->valDesktop->setText(getenv("DESKTOP_SESSION"));
    ui->valTotalHDD->setText(QString("%1 Gb").arg(hddInfo(true)/1024/1024/1024));
    ui->valAvailHDD->setText(QString("%1 Gb").arg(hddInfo(false)/1024/1024/1024));
    ui->valSocketMax->setText("???");
    ui->valUdpSize->setText(QString::number(udpSocket.readBufferSize()));

    // Memory status
    ui->valTotalPhysical->setText("???");
    ui->valAvailPhysical->setText("???");
    ui->piePhysical->clear();
    ui->valTotalSwap->setText("???");
    ui->valAvailSwap->setText("???");
    ui->pieSwap->clear();
    ui->valTotalHeigh->setText("???");
    ui->valAvailHeigh->setText("???");
    ui->pieHeigh->clear();

    struct sysinfo sInfo;
    int res = sysinfo(&sInfo);
    if (!res) {
        ui->valTotalPhysical->setText(QString("%1 MB").arg(sInfo.totalram/1024/1024));
        ui->valAvailPhysical->setText(QString("%1 MB").arg(sInfo.freeram/1024/1024));
        ui->piePhysical->setPicture(pie(sInfo.totalram,sInfo.freeram));
        ui->valTotalSwap->setText(QString("%1 MB").arg(sInfo.totalswap/1024/1024));
        ui->valAvailSwap->setText(QString("%1 MB").arg(sInfo.freeswap/1024/1024));
        ui->pieSwap->setPicture(pie(sInfo.totalswap,sInfo.freeswap));
        ui->valTotalHeigh->setText(QString("%1 MB").arg(sInfo.totalhigh/1024/1024));
        ui->valAvailHeigh->setText(QString("%1 MB").arg(sInfo.freehigh/1024/1024));
        ui->pieHeigh->setPicture(pie(sInfo.totalhigh,sInfo.freehigh));
    }

    // Network connection status
    ui->valConnection->setText("Unknown");
    ui->valUsesLan->setText("Unknown");
    ui->valUsesModem->setText("Unknown");
    ui->valUsesProxy->setText(hasProxy()?"Yes":"No");
    // IP v6
    ui->valIPv6->setText(isIPv6compatible()?"Yes":"No");
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

QString LocalSystemInfoDlg::localIP()
{
    foreach (const QNetworkInterface &netInterface, QNetworkInterface::allInterfaces()) {
        QNetworkInterface::InterfaceFlags flags = netInterface.flags();
        if( (bool)(flags & QNetworkInterface::IsRunning) && !(bool)(flags & QNetworkInterface::IsLoopBack)){
            foreach (const QNetworkAddressEntry &address, netInterface.addressEntries()) {
                if(address.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                    return address.ip().toString();
                }
            }
        }
    }
    return QString();
}

/******************************************************************/
/*!
 * Linux kernel has IPv6 support since 1996. All you need to do is compile kernel with IPv6 networking support.
 * However, there is easy way to find out if Linux kernel compiled with IPv6 or not.
 * To check, whether your current running kernel supports IPv6, take a look into your /proc-file-system. Following entry must exists:
 * $ cat /proc/net/if_inet6
 */
bool LocalSystemInfoDlg::isIPv6compatible()
{
    QString fName = "/proc/net/if_inet6";
    QFileInfo fileInfo(fName);
    return fileInfo.exists();
}

/******************************************************************/

bool LocalSystemInfoDlg::hasProxy()
{
    QString http = getenv("http_proxy");
    QString https = getenv("https_proxy");
    return !http.isEmpty() || !https.isEmpty();
}

/******************************************************************/

qint64 LocalSystemInfoDlg::hddInfo(bool total)
{
    qint64 result = 0;
    foreach(const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
        if (total) {
            result += storage.bytesTotal();
        } else {
            result += storage.bytesAvailable();
        }
    }
    return result;
}

/******************************************************************/

} // namespace SDPO
