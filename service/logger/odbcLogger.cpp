#include "odbcLogger.h"
#include "global/gMacroTranslator.h"
#include "tTest.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

namespace SDPO {

/***********************************************/

OdbcLogger::OdbcLogger(QObject *parent) :
    QObject(parent),
    m_isStarted(false),
    m_DB(QSqlDatabase::database("odbcLogger"))
{
    if (!m_DB.isValid()) {
        m_DB = QSqlDatabase::addDatabase("QODBC", "odbcLogger");
    }
}

/***********************************************/

OdbcLogger::~OdbcLogger()
{
    stopLog();
}

/***********************************************/

bool OdbcLogger::startLog(const QString& dbName, const QString& dbUser, const QString& dbPassword)
{
    if (!m_isStarted) {
        m_DB.setDatabaseName(dbName);
        m_DB.setUserName(dbUser);
        m_DB.setPassword(dbPassword);
        m_isStarted = m_DB.open();
        if (!m_isStarted) {
            qDebug() << "ODBC Open:" + m_DB.lastError().text();
        }
    }
    return m_isStarted;
}

/***********************************************/

void OdbcLogger::stopLog()
{
    if (m_isStarted) {
        m_DB.close();
        m_isStarted = false;
    }
}

/***********************************************/

bool OdbcLogger::log(TTest *test, QString dbQuery)
{
    if (!m_isStarted) {
        return false;
    }
    GMacroTranslator translator(dbQuery, test);
    QString sqlScript = translator.translate();
    QSqlQuery query(m_DB);
    bool result = query.exec(sqlScript);
    if (!result) {
        qDebug() << "ODBC query:" + query.lastError().text();
    }
    return result;
}

/***********************************************/

} // namespace SDPO
