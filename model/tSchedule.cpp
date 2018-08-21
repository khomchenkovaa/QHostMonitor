#include "tSchedule.h"
#include "qcron/qcron.hpp"

namespace SDPO {

QStringList TSchedule::dayOfWeek = (QStringList() << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday" << "Saturday" << "Sunday");

/***********************************************/

TSchedule::TSchedule(QObject *parent) :
    QObject(parent)
{
    a_Mode = ScheduleMode::Regular;
    a_ScheduleName = QString();
    a_Interval = 600; // 10 min
    a_ScheduleDay = 2; // Tuesday or 2nd of month
    a_ScheduleTime = QTime(9,0,0);
    a_ScheduleExpr1 = QString();
    a_ScheduleExpr2 = QString();

    m_timer.setTimerType(Qt::VeryCoarseTimer);
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &TSchedule::activated);
    m_cron1 = m_cron2 = 0;
}

/***********************************************/

TSchedule::~TSchedule()
{
    if (m_cron1) delete m_cron1;
    if (m_cron2) delete m_cron2;
}

/***********************************************/

void TSchedule::setRegular(const int interval, const QString schedName)
{
    bool changed = false;
    if (a_Mode != TSchedule::Regular ) {
        a_Mode = TSchedule::Regular;
        changed = true;
    }
    if (a_Interval != interval) {
        a_Interval = interval;
        changed = true;
    }
    if (a_ScheduleName != schedName) {
        a_ScheduleName = schedName;
        changed = true;
    }
    if (changed) {
        start();
    }
}

/***********************************************/

void TSchedule::setOneTestPerDay(const QTime schedTime)
{
    bool changed = false;
    if (a_Mode != TSchedule::OneTestPerDay ) {
        a_Mode = TSchedule::OneTestPerDay;
        changed = true;
    }
    if (a_ScheduleTime != schedTime) {
        a_ScheduleTime = schedTime;
        changed = true;
    }
    if (changed) {
        start();
    }
}

/***********************************************/

void TSchedule::setOneTestPerWeek(const int weekDay, const QTime schedTime)
{
    bool changed = false;
    if (a_Mode != TSchedule::OneTestPerWeek ) {
        a_Mode = TSchedule::OneTestPerWeek;
        changed = true;
    }
    if (a_ScheduleDay != weekDay) {
        a_ScheduleDay = weekDay;
        changed = true;
    }
    if (a_ScheduleTime != schedTime) {
        a_ScheduleTime = schedTime;
        changed = true;
    }
    if (changed) {
        start();
    }
}

/***********************************************/

void TSchedule::setOneTestPerMonth(const int monthDay, const QTime schedTime)
{
    bool changed = false;
    if (a_Mode != TSchedule::OneTestPerMonth ) {
        a_Mode = TSchedule::OneTestPerMonth;
        changed = true;
    }
    if (a_ScheduleDay != monthDay) {
        a_ScheduleDay = monthDay;
        changed = true;
    }
    if (a_ScheduleTime != schedTime) {
        a_ScheduleTime = schedTime;
        changed = true;
    }
    if (changed) {
        start();
    }
}

/***********************************************/

void TSchedule::setByExpression(const QString expr1, const QString expr2)
{
    bool changed = false;
    if (a_Mode != TSchedule::ByExpression ) {
        a_Mode = TSchedule::ByExpression;
        changed = true;
    }
    if (a_ScheduleExpr1 != expr1) {
        a_ScheduleExpr1 = expr1;
        changed = true;
    }
    if (a_ScheduleExpr2 != expr2) {
        a_ScheduleExpr2 = expr2;
        changed = true;
    }
    if (changed) {
        start();
    }
}

/***********************************************/

QString TSchedule::intervalAsStr() const
{
    QString result;
    switch (a_Mode) {
    case ScheduleMode::Regular : {
        QTime time(0,0,0,0);
        QTime t = time.addSecs(a_Interval);
        result = t.toString("hh:mm:ss");
        } break;
    case ScheduleMode::OneTestPerDay :
        result = QString("Daily, at %1").arg(a_ScheduleTime.toString("hh:mm:ss"));
        break;
    case ScheduleMode::OneTestPerWeek :
        result = QString("Weekly, on %1").arg(dayOfWeek.at(a_ScheduleDay));
        break;
    case ScheduleMode::OneTestPerMonth :
        result = QString("Monthly,[%1] %2").arg(a_ScheduleDay).arg(a_ScheduleTime.toString("hh:mm:ss"));
        break;
    case ScheduleMode::ByExpression :
        if (!a_ScheduleExpr1.isEmpty() && !a_ScheduleExpr2.isEmpty()) {
            result = QString("[%1,%2]").arg(a_ScheduleExpr1).arg(a_ScheduleExpr2);
        } else {
            if (!a_ScheduleExpr1.isEmpty()) result = QString("[%1]").arg(a_ScheduleExpr1);
            if (!a_ScheduleExpr2.isEmpty()) result = QString("[%1]").arg(a_ScheduleExpr2);
        }
        break;
    }
    return result;
}

/***********************************************/

QString TSchedule::scheduleModeAsString() const
{
    switch (a_Mode) {
    case ScheduleMode::Regular : return "Regular";
    case ScheduleMode::OneTestPerDay : return "OneTestPerDay";
    case ScheduleMode::OneTestPerWeek : return "OneTestPerWeek";
    case ScheduleMode::OneTestPerMonth : return "OneTestPerMonth";
    case ScheduleMode::ByExpression : return "ByExpression";
    }
    return QString();
}

/***********************************************/

void TSchedule::start()
{
    stop();
    QString pattern;
    switch (a_Mode) {
    case ScheduleMode::Regular : startTimer(); break;
    case ScheduleMode::OneTestPerDay :
        pattern = QString("%1 %2 * * * *").arg(a_ScheduleTime.minute()).arg(a_ScheduleTime.hour());
        m_cron1 = startCron(pattern);
        break;
    case ScheduleMode::OneTestPerWeek :
        pattern = QString("%1 %2 * * %3 *").arg(a_ScheduleTime.minute()).arg(a_ScheduleTime.hour()).arg(a_ScheduleDay+1);
        m_cron1 = startCron(pattern);
        break;
    case ScheduleMode::OneTestPerMonth :
        pattern = QString("%1 %2 %3 * * *").arg(a_ScheduleTime.minute()).arg(a_ScheduleTime.hour()).arg(a_ScheduleDay+1);
        m_cron1 = startCron(pattern);
        break;
    case ScheduleMode::ByExpression :
        if (!a_ScheduleExpr1.isEmpty()) m_cron1 = startCron(a_ScheduleExpr1);
        if (!a_ScheduleExpr2.isEmpty()) m_cron2 = startCron(a_ScheduleExpr2);
        break;
    }
}

/***********************************************/

void TSchedule::stop()
{
    if (m_timer.isActive()) {
        m_timer.stop();
    }
    if (m_cron1) {
        disconnect(m_cron1, &QCron::activated, this, &TSchedule::activated);
        delete m_cron1;
        m_cron1 = 0;
    }
    if (m_cron2) {
        disconnect(m_cron2, &QCron::activated, this, &TSchedule::activated);
        delete m_cron2;
        m_cron2 = 0;
    }
}

/***********************************************/

QCron *TSchedule::startCron(const QString pattern)
{
    QCron *cron = new QCron(pattern);
    if (!cron->isValid()) {
        qDebug() << "Cron" << scheduleModeAsString() << "invalid:" << cron->error();
    }
    connect(cron, &QCron::activated, this, &TSchedule::activated);
    qDebug() << "Cron:" << scheduleModeAsString() << "pattern:" << pattern << "status:" << cron->isValid();
    return cron;
}

/***********************************************/

void TSchedule::startTimer()
{
    m_timer.start(a_Interval * 1000);
}

/***********************************************/

} // namespace SDPO
