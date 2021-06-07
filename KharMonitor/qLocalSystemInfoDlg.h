/*!
 * \class SDPO::LocalSystemInfoDlg
 * \brief Displays information about the local computer
 *
 * Examines the local host and displays information about the local computer: processor, memory, Winsock data, etc
 * Some comments regarding counters that show memory status:
 *
 * <b>Total Physical</b>
 * The amount of actual physical memory installed on the system.
 *
 * <b>Avail Physical</b>
 * The amount of physical memory currently available.
 * This is the amount of physical memory that can be immediately reused without having to write its contents to disk first.
 *
 * <b>Total Page File</b>
 * The current size of the committed memory limit.
 * This is physical memory plus the size of the page file, minus a small overhead.
 *
 * <b>Avail Page File</b>
 * The maximum amount of memory the HostMonitor can commit.
 *
 * <b>Total Virtual</b>
 * The size of the user-mode portion of the virtual address space of the HostMonitor process.
 *
 * <b>Avail Virtual</b>
 * The amount of unreserved and uncommitted memory currently in the user-mode portion of the virtual address space of the HostMonitor process.
 */

#ifndef QLOCALSYSTEMINFODLG_H
#define QLOCALSYSTEMINFODLG_H

#include <QDialog>
#include <QPicture>

namespace Ui {
class LocalSystemInfoDlg;
}

namespace SDPO {

class LocalSystemInfoDlg : public QDialog
{
    Q_OBJECT

    Ui::LocalSystemInfoDlg *ui;
    int sizeX;
    int sizeY;
    int height;

public:
    explicit LocalSystemInfoDlg(QWidget *parent = nullptr);
    ~LocalSystemInfoDlg();

private slots:
    void init();

private:
    QPicture pie(double total, double value);
    QString localIP();
    bool isIPv6compatible();
    bool hasProxy();
    qint64 hddInfo(bool total);
};

} // namespace SDPO

#endif // QLOCALSYSTEMINFODLG_H
