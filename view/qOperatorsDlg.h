#ifndef QOPERATORSDLG_H
#define QOPERATORSDLG_H

#include <QDialog>

namespace Ui {
class OperatorsDlg;
}

namespace SDPO {

class OperatorsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit OperatorsDlg(QWidget *parent = 0);
    ~OperatorsDlg();

private:
    Ui::OperatorsDlg *ui;
};

} // namespace SDPO

#endif // QOPERATORSDLG_H
