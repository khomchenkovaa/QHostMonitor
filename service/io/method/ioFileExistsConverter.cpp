#include "ioFileExistsConverter.h"

namespace SDPO {

/***********************************************/

IOFileExistsConverter::IOFileExistsConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/***********************************************/

TTestMethod *IOFileExistsConverter::getTestMethod()
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

} // namespace SDPO
