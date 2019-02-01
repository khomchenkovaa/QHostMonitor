#ifndef QSNMPTRAPFILTERDLG_H
#define QSNMPTRAPFILTERDLG_H

#include <QDialog>

namespace Ui {
class SnmpTrapFilterDlg;
}

namespace SDPO {

class SnmpTrapFilterDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SnmpTrapFilterDlg(QWidget *parent = 0);
    ~SnmpTrapFilterDlg();

private:
    Ui::SnmpTrapFilterDlg *ui;
};

} // namespace SDPO

#endif // QSNMPTRAPFILTERDLG_H
