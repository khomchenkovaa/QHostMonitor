#ifndef MONITORINGTASK_H
#define MONITORINGTASK_H

#include <QObject>
#include <QRunnable>
#include "method/testmethod.h"

class MonitoringTask : public QObject, public QRunnable
{
    Q_OBJECT

    SDPO::TestMethod *m_TestMethod;
    bool m_Canceled;
public:
    explicit MonitoringTask(SDPO::TestMethod *testMethod, QObject *parent = 0);

    void run(); // QRunnable interface
signals:

public slots:
    void canceled();


};

#endif // MONITORINGTASK_H
