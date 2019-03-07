#include "qdaemonlog_p.h"
#include "qdaemonlog.h"

#include <QtCore/qcoreapplication.h>
#include <QtCore/qdatetime.h>
#include <QtCore/qdir.h>
#include <QtCore/qfileinfo.h>

QT_BEGIN_NAMESPACE

QDaemonLog * QDaemonLogPrivate::logger = nullptr;

QDaemonLogPrivate::QDaemonLogPrivate()
    : logStream(&logFile), logType(QDaemonLog::LogToStdout)
{
    // Get the log file path
    QFileInfo info(QCoreApplication::applicationFilePath());
    logFilePath = info.absoluteDir().filePath(info.completeBaseName() + QStringLiteral(".log"));

    // Open the default stdout logging
    if (Q_UNLIKELY(!logFile.open(stdout, QFile::WriteOnly | QFile::Text)))
        qWarning("Error while trying to open the standard output. Giving up!");
}

QDaemonLogPrivate::~QDaemonLogPrivate()
{
    logStream.flush();
    logFile.close();
}

void QDaemonLogPrivate::write(const QString & message, QDaemonLog::EntrySeverity severity)
{
    static const QString noticeEntry = QStringLiteral("%1 %2");
    static const QString warningEntry = QStringLiteral("%1 Warning: %2");
    static const QString errorEntry = QStringLiteral("%1 Error: %2");

    QString formattedMessage, date = QDateTime::currentDateTime().toString(Qt::ISODate);
    switch (severity)
    {
    case QDaemonLog::ErrorEntry:
        formattedMessage = errorEntry.arg(date).arg(message);
        break;
    case QDaemonLog::WarningEntry:
        formattedMessage = warningEntry.arg(date).arg(message);
        break;
    case QDaemonLog::NoticeEntry:
        formattedMessage = noticeEntry.arg(date).arg(message);
    }

    logStream << formattedMessage << endl;
}

QT_END_NAMESPACE
