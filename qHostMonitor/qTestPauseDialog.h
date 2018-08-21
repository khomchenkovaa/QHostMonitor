#ifndef QTESTPAUSEDIALOG_H
#define QTESTPAUSEDIALOG_H

#include <QDialog>

namespace Ui {
class TestPauseDialog;
}

namespace SDPO {

class TestPauseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestPauseDialog(QWidget *parent = 0);
    ~TestPauseDialog();

private:
    Ui::TestPauseDialog *ui;
};

} // namespace SDPO

#endif // QTESTPAUSEDIALOG_H
