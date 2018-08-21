#ifndef QACTIONPOPUPEVENT_H
#define QACTIONPOPUPEVENT_H

#include <QDialog>

namespace Ui {
class ActionPopupEvent;
}

namespace SDPO {

class TTest;

class ActionPopupEvent : public QDialog
{
    Q_OBJECT

public:
    explicit ActionPopupEvent(TTest *test, QWidget *parent = 0);
    ~ActionPopupEvent();

protected:
      void timerEvent(QTimerEvent *event);

private slots:
      void on_btnStop_clicked();

private:
    Ui::ActionPopupEvent *ui;
    TTest *m_test;

    int m_closeAfter;
    bool m_autoClose;
    int m_timerId;

    void setupProperties();
};

} // namespace SDPO

#endif // QACTIONPOPUPEVENT_H
