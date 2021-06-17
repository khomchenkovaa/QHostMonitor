#include "ioCompareFilesConverter.h"

#include <QTextCodec>

namespace SDPO {

IOCompareFilesConverter::IOCompareFilesConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
    int idx = TCompareFiles::staticMetaObject.indexOfEnumerator("AlertMode");
    m_AlertModeEnum = TCompareFiles::staticMetaObject.enumerator(idx);
}

/******************************************************************/

TestMethod *IOCompareFilesConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TCompareFiles();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOCompareFilesConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::CompareFiles)) {
        return false;
    }
    TCompareFiles *test = qobject_cast<TCompareFiles*>(m_TestMethod);
    if (key == SP_ALERTMODE) {
        TCompareFiles::AlertMode crAMode = (TCompareFiles::AlertMode) m_AlertModeEnum.keyToValue(value.toStdString().data());
        test->setAlertWhen(crAMode);
    } else if (key == SP_USE_MACROS_1) {
        test->setTranslateFirstMacros(value == "Yes");
    } else if (key == SP_USE_MACROS_2) {
        test->setTranslateSecondMacros(value == "Yes");
    } else if (key == SP_FILE_1) {
        test->setFirstFile(value);
    } else if (key == SP_FILE_2) {
        test->setSecondFile(value);
    } else if (key == SP_STRING) {
        test->setString(value);
    } else if (key == SP_ENCODING) {
        test->setCodecMibEnum(getMibForCodecName(value));
    } else if (key == SP_WHOLEWORDS) {
        test->setWholeWordsOnly(value == "Yes");
    } else if (key == SP_CASESENSITIVE) {
        test->setCaseSensitive(value == "Yes");
    } else if (key == SP_CHECKTIME) {
        test->setTime(value == "Yes");
    } else if (key == SP_CHECKSIZE) {
        test->setSize(value == "Yes");
    } else if (key == SP_CHECKCONTENT) {
        test->setContents(value == "Yes");
    } else if (key == SP_MISSINGCHECK) {
//  i don't know what to do
    } else {
        return false;
    }
    return true;
}
/******************************************************************/

void IOCompareFilesConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::CompareFiles)) {
        return;
    }
    TCompareFiles*test = qobject_cast<TCompareFiles*>(m_TestMethod);
    out << SP_ALERTMODE     << " = " << m_AlertModeEnum.key(test->getAlertWhen())    << endl;
    out << SP_FILE_1        << " = " << test->getFirstFile()                         << endl;
    out << SP_USE_MACROS_1  << " = " << (test->isTranslateFirstMacros()?"Yes":"No")  << endl;
    switch (test->getAlertWhen()) {
    case TCompareFiles::FilesDifferent:
    case TCompareFiles::FilesIdentical:
        out << SP_FILE_2        << " = " << test->getSecondFile()                        << endl;
        out << SP_USE_MACROS_2  << " = " << (test->isTranslateSecondMacros()?"Yes":"No") << endl;
        out << SP_CHECKTIME     << " = " << (test->isTime()?"Yes":"No")                  << endl;
        out << SP_CHECKSIZE     << " = " << (test->isSize()?"Yes":"No")                  << endl;
        out << SP_CHECKCONTENT  << " = " << (test->isContents()?"Yes":"No")              << endl;
        break;
    case TCompareFiles::ContainsFile:
    case TCompareFiles::DoesntContainFile:
        out << SP_FILE_2        << " = " << test->getSecondFile()                        << endl;
        out << SP_USE_MACROS_2  << " = " << (test->isTranslateSecondMacros()?"Yes":"No") << endl;
        break;
    case TCompareFiles::ContainsString:
    case TCompareFiles::DoesntContainString:
        out << SP_STRING        << " = " << test->getString()                            << endl;
        out << SP_ENCODING      << " = " << getCodecNameForMib(test->getCodecMibEnum())  << endl;
        out << SP_WHOLEWORDS    << " = " << (test->isWholeWordsOnly()?"Yes":"No")        << endl;
        out << SP_CASESENSITIVE << " = " << (test->isCaseSensitive()?"Yes":"No")         << endl;
        break;
    }
}

/******************************************************************/

