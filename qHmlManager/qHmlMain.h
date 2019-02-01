#ifndef QHMLMAIN_H
#define QHMLMAIN_H

#include <QMainWindow>

namespace Ui {
class HMLMain;
}

namespace SDPO {

class HMLMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit HMLMain(QWidget *parent = 0);
    ~HMLMain();

private slots:
    void on_actHelpAbout_triggered();

    void on_actExit_triggered();

private:
    Ui::HMLMain *ui;
};

} // namespace SDPO

#endif // QHMLMAIN_H
