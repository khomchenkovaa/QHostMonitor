#ifndef MONITORINGTASK_H
#define MONITORINGTASK_H

#include <QObject>
#include <QRunnable>
#include "method/tTestMethod.h"

class MonitoringTask : public QObject, public QRunnable
{
    Q_OBJECT

    SDPO::TTestMethod *m_testMethod;
    bool m_canceled;
public:
    explicit MonitoringTask(SDPO::TTestMethod *testMethod, QObject *parent = 0);

    void run(); // QRunnable interface
signals:

public slots:
    void canceled();


};

#endif // MONITORINGTASK_H
