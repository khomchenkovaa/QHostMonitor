#ifndef QREPORTPROFILESDLG_H
#define QREPORTPROFILESDLG_H

#include <QDialog>

namespace Ui {
class ReportProfilesDlg;
}

namespace SDPO {

class ReportProfilesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ReportProfilesDlg(QWidget *parent = nullptr);
    ~ReportProfilesDlg();

private:
    Ui::ReportProfilesDlg *ui;
};

} // namespace SDPO

#endif // QREPORTPROFILESDLG_H
