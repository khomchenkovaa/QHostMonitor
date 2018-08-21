#include "ioDICOMConverter.h"

namespace SDPO {

/******************************************************************/

IODICOMConverter::IODICOMConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IODICOMConverter::getTestMethod()
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


} //namespace SDPO
