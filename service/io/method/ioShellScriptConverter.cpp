#include "ioShellScriptConverter.h"

namespace SDPO {

/******************************************************************/

IOShellScriptConverter::IOShellScriptConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOShellScriptConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TShellScript();
    }
    return m_TestMethod;
}

/******************************************************************/

bool IOShellScriptConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::ShellScript)) {
        return false;
    }
    TShellScript *test = qobject_cast<TShellScript*>(m_TestMethod);
    if (key == SP_SCRIPT) {
        //! TODO get Name, Platform, etc from script
        QStringList scriptProps = value.split("||");
        if (scriptProps.count() > 1) test->setPlatform(scriptProps.at(1));
        if (scriptProps.count() > 0) {
            QString name = scriptProps.at(0);
            test->setName(name);
            //! TODO find script by name
        }
    } else if (key == SP_PARAMS) {
        test->setParams(value);
    } else if (key == SP_TIMEOUT) {
        test->setTimeout(value.toInt());
    } else if (key == SP_USE_MACROS) {
        test->setTranslateMacros(value == "Yes");
    } else {
        return false;
    }
    return true;

}

/******************************************************************/

void IOShellScriptConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::ShellScript)) {
        return;
    }
    TShellScript *test = qobject_cast<TShellScript*>(m_TestMethod);
    out << SP_SCRIPT     << " = " << test->getName() << "||" << test->getPlatform() << endl;
    out << SP_PARAMS     << " = " << test->getParams()                              << endl;
    out << SP_TIMEOUT    << " = " << test->getTimeout()                             << endl;
    out << SP_USE_MACROS << " = " << QString(test->isTranslateMacros()?"Yes":"No")  << endl;
}

/******************************************************************/

} // namespace SDPO
