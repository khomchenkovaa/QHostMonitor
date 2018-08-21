#include "ioODBCConverter.h"

namespace SDPO {

/******************************************************************/

IOODBCConverter::IOODBCConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
    m_criteriaMode << "LessThan" << "MoreThan" << "EqualTo" << "DifferentFrom" << "Contains" << "Does not contain";
}

/******************************************************************/

TTestMethod *IOODBCConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TOdbcQuery();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOODBCConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::ODBC)) {
        return false;
    }
    TOdbcQuery *test = qobject_cast<TOdbcQuery*>(m_TestMethod);
    if (key == SP_DATASOURCE) {
        test->setDataSource(value);
    } else if (key == SP_LOGIN) {
        test->setLogin(value);
    } else if (key == SP_PASSWORD) {
        test->setPassword(value);
    } else if (key == SP_TIMEOUT) {
        test->setTimeout(value.toInt());
    } else if (key == SP_SQLQUERY) {
        test->setSqlQuery(value);
    } else if (key == SP_CHECKFIELD) {
        int crMode = m_criteriaMode.indexOf(value);
        test->setCriteriaMode( crMode == -1 ? 0 : crMode );
    } else if (key == SP_FIELDROW) {
        test->setAlertRow(value.toInt());
    } else if (key == SP_FIELDCOL) {
        test->setAlertCol(value.toInt());
    } else if (key == SP_VALUE) {
        test->setCriteriaValue(value);
    } else if (key == SP_EMPTYSTATUS) {
        test->setExecuteQuery(value.toInt() == 1);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOODBCConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::ODBC)) {
        return;
    }
    TOdbcQuery *test = qobject_cast<TOdbcQuery*>(m_TestMethod);
    out << SP_DATASOURCE   << " = " << test->getDataSource()                       << endl;
    out << SP_LOGIN        << " = " << test->getLogin()                            << endl;
    out << SP_PASSWORD     << " = " << test->getPassword()                         << endl;
    out << SP_TIMEOUT      << " = " << test->getTimeout()                          << endl;
    out << SP_SQLQUERY     << " = " << test->getSqlQuery()                         << endl;
    out << SP_CHECKFIELD   << " = " << m_criteriaMode.at(test->getCriteriaMode())  << endl;
    out << SP_FIELDROW     << " = " << test->getAlertRow()                         << endl;
    out << SP_FIELDCOL     << " = " << test->getAlertCol()                         << endl;
    out << SP_VALUE        << " = " << test->getCriteriaValue()                    << endl;
    out << SP_EMPTYSTATUS  << " = " << QString::number(test->isExecuteQuery()?1:0) << endl;
}
/******************************************************************/

} //namespace SDPO
