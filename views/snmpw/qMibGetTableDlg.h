#ifndef QMIBGETTABLEDLG_H
#define QMIBGETTABLEDLG_H

#include <QDialog>

namespace Ui {
class QMibGetTableDlg;
}

namespace SDPO {

class SnmpTableModel;

class QMibGetTableDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QMibGetTableDlg(QWidget *parent = nullptr);
    ~QMibGetTableDlg();

    void setOid(const QString& oid);

private slots:
    void on_btnGet_clicked();

    void on_btnProfile_clicked();

private:
    Ui::QMibGetTableDlg *ui;
    SnmpTableModel *model;
};

} // namespace SDPO

#endif // QMIBGETTABLEDLG_H
