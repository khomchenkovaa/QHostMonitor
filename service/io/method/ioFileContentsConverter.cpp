#include "ioFileContentsConverter.h"

namespace SDPO {

/******************************************************************/

IOFileContentsConverter::IOFileContentsConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TestMethod *IOFileContentsConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TFileContents();
    }
    return m_TestMethod;
}

/******************************************************************/

bool IOFileContentsConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::FileCRC)) {
        return false;
    }
    TFileContents *test = qobject_cast<TFileContents*>(m_TestMethod);
    if (key == SP_FILE) {
        test->setFile(value);
    } else if (key == SP_CRC) {
        test->setCrc(value);
        test->setRecalculateCrc(true);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOFileContentsConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::FileCRC)) {
        return;
    }
    TFileContents*test = qobject_cast<TFileContents*>(m_TestMethod);
    out << SP_FILE       << " = " << test->getFile()         << endl;
    if (test->isRecalculateCrc()) {
        out << SP_CRC    << " = " << test->getCrc()          << endl;
    }
}

/******************************************************************/

QJsonObject IOFileContentsConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::FileCRC)) {
        return jsonObj;
    }
    TFileContents* test = qobject_cast<TFileContents*>(m_TestMethod);
    jsonObj.insert(SP_FILE, QJsonValue(test->getFile()));
    if (test->isRecalculateCrc()) {
        jsonObj.insert(SP_CRC, QJsonValue(test->getCrc()));
        }
    return jsonObj;
}

/******************************************************************/

TestMethod *IOFileContentsConverter::fromJsonObject(QJsonObject jsonObj)
{
    TFileContents *test = qobject_cast<TFileContents*>(getTestMethod());
    test->setFile(jsonObj.value(SP_FILE).toString());
    if (test->isRecalculateCrc()) {
        test->setCrc(jsonObj.value(SP_CRC).toString());
    }
    return test;
}

/******************************************************************/

} //namespace SDPO
