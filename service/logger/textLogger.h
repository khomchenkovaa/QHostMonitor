#ifndef TEXTLOGGER_H
#define TEXTLOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

namespace SDPO {

class TTest;

class TextLogger : public QObject
{
    Q_OBJECT

    bool m_isStarted;
    QFile m_logFile;
    QTextStream m_outTextStream;
    QString m_separator;
public:
    explicit TextLogger(QObject *parent = 0);
    ~TextLogger();

    bool startLog(const QString &logFileName);
    void stopLog();
    void setSeparator(const QString value) { m_separator = value; }

public slots:
    bool log(TTest* test);

};

} // namespace SDPO

#endif // TEXTLOGGER_H
