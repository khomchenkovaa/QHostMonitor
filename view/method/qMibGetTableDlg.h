#ifndef QMIBGETTABLEDLG_H
#define QMIBGETTABLEDLG_H

#include <QDialog>

namespace Ui {
class QMibGetTableDlg;
}

namespace SDPO {

class QMibGetTableDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QMibGetTableDlg(QWidget *parent = nullptr);
    ~QMibGetTableDlg();

    void setOid(const QString& oid);

private slots:
    void on_btnGet_clicked();

private:
    Ui::QMibGetTableDlg *ui;
};

} // namespace SDPO

#endif // QMIBGETTABLEDLG_H
