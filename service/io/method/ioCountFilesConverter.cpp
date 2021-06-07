#include "ioCountFilesConverter.h"

namespace SDPO {

/******************************************************************/

IOCountFilesConverter::IOCountFilesConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
    int idx = TCompareFiles::staticMetaObject.indexOfEnumerator("CountCondition");
    m_CountConditionEnum = TCompareFiles::staticMetaObject.enumerator(idx);
}

/******************************************************************/

TestMethod *IOCountFilesConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TCountFiles();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOCountFilesConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::CountFiles)) {
        return false;
    }
    TCountFiles *test = qobject_cast<TCountFiles*>(m_TestMethod);
    if (key == SP_FOLDER) {
        test->setFolder(value);
    } else if (key == SP_MASK) {
        test->setFileNameMask(value);
    } else if (key == SP_SUBFOLDERS) {
        test->setIncludeSybFolder(value == "Yes");
    } else if (key == SP_USE_MACROS) {
        test->setTranslateMacros(value == "Yes");
    } else if (key == SP_COUNTMODE) {
        TCountFiles::CountCondition condition = (TCountFiles::CountCondition) m_CountConditionEnum.keyToValue(value.toStdString().data());
        test->setCondition(condition);
    } else if (key == SP_COUNTVALUE) {
        test->setCountValue(value.toInt());
    } else if (key == SP_FILESLIMIT) {
        test->setAlertWhen(value.toInt());
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOCountFilesConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::CountFiles)) {
        return;
    }
    TCountFiles* test = qobject_cast<TCountFiles*>(m_TestMethod);
    out << SP_FOLDER     << " = " << test->getFolder()                              << endl;
    out << SP_MASK       << " = " << test->getFileNameMask()                        << endl;
    out << SP_SUBFOLDERS << " = " << (test->isIncludeSybFolder()?"Yes":"No")        << endl;
    out << SP_USE_MACROS << " = " << (test->isTranslateMacros()?"Yes":"No")         << endl;
    out << SP_COUNTMODE  << " = " << m_CountConditionEnum.key(test->getCondition()) << endl;
    out << SP_COUNTVALUE << " = " << test->getCountValue()                          << endl;
    out << SP_FILESLIMIT << " = " << test->getAlertWhen()                           << endl;

}

/******************************************************************/

QJsonObject IOCountFilesConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::CountFiles)) {
        return jsonObj;
    }
    TCountFiles* test = qobject_cast<TCountFiles*>(m_TestMethod);
    jsonObj.insert(SP_FOLDER, QJsonValue(test->getFolder()));
    jsonObj.insert(SP_MASK, QJsonValue(test->getFileNameMask()));
    jsonObj.insert(SP_SUBFOLDERS, QJsonValue(test->isIncludeSybFolder()));
    jsonObj.insert(SP_USE_MACROS, QJsonValue(test->isTranslateMacros()));
    TCountFiles::CountCondition condition = test->getCondition();
    jsonObj.insert(SP_COUNTMODE, QJsonValue(m_CountConditionEnum.key(condition)));
    if (condition != TCountFiles::AllFiles && condition != TCountFiles::SubfolderOnly) {
        jsonObj.insert(SP_COUNTVALUE, QJsonValue(test->getCountValue()));
    }
    jsonObj.insert(SP_FILESLIMIT, QJsonValue(test->getAlertWhen()));
    return jsonObj;
}

/******************************************************************/

TestMethod *IOCountFilesConverter::fromJsonObject(QJsonObject jsonObj)
{
    TCountFiles *test = qobject_cast<TCountFiles*>(getTestMethod());
    test->setFolder(jsonObj.value(SP_FOLDER).toString());
    test->setFileNameMask(jsonObj.value(SP_MASK).toString());
    test->setIncludeSybFolder(jsonObj.value(SP_SUBFOLDERS).toBool());
    test->setTranslateMacros(jsonObj.value(SP_USE_MACROS).toBool());
    TCountFiles::CountCondition condition = (TCountFiles::CountCondition) m_CountConditionEnum.keyToValue(jsonObj.value(SP_COUNTMODE).toString().toStdString().data());
    test->setCondition(condition);
    if (condition != TCountFiles::AllFiles && condition != TCountFiles::SubfolderOnly) {
        test->setCountValue(jsonObj.value(SP_COUNTVALUE).toInt());
    }
    test->setAlertWhen(jsonObj.value(SP_FILESLIMIT).toInt());
    return test;
}
/******************************************************************/

} //namespace SDPO
