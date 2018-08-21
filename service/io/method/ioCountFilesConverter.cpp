#include "ioCountFilesConverter.h"

namespace SDPO {

/******************************************************************/

IOCountFilesConverter::IOCountFilesConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
    m_countMode << "AllFiles" << "OlderThan" << "NewerThan" << "BiggerThan" << "SmallerThan" << "SubfolderOnly";
}

/******************************************************************/

TTestMethod *IOCountFilesConverter::getTestMethod()
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
        int crCMode = m_countMode.indexOf(value);
        test->setSelectCountFiles(crCMode == -1 ? 0 : crCMode);
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
    TCountFiles*test = qobject_cast<TCountFiles*>(m_TestMethod);
    out << SP_FOLDER     << " = " << test->getFolder()                       << endl;
    out << SP_MASK       << " = " << test->getFileNameMask()                 << endl;
    out << SP_SUBFOLDERS << " = " << (test->isIncludeSybFolder()?"Yes":"No") << endl;
    out << SP_USE_MACROS << " = " << (test->isTranslateMacros()?"Yes":"No")  << endl;
    out << SP_COUNTMODE  << " = " << test->getSelectCountFiles()             << endl;
    out << SP_COUNTVALUE << " = " << test->getCountValue()                   << endl;
    out << SP_FILESLIMIT << " = " << test->getAlertWhen()                    << endl;

}
/******************************************************************/

} //namespace SDPO
