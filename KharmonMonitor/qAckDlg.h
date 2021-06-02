#ifndef QACKDLG_H
#define QACKDLG_H

#include <QDialog>

namespace Ui {
class AckDlg;
}

namespace SDPO {

class AckDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AckDlg(QWidget *parent = 0);
    ~AckDlg();

    void init();

private:
    Ui::AckDlg *ui;
    bool append;
};

} // namespace SDPO

#endif // QACKDLG_H
