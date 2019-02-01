#ifndef QTRAFFICNETWORKINTERFACEDLG_H
#define QTRAFFICNETWORKINTERFACEDLG_H

#include <QDialog>

namespace Ui {
class TrafficNetworkInterfaceDlg;
}

namespace SDPO {

class TrafficNetworkInterfaceDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TrafficNetworkInterfaceDlg(QWidget *parent = 0);
    ~TrafficNetworkInterfaceDlg();

private:
    Ui::TrafficNetworkInterfaceDlg *ui;
};

} // namespace SDPO
#endif // QTRAFFICNETWORKINTERFACEDLG_H
