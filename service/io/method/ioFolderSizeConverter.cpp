#include "ioFolderSizeConverter.h"

namespace SDPO {

/******************************************************************/

IOFolderSizeConverter::IOFolderSizeConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TestMethod *IOFolderSizeConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TFolderSize();
    }
    return m_TestMethod;
}

/******************************************************************/

bool IOFolderSizeConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::FileSize)) {
        return false;
    }
    TFolderSize *test = qobject_cast<TFolderSize*>(m_TestMethod);
    if (key == SP_FILE) {
        test->setPath(value);
    } else if (key == SP_SUBFOLDERS) {
        test->setIncludeSubfolders(value == "Yes");
    } else if (key == SP_USE_MACROS) {
        test->setTranslateMacros(value == "Yes");
    } else if (key == SP_MAX_SIZE) {
        QString size = value;
        test->setMaxSize(size.remove(QRegExp("[^\\d]+")).toLong());
        if (value.contains("K")) { // KB
            test->setDimension("KB");
        } else if (value.contains("M")) { // MB
            test->setDimension("MB");
        } else if (value.contains("G")) { // GB
            test->setDimension("GB");
        } else {
            test->setDimension("b");
        }
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOFolderSizeConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::FileSize)) {
        return;
    }
    TFolderSize *test = qobject_cast<TFolderSize*>(m_TestMethod);
    out << SP_FILE       << " = " << test->getPath()                                            << endl;
    out << SP_MAX_SIZE   << " = " << QString::number(test->getMaxSize()) + test->getDimension() << endl;
    out << SP_SUBFOLDERS << " = " << QString(test->isIncludeSubfolders()?"Yes":"No")            << endl;
    out << SP_USE_MACROS << " = " << QString(test->isTranslateMacros()?"Yes":"No")              << endl;
}

/******************************************************************/

QJsonObject IOFolderSizeConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::FileSize)) {
        return jsonObj;
    }
    TFolderSize* test = qobject_cast<TFolderSize*>(m_TestMethod);
    jsonObj.insert(SP_FILE, QJsonValue(test->getPath()));
    jsonObj.insert(SP_SUBFOLDERS, QJsonValue(test->isIncludeSubfolders()));
    jsonObj.insert(SP_USE_MACROS, QJsonValue(test->isTranslateMacros()));
    jsonObj.insert(SP_MAX_SIZE, QJsonValue(test->getMaxSize()));
    jsonObj.insert(SP_DIMENSION, QJsonValue(test->getDimension()));
    return jsonObj;
}

/******************************************************************/

TestMethod *IOFolderSizeConverter::fromJsonObject(QJsonObject jsonObj)
{
    TFolderSize *test = qobject_cast<TFolderSize*>(getTestMethod());
    test->setPath(jsonObj.value(SP_FILE).toString());
    test->setIncludeSubfolders(jsonObj.value(SP_SUBFOLDERS).toBool());
    test->setTranslateMacros(jsonObj.value(SP_USE_MACROS).toBool());
    test->setMaxSize(jsonObj.value(SP_MAX_SIZE).toInt());
    test->setDimension(jsonObj.value(SP_DIMENSION).toString());
    return test;
}

/******************************************************************/

} // namespace SDPO
