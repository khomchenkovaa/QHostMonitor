#include "ioFileExistsConverter.h"

namespace SDPO {

/***********************************************/

IOFileExistsConverter::IOFileExistsConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/***********************************************/

TestMethod *IOFileExistsConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TFileExists();
    }
    return m_TestMethod;
}

/***********************************************/

bool IOFileExistsConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::FileExists)) {
        return false;
    }
    TFileExists *test = qobject_cast<TFileExists*>(m_TestMethod);
    if (key == SP_FILE) {
        test->setFileName(value);
    } else if (key == SP_OK_IF_EXISTS) {
        test->setFileExistsCriteria(value == "Yes");
    } else if (key == SP_USE_MACROS) {
        test->setTranslateMacros(value == "Yes");
    } else if (key == SP_MAX_AGE) {
        test->setFileOlderFlag(true);
        test->setFileOlderValue(value.toInt());
    } else if (key == SP_MIN_AGE) {
        test->setFileNewerFlag(true);
        test->setFileNewerValue(value.toInt());
    } else {
        return false;
    }
    return true;
}

/***********************************************/

void IOFileExistsConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::FileExists)) {
        return;
    }
    TFileExists *test = qobject_cast<TFileExists*>(m_TestMethod);
    out << SP_FILE         << " = " << test->getFileName()                              << endl;
    out << SP_OK_IF_EXISTS << " = " << QString(test->isFileExistsCriteria()?"Yes":"No") << endl;
    out << SP_USE_MACROS   << " = " << QString(test->isTranslateMacros()?"Yes":"No")    << endl;
    if (test->isFileOlderFlag()) {
        out << SP_MAX_AGE  << " = " << test->getFileOlderValue() << endl;
    }
    if (test->isFileNewerFlag()) {
        out << SP_MIN_AGE  << " = " << test->getFileNewerValue() << endl;
    }
}

/***********************************************/

QJsonObject IOFileExistsConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::FileExists)) {
        return jsonObj;
    }
    TFileExists* test = qobject_cast<TFileExists*>(m_TestMethod);
    jsonObj.insert(SP_FILE, QJsonValue(test->getFileName()));
    jsonObj.insert(SP_OK_IF_EXISTS, QJsonValue(test->isFileExistsCriteria()));
    jsonObj.insert(SP_USE_MACROS, QJsonValue(test->isTranslateMacros()));
    if (test->isFileOlderFlag()) {
        jsonObj.insert(SP_MAX_AGE, QJsonValue(test->getFileOlderValue()));
        }
    if (test->isFileNewerFlag()) {
        jsonObj.insert(SP_MIN_AGE, QJsonValue(test->getFileNewerValue()));
        }
    return jsonObj;
}

/******************************************************************/

TestMethod *IOFileExistsConverter::fromJsonObject(QJsonObject jsonObj)
{
    TFileExists *test = qobject_cast<TFileExists*>(getTestMethod());
    test->setFileName(jsonObj.value(SP_FILE).toString());
    test->setFileExistsCriteria(jsonObj.value(SP_OK_IF_EXISTS).toBool());
    test->setTranslateMacros(jsonObj.value(SP_USE_MACROS).toBool());
    if (test->isFileOlderFlag()) {
        test->setFileOlderValue(jsonObj.value(SP_MAX_AGE).toInt());
        }
    if (test->isFileNewerFlag()) {
        test->setFileNewerValue(jsonObj.value(SP_MIN_AGE).toInt());
    }
    return test;
}

/******************************************************************/

} // namespace SDPO
