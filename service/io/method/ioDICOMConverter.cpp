#include "ioDICOMConverter.h"

namespace SDPO {

/******************************************************************/

IODICOMConverter::IODICOMConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TestMethod *IODICOMConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TDicom();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IODICOMConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DICOM)) {
        return false;
    }
    TDicom *test = qobject_cast<TDicom*>(m_TestMethod);
    if (key == SP_HOST) {
        test->setHost(value);
    } else if (key == SP_PORT) {
        test->setPort(value.toInt());
    } else if (key == SP_TIMEOUT) {
        test->setTimeout(value.toInt());
    } else if (key == SP_CALLEDAE) {
        test->setCalledAeTitle(value);
    } else if (key == SP_CALLINGAE) {
        test->setCallingAeTitle(value);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IODICOMConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DICOM)) {
        return;
    }
    TDicom*test = qobject_cast<TDicom*>(m_TestMethod);
    out << SP_HOST      << " = " << test->getHost()           << endl;
    out << SP_PORT      << " = " << test->getPort()           << endl;
    out << SP_TIMEOUT   << " = " << test->getTimeout()        << endl;
    out << SP_CALLEDAE  << " = " << test->getCalledAeTitle()  << endl;
    out << SP_CALLINGAE << " = " << test->getCallingAeTitle() << endl;

}
/******************************************************************/

QJsonObject IODICOMConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DICOM)) {
        return jsonObj;
    }
    TDicom* test = qobject_cast<TDicom*>(m_TestMethod);
    jsonObj.insert(SP_HOST, QJsonValue(test->getHost()));
    jsonObj.insert(SP_PORT, QJsonValue(test->getPort()));
    jsonObj.insert(SP_TIMEOUT, QJsonValue(test->getTimeout()));
    jsonObj.insert(SP_CALLEDAE, QJsonValue(test->getCalledAeTitle()));
    jsonObj.insert(SP_CALLINGAE, QJsonValue(test->getCallingAeTitle()));
    return jsonObj;
}

/******************************************************************/

TestMethod *IODICOMConverter::fromJsonObject(QJsonObject jsonObj)
{
    TDicom *test = qobject_cast<TDicom*>(getTestMethod());
    test->setHost(jsonObj.value(SP_HOST).toString());
    test->setPort(jsonObj.value(SP_PORT).toInt());
    test->setTimeout(jsonObj.value(SP_TIMEOUT).toInt());
    test->setCalledAeTitle(jsonObj.value(SP_CALLEDAE).toString());
    test->setCallingAeTitle(jsonObj.value(SP_CALLINGAE).toString());
    return test;
}

/******************************************************************/

} //namespace SDPO
