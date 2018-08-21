#ifndef QSERVICETOMONITORDLG_H
#define QSERVICETOMONITORDLG_H

#include <QDialog>

namespace Ui {
class ServiceToMonitorDlg;
}

namespace SDPO {

class ServiceToMonitorDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ServiceToMonitorDlg(QWidget *parent = 0);
    ~ServiceToMonitorDlg();

private:
    Ui::ServiceToMonitorDlg *ui;
};

} // namespace SDPO

#endif // QSERVICETOMONITORDLG_H
