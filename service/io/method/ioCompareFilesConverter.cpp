#include "ioCompareFilesConverter.h"

namespace SDPO {

IOCompareFilesConverter::IOCompareFilesConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
    m_alertMode << "FilesDifferent" << "FilesIdentical" << "ContainsFile" << "DoesntContainFile" << "ContainsString" << "DoesntContainString";
}

/******************************************************************/

TTestMethod *IOCompareFilesConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TCompareFiles();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOCompareFilesConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::FileCompare)) {
        return false;
    }
    TCompareFiles *test = qobject_cast<TCompareFiles*>(m_TestMethod);
    if (key == SP_ALERTMODE) {
        int crAMode = m_alertMode.indexOf(value);
        test->setAlertWhen(crAMode == -1 ? 0 : crAMode);
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
        test->setStringCoding(value);
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
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::FileCompare)) {
        return;
    }
    TCompareFiles*test = qobject_cast<TCompareFiles*>(m_TestMethod);
    out << SP_ALERTMODE     << " = " << test->getAlertWhen()                         << endl;
    out << SP_USE_MACROS_1  << " = " << (test->isTranslateFirstMacros()?"Yes":"No")  << endl;
    out << SP_USE_MACROS_2  << " = " << (test->isTranslateSecondMacros()?"Yes":"No") << endl;
    out << SP_FILE_1        << " = " << test->getFirstFile()                         << endl;
    out << SP_FILE_2        << " = " << test->getSecondFile()                        << endl;
    out << SP_STRING        << " = " << test->getString()                            << endl;
    out << SP_ENCODING      << " = " << test->getStringCoding()                      << endl;
    out << SP_CHECKTIME     << " = " << (test->isTime()?"Yes":"No")                  << endl;
    out << SP_CHECKSIZE     << " = " << (test->isSize()?"Yes":"No")                  << endl;
    out << SP_CHECKCONTENT  << " = " << (test->isContents()?"Yes":"No")              << endl;
    out << SP_WHOLEWORDS    << " = " << (test->isWholeWordsOnly()?"Yes":"No")        << endl;
    out << SP_CASESENSITIVE << " = " << (test->isCaseSensitive()?"Yes":"No")         << endl;



}
/******************************************************************/

} //namespace SDPO
