#include "ioShellScriptConverter.h"

namespace SDPO {

/******************************************************************/

IOShellScriptConverter::IOShellScriptConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TestMethod *IOShellScriptConverter::getTestMethod()
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

QJsonObject IOShellScriptConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::ShellScript)) {
        return jsonObj;
    }
    TShellScript* test = qobject_cast<TShellScript*>(m_TestMethod);
    jsonObj.insert(SP_SCRIPT, QJsonValue(test->getName()));
    jsonObj.insert(SP_PARAMS, QJsonValue(test->getParams()));
    jsonObj.insert(SP_TIMEOUT, QJsonValue(test->getTimeout()));
    jsonObj.insert(SP_USE_MACROS, QJsonValue(test->isTranslateMacros()));
    return jsonObj;
}

/******************************************************************/

TestMethod *IOShellScriptConverter::fromJsonObject(QJsonObject jsonObj)
{
    TShellScript *test = qobject_cast<TShellScript*>(getTestMethod());
    test->setName(jsonObj.value(SP_SCRIPT).toString());
    test->setParams(jsonObj.value(SP_PARAMS).toString());
    test->setTimeout(jsonObj.value(SP_TIMEOUT).toInt());
    test->setTranslateMacros(jsonObj.value(SP_USE_MACROS).toBool());
    return test;
}
/******************************************************************/

} // namespace SDPO
