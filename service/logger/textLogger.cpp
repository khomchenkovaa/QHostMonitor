#include "textLogger.h"
#include "tTest.h"

namespace SDPO {

/***********************************************/

TextLogger::TextLogger(QObject *parent) :
    QObject(parent),
    m_isStarted(false),
    m_separator("\t")
{
}

/***********************************************/

TextLogger::~TextLogger()
{
    stopLog();
}

/***********************************************/

bool TextLogger::startLog(const QString &logFileName)
{
    if(!m_isStarted){
        m_logFile.setFileName(logFileName);
        if (m_logFile.open(QFile::WriteOnly | QFile::Append | QFile::Text)){
            m_outTextStream.setDevice(&m_logFile);
            m_isStarted = true;
        }
    }
    return m_isStarted;
}

/***********************************************/

void TextLogger::stopLog()
{
    if(m_isStarted){
        m_logFile.close();
        m_outTextStream.reset();
        m_isStarted = false;
    }
}

/***********************************************/

bool TextLogger::log(TTest *test)
{
    if (!m_isStarted) {
        return false;
    }
    m_outTextStream
             << QString("[%1]").arg(test->property("LastTestTime").toString())
             << m_separator << test->property("HostName").toString()
             << m_separator << test->property("Status").toString()
             << m_separator << test->property("Reply").toString()
             << m_separator << test->property("TestMethod").toString()
             << m_separator << test->property("TestID").toInt()
             << "\n";
    return true;
}

/***********************************************/

} // namespace SDPO
