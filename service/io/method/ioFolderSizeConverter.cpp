#include "ioFolderSizeConverter.h"

namespace SDPO {

/******************************************************************/

IOFolderSizeConverter::IOFolderSizeConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOFolderSizeConverter::getTestMethod()
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

} // namespace SDPO
