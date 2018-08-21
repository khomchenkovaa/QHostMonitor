#ifndef QLOGINASDLG_H
#define QLOGINASDLG_H

#include <QDialog>

namespace Ui {
class LoginAsDlg;
}

namespace SDPO {

class LoginAsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginAsDlg(QWidget *parent = 0);
    ~LoginAsDlg();

private:
    Ui::LoginAsDlg *ui;
};

} // namespace SDPO

#endif // QLOGINASDLG_H
