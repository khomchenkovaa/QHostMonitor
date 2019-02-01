#ifndef ACTIONTASK_H
#define ACTIONTASK_H

#include <QObject>
#include <QRunnable>

namespace SDPO {

class TTest;
class TestAction;

class ActionTask : public QObject, public QRunnable
{
    Q_OBJECT

    TTest *m_test;
    TestAction *m_action;

public:
    explicit ActionTask(TTest *test, TestAction *act, QObject *parent=0 );

    void run(); // QRunnable interface
};

} // namespace SDPO

#endif // ACTIONTASK_H
