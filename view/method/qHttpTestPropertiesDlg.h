#ifndef QHTTPTESTPROPERTIESDLG_H
#define QHTTPTESTPROPERTIESDLG_H

#include <QDialog>

namespace Ui {
class HttpTestPropertiesDlg;
}

namespace SDPO {

class HttpTestPropertiesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HttpTestPropertiesDlg(QWidget *parent = 0);
    ~HttpTestPropertiesDlg();

private slots:
    void on_btnProxy_clicked();

private:
    Ui::HttpTestPropertiesDlg *ui;
};

} // namespace SDPO

#endif // QHTTPTESTPROPERTIESDLG_H
