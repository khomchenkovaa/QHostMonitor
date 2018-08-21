#ifndef QTRAFFICSNMPCREDENTIALSDLG_H
#define QTRAFFICSNMPCREDENTIALSDLG_H

#include <QDialog>

namespace Ui {
class TrafficSnmpCredentialsDlg;
}

namespace SDPO {

class TrafficSnmpCredentialsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TrafficSnmpCredentialsDlg(QWidget *parent = 0);
    ~TrafficSnmpCredentialsDlg();

private:
    Ui::TrafficSnmpCredentialsDlg *ui;
};

} // namespace SDPO
#endif // QTRAFFICSNMPCREDENTIALSDLG_H
