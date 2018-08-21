#ifndef TSCHEDULE_H
#define TSCHEDULE_H

#include <QString>
#include <QTime>
#include <QTimer>
#include "PropertyHelper.h"
#include "tEnums.h"

namespace SDPO {

class QCron;

class TSchedule : public QObject
{
    Q_OBJECT

    QTimer m_timer;
    QCron *m_cron1;
    QCron *m_cron2;

public:
    enum ScheduleMode {
        Regular,
        OneTestPerDay,
        OneTestPerWeek,
        OneTestPerMonth,
        ByExpression
    };
    Q_ENUM(ScheduleMode)

private:
    AUTO_PROPERTY(ScheduleMode, Mode)
    //! TODO Schedule for regular mode
    AUTO_PROPERTY(QString, ScheduleName)     //!stub
    AUTO_PROPERTY(int, Interval)
    AUTO_PROPERTY(int, ScheduleDay)
    AUTO_PROPERTY(QTime, ScheduleTime)
    AUTO_PROPERTY(QString, ScheduleExpr1)
    AUTO_PROPERTY(QString, ScheduleExpr2)

public:
    explicit TSchedule(QObject *parent = 0);
    ~TSchedule();

    void setRegular(const int interval, const QString schedName);
    void setOneTestPerDay(const QTime schedTime);
    void setOneTestPerWeek(const int weekDay, const QTime schedTime);
    void setOneTestPerMonth(const int monthDay, const QTime schedTime);
    void setByExpression(const QString expr1, const QString expr2);

    QString intervalAsStr() const;
    QString scheduleModeAsString() const;
signals:
    void activated();

public slots:
    void start();
    void stop();

private:
    void startTimer();
    QCron * startCron(const QString pattern);
    static QStringList dayOfWeek;

};

} // namespace SDPO

#endif // TSCHEDULE_H