QJsonObject IOCompareFilesConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::CompareFiles)) {
        return jsonObj;
    }
    TCompareFiles* test = qobject_cast<TCompareFiles*>(m_TestMethod);
    jsonObj.insert(SP_ALERTMODE, QJsonValue(m_AlertModeEnum.key(test->getAlertWhen())));
    jsonObj.insert(SP_FILE_1, QJsonValue(test->getFirstFile()));
    jsonObj.insert(SP_USE_MACROS_1, QJsonValue(test->isTranslateFirstMacros()));
    switch (test->getAlertWhen()) {
    case TCompareFiles::FilesDifferent:
    case TCompareFiles::FilesIdentical:
        jsonObj.insert(SP_FILE_2, QJsonValue(test->getSecondFile()));
        jsonObj.insert(SP_USE_MACROS_2, QJsonValue(test->isTranslateSecondMacros()));
        jsonObj.insert(SP_CHECKTIME, QJsonValue(test->isTime()));
        jsonObj.insert(SP_CHECKSIZE, QJsonValue(test->isSize()));
        jsonObj.insert(SP_CHECKCONTENT, QJsonValue(test->isContents()));
        break;
    case TCompareFiles::ContainsFile:
    case TCompareFiles::DoesntContainFile:
        jsonObj.insert(SP_FILE_2, QJsonValue(test->getSecondFile()));
        jsonObj.insert(SP_USE_MACROS_2, QJsonValue(test->isTranslateSecondMacros()));
        break;
    case TCompareFiles::ContainsString:
    case TCompareFiles::DoesntContainString:
        jsonObj.insert(SP_STRING, QJsonValue(test->getString()));
        jsonObj.insert(SP_ENCODING, QJsonValue(test->getCodecMibEnum()));
        jsonObj.insert(SP_WHOLEWORDS, QJsonValue(test->isWholeWordsOnly()));
        jsonObj.insert(SP_CASESENSITIVE, QJsonValue(test->isCaseSensitive()));
        break;
    }
    return jsonObj;
}

/******************************************************************/

TestMethod *IOCompareFilesConverter::fromJsonObject(QJsonObject jsonObj)
{
    TCompareFiles *test = qobject_cast<TCompareFiles*>(getTestMethod());
    TCompareFiles::AlertMode crAMode = (TCompareFiles::AlertMode) m_AlertModeEnum.keyToValue(jsonObj.value(SP_ALERTMODE).toString().toStdString().data());
    test->setAlertWhen(crAMode);
    test->setFirstFile(jsonObj.value(SP_FILE_1).toString());
    test->setTranslateFirstMacros(jsonObj.value(SP_USE_MACROS_1).toBool());
    switch (test->getAlertWhen()) {
    case TCompareFiles::FilesDifferent:
    case TCompareFiles::FilesIdentical:
        test->setSecondFile(jsonObj.value(SP_FILE_2).toString());
        test->setTranslateSecondMacros(jsonObj.value(SP_USE_MACROS_2).toBool());
        test->setTime(jsonObj.value(SP_CHECKTIME).toBool());
        test->setSize(jsonObj.value(SP_CHECKSIZE).toBool());
        test->setContents(jsonObj.value(SP_CHECKCONTENT).toBool());
        break;
    case TCompareFiles::ContainsFile:
    case TCompareFiles::DoesntContainFile:
        test->setSecondFile(jsonObj.value(SP_FILE_2).toString());
        test->setTranslateSecondMacros(jsonObj.value(SP_USE_MACROS_2).toBool());
        break;
    case TCompareFiles::ContainsString:
    case TCompareFiles::DoesntContainString:
        test->setString(jsonObj.value(SP_STRING).toString());
        test->setCodecMibEnum(jsonObj.value(SP_ENCODING).toInt());
        test->setWholeWordsOnly(jsonObj.value(SP_WHOLEWORDS).toBool());
        test->setCaseSensitive(jsonObj.value(SP_CASESENSITIVE).toBool());
        break;
    }

    return test;
}

/******************************************************************/

QString IOCompareFilesConverter::getCodecNameForMib(int mibEnum)
{
    QString result = "<Default>";
    QTextCodec *codec = QTextCodec::codecForMib(mibEnum);
    if (codec) {
        result = codec->name();
    }
    return result;
}

/******************************************************************/

int IOCompareFilesConverter::getMibForCodecName(QString name)
{
    int result = 0;
    QTextCodec *codec = QTextCodec::codecForName(name.toLatin1());
    if (codec) {
        result = codec->mibEnum();
    }
    return result;
}

/******************************************************************/

} //namespace SDPO
