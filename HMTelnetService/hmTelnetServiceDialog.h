#ifndef HMTELNETSERVICEDIALOG_H
#define HMTELNETSERVICEDIALOG_H

#include <QDialog>

namespace Ui {
class HMTelnetServiceDialog;
}

namespace SDPO {

class HMTelnetServiceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HMTelnetServiceDialog(QWidget *parent = nullptr);
    ~HMTelnetServiceDialog();

private slots:
    void on_btnApply_clicked();
    void on_btnInstall_clicked();
    void on_btnStart_clicked();

private:
    Ui::HMTelnetServiceDialog *ui;
};

} // namespace SDPO

#endif // HMTELNETSERVICEDIALOG_H
