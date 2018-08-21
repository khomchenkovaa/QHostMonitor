#include "ioExternalPrgConverter.h"

namespace SDPO {

/******************************************************************/

IOExternalPrgConverter::IOExternalPrgConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
    m_alertMode << "LessThan" << "MoreThan" << "EqualTo" << "DifferentFrom";
    m_windowMode << "shownormal" << "hide" << "maximized" << "minimized" << "snowminnoactivate" << "shownoactivate";
}

/******************************************************************/

TTestMethod *IOExternalPrgConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TExternalPrg();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOExternalPrgConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Externalprg)) {
        return false;
    }
    TExternalPrg *test = qobject_cast<TExternalPrg*>(m_TestMethod);
    if (key == SP_COMMANDLINE) {
        test->setExternalPrg(value);
    } else if (key == SP_ERRORLEVEL) {
        test->setExitCode(value.toInt());
    } else if (key == SP_CONDITION) {
        int crMode = m_alertMode.indexOf(value);
        test->setAlertMode( crMode == -1 ? 0 : crMode );
    } else if (key == SP_WINDOWMODE) {
        int crWMode = m_windowMode.indexOf(value);
        test->setWinMode( crWMode == -1 ? 0 : crWMode);
    } else if (key == SP_KILLAFTER) {
        test->setKillTimeout(value.toInt());
        test->setKillPrg(true);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOExternalPrgConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Externalprg)) {
        return;
    }
    TExternalPrg *test = qobject_cast<TExternalPrg*>(m_TestMethod);
    out << SP_COMMANDLINE << " = " << test->getExternalPrg()                 << endl;
    out << SP_ERRORLEVEL  << " = " << test->getExitCode()                    << endl;
    out << SP_CONDITION   << " = " << m_alertMode.at(test->getAlertMode())   << endl;
    out << SP_WINDOWMODE  << " = " << m_windowMode.at(test->getWinMode())    << endl;
    if (test->isKillPrg()) {
        out << SP_KILLAFTER << " = " << test->getKillTimeout()               << endl;
    }
}
/******************************************************************/

} //namespace SDPO
