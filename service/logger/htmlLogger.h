#ifndef HTMLLOGGER_H
#define HTMLLOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

namespace SDPO {

class TTest;

class HtmlLogger : public QObject
{
    Q_OBJECT

    bool m_isStarted;
    QFile m_logFile;
    QTextStream m_outTextStream;
public:
    explicit HtmlLogger(QObject *parent = 0);
    ~HtmlLogger();

    bool startLog(const QString &logFileName);
    void stopLog();

public slots:
    bool log(TTest* test);

private:
    void writeHead();
    void writeFooter();

};

} // namespace SDPO

#endif // HTMLLOGGER_H
