#ifndef QCONNECTIONMANAGERDLG_H
#define QCONNECTIONMANAGERDLG_H

#include <QDialog>

namespace Ui {
class ConnectionManagerDlg;
}

namespace SDPO {

class ConnectionManagerDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionManagerDlg(QWidget *parent = 0);
    ~ConnectionManagerDlg();

private:
    Ui::ConnectionManagerDlg *ui;
};

} // namespace SDPO

#endif // QCONNECTIONMANAGERDLG_H
