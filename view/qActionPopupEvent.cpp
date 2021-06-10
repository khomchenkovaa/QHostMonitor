#include "qActionPopupEvent.h"
#include "ui_qActionPopupEvent.h"
#include "tTest.h"
#include "settings.h"

namespace SDPO {

/***********************************************/

ActionPopupEvent::ActionPopupEvent(TTest *test, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActionPopupEvent),
    m_test(test)
{
    ui->setupUi(this);
    setupProperties();
    if (m_autoClose) {
        m_timerId = startTimer(1000);
        ui->lblClock->setText(QString("This window will be closed in %1 sec").arg(m_closeAfter));
    } else {
        m_timerId = 0;
        ui->lblClock->setText(QString());
        ui->btnStop->setDisabled(true);
    }
}

/***********************************************/

ActionPopupEvent::~ActionPopupEvent()
{
    delete ui;
}

/***********************************************/

void ActionPopupEvent::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != m_timerId) return;
    if (m_closeAfter) {
        m_closeAfter--;
        ui->lblClock->setText(QString("This window will be closed in %1 sec").arg(m_closeAfter));
    } else {
        close();
    }
}

/***********************************************/

void ActionPopupEvent::on_btnStop_clicked()
{
    ui->lblClock->setText(QString());
    ui->btnStop->setDisabled(true);
    if (m_timerId) {
        killTimer(m_timerId);
    }
}

/***********************************************/

void ActionPopupEvent::setupProperties()
{
    ui->editFolder->setText(m_test->getPath());
    ui->editTest->setText(m_test->testName());
    ui->editMethod->setText(m_test->testedObjectInfo());
    ui->txtComment->setPlainText(m_test->getComment());
    ui->editTime->setText(m_test->testTime());
    ui->editStatus->setText(m_test->simpleStatus());
    ui->editReply->setText(m_test->getReply());

    QSettings s;
    m_closeAfter = s.value(SKEY_HOSTMON_MsgWinTime, 5).toInt();
    m_autoClose = (s.value(SKEY_HOSTMON_MsgWinCloseAuto, 5).toInt() == 1);
}

/***********************************************/

} // namespace SDPO


