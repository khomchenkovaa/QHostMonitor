#ifndef QTESTPLANNEDPAUSEDLG_H
#define QTESTPLANNEDPAUSEDLG_H

#include <QDialog>

namespace Ui {
class TestPlannedPauseDlg;
}

namespace SDPO {

class TestPlannedPauseDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TestPlannedPauseDlg(QWidget *parent = 0);
    ~TestPlannedPauseDlg();

private:
    Ui::TestPlannedPauseDlg *ui;
};

} // namespace SDPO

#endif // QTESTPLANNEDPAUSEDLG_H
