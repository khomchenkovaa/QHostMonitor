#ifndef QMIBGETVALUEDLG_H
#define QMIBGETVALUEDLG_H

#include <QDialog>

namespace Ui {
class QMibGetValueDlg;
}

namespace SDPO {

class QMibGetValueDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QMibGetValueDlg(QWidget *parent = nullptr);
    ~QMibGetValueDlg();

    void setOid(const QString& oid);

private slots:
    void on_btnSysInfo_clicked();
    void on_btnGet_clicked();
    void on_btnGetRow_clicked();
    void on_btnGetNext_clicked();

    void on_btnSet_clicked();

    void on_btnProfile_clicked();

private:
    Ui::QMibGetValueDlg *ui;
};

} // namespace SDPO

#endif // QMIBGETVALUEDLG_H
