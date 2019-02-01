#ifndef QABOUTDLG_H
#define QABOUTDLG_H

#include <QDialog>

namespace Ui {
    class AboutDlg;
}

namespace SDPO {

class AboutDlg : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDlg(QWidget *parent = 0);
    ~AboutDlg();

private:
    Ui::AboutDlg *ui;

};

} // namespace SDPO

#endif // QABOUTDLG_H
