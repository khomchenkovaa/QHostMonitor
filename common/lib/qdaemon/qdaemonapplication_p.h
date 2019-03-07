#ifndef QDAEMONAPPLICATIONPRIVATE_H
#define QDAEMONAPPLICATIONPRIVATE_H

#include "qdaemonlog.h"

#include <QCommandLineParser>
#include <QCommandLineOption>

QT_BEGIN_NAMESPACE

namespace QtDaemon
{
    class QAbstractDaemonBackend;
}

class QDaemonApplication;
class QDaemonApplicationPrivate
{
    Q_DECLARE_PUBLIC(QDaemonApplication)
public:
    QDaemonApplicationPrivate(QDaemonApplication *);
    ~QDaemonApplicationPrivate();

private:
    int exec();

    static void processSignalHandler(int);

private:
    QtDaemon::QAbstractDaemonBackend * createBackend(bool);

private:
    QDaemonApplication * q_ptr;
    QDaemonLog log;
    bool autoQuit;
    QCommandLineParser parser;

    static QString description;
};

QT_END_NAMESPACE

#endif // QDAEMONAPPLICATIONPRIVATE_H
