#include "ioActiveScriptConverter.h"

namespace SDPO {

/******************************************************************/

IOActiveScriptConverter::IOActiveScriptConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TestMethod *IOActiveScriptConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TActiveScript();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOActiveScriptConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Script)) {
        return false;
    }
    TActiveScript *test = qobject_cast<TActiveScript*>(m_TestMethod);
    if (key == SP_SCRIPTCRITERIA) {
        test->setScriptCriteria(value == "Yes");
    } else if (key == SP_FILESCRIPT) {
        test->setFileScript(value);
    } else if (key == SP_LANGUAGE) {
        test->setLanguage(value);
    } else if (key == SP_ALLOWUI) {
        test->setAllowUi(value == "Yes");
    } else if (key == SP_TIMEOUT) {
        test->setTimeout(value.toInt());
    } else if (key == SP_TRANSLATEMACROS) {
        test->setTranslateMacros(value == "Yes");
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOActiveScriptConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Script)) {
        return;
    }
    TActiveScript*test = qobject_cast<TActiveScript*>(m_TestMethod);
    out << SP_SCRIPTCRITERIA     << " = " << test->isScriptCriteria()   << endl;
    out << SP_FILESCRIPT         << " = " << test->getFileScript()      << endl;
    out << SP_LANGUAGE           << " = " << test->getLanguage()        << endl;
    out << SP_ALLOWUI            << " = " << test->isAllowUi()          << endl;
    out << SP_TIMEOUT            << " = " << test->getTimeout()         << endl;
    out << SP_TRANSLATEMACROS    << " = " << test->isTranslateMacros()  << endl;
}

/******************************************************************/

QJsonObject IOActiveScriptConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Script)) {
        return jsonObj;
    }
    TActiveScript* test = qobject_cast<TActiveScript*>(m_TestMethod);
    jsonObj.insert(SP_SCRIPTCRITERIA, QJsonValue(test->isScriptCriteria()));
    jsonObj.insert(SP_FILESCRIPT, QJsonValue(test->getFileScript()));
    jsonObj.insert(SP_LANGUAGE, QJsonValue(test->getLanguage()));
    jsonObj.insert(SP_ALLOWUI, QJsonValue(test->isAllowUi()));
    jsonObj.insert(SP_TIMEOUT, QJsonValue(test->getTimeout()));
    jsonObj.insert(SP_TRANSLATEMACROS, QJsonValue(test->isTranslateMacros()));
    return jsonObj;
}

/******************************************************************/

TestMethod *IOActiveScriptConverter::fromJsonObject(QJsonObject jsonObj)
{
    TActiveScript *test = qobject_cast<TActiveScript*>(getTestMethod());
    test->setScriptCriteria(jsonObj.value(SP_SCRIPTCRITERIA).toBool());
    test->setFileScript(jsonObj.value(SP_FILESCRIPT).toString());
    test->setLanguage(jsonObj.value(SP_LANGUAGE).toString());
    test->setAllowUi(jsonObj.value(SP_ALLOWUI).toBool());
    test->setTimeout(jsonObj.value(SP_TIMEOUT).toInt());
    test->setTranslateMacros(jsonObj.value(SP_TRANSLATEMACROS).toBool());
    return test;
}

/******************************************************************/

} //namespace SDPO
