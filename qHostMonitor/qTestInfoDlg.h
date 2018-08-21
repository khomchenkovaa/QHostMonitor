#ifndef QTESTINFODLG_H
#define QTESTINFODLG_H

#include <QDialog>

namespace Ui {
class TestInfoDlg;
}

namespace SDPO {

class TestInfoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TestInfoDlg(QWidget *parent = 0);
    ~TestInfoDlg();

private slots:
    void on_btnTestHistory_clicked();

private:
    Ui::TestInfoDlg *ui;
};

} // namespace SDPO

#endif // QTESTINFODLG_H
