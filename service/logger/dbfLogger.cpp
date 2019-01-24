#include "dbfLogger.h"
#include <QFile>
#include <QDebug>
#include "tTest.h"

namespace SDPO {

/***********************************************/

DbfLogger::DbfLogger(QObject *parent) :
    QObject(parent),
    m_isStarted(false),
    m_model()
{
}

/***********************************************/

DbfLogger::~DbfLogger()
{
    stopLog();
}

/***********************************************/

bool DbfLogger::startLog(const QString &logFileName)
{
    if(!m_isStarted){
        QFile dbFile(logFileName);
        if (!dbFile.exists()) {
            if (!createLogFile(logFileName)) {
                qDebug() << "DBF create: cannot copy logTemplate.dbf";
                return m_isStarted;
            }
        }
        if (!m_model.open(logFileName)) {
            qDebug() << "DBF open: cannot open file";
        } else {
            m_isStarted = true;
        }
    }
    return m_isStarted;
}

/***********************************************/

void DbfLogger::stopLog()
{
    if(m_isStarted){
        m_model.close();
        m_isStarted = false;
    }
}

/***********************************************/

bool DbfLogger::log(TTest *test)
{
    if (!m_isStarted) {
        return false;
    }

    int idx = m_model.rowCount();

    if (!m_model.insertRow(idx)) {
        return false;
    }

    bool result = true;
    result &= m_model.setData(m_model.index(idx, 0), test->getTestTime()); // date:D:8:0
    result &= m_model.setData(m_model.index(idx, 1), test->getTestTime().toString("hhmmss"));   // time:C:6:0
    result &= m_model.setData(m_model.index(idx, 2), QVariant(false));                          // SysMsg:L:1:0
    result &= m_model.setData(m_model.index(idx, 3), test->property("HostName"));               // host:C:60:0
    result &= m_model.setData(m_model.index(idx, 4), QVariant(test->statusID()));               // status_cod:N:6:0
    result &= m_model.setData(m_model.index(idx, 5), test->property("Status"));                 // status_str:C:20:0
    result &= m_model.setData(m_model.index(idx, 6), test->property("Reply"));                  // reply:C:15:0
    result &= m_model.setData(m_model.index(idx, 7), QVariant(0));                              // replytime:N:11:0
    result &= m_model.setData(m_model.index(idx, 8), QVariant(100500));                         // diskspace:N:20:0
    result &= m_model.setData(m_model.index(idx, 9), test->property("TestMethod"));             // testmethod:C:40:0
    result &= m_model.setData(m_model.index(idx,10), test->property("TestID"));                 // testid:N:11:0
    return result;
}

/***********************************************/

bool DbfLogger::createLogFile(const QString &logFileName)
{
    bool result = QFile::copy(":/resources/logTemplate.dbf", logFileName);
    if (result) {
        QFile(logFileName).setPermissions(QFileDevice::ReadOwner | QFileDevice::ReadGroup | QFileDevice::ReadOther
                                   | QFileDevice::WriteOwner | QFileDevice::WriteGroup);
    }
    return result;
}

/***********************************************/

} // namespace SDPO
