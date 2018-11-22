#include "ioPingConverter.h"

namespace SDPO {

/***********************************************/

IOPingConverter::IOPingConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
    int idx = TPing::staticMetaObject.indexOfEnumerator("DisplayMode");
    m_DisplayModeEnum = TPing::staticMetaObject.enumerator(idx);
}

/***********************************************/

TTestMethod *IOPingConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TPing(QString());
    }
    return m_TestMethod;
}

/***********************************************/

bool IOPingConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Ping)) {
        return false;
    }
    TPing *test = qobject_cast<TPing*>(m_TestMethod);
    if (key == SP_HOST) {
        test->setAddress(value);
    } else if (key == SP_RETRIES) {
        test->setPackets(value.toInt());
    } else if (key == SP_TIMEOUT) {
        test->setTimeout(value.toInt());
    } else if (key == SP_PACKET_SIZE) {
        test->setPacketSize(value.toInt());
    } else if (key == SP_DONT_FRAGMENT) {
        test->setDontFragment(value == "Yes");
    } else if (key == SP_MAX_LOST_RATIO) {
        test->setBadCriteria(value.toFloat() / 100);
    } else if (key == SP_DISPLAY_MODE) {
        if (value.compare("lost",Qt::CaseInsensitive) == 0) test->setDisplayMode(TPing::Lost);
        else if (value.compare("received",Qt::CaseInsensitive) == 0) test->setDisplayMode(TPing::Received);
        else test->setDisplayMode(TPing::Time); // "time"
    } else {
        return false;
    }
    return true;

}

/***********************************************/

void IOPingConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Ping)) {
        return;
    }
    TPing *test = qobject_cast<TPing*>(m_TestMethod);
    out << SP_HOST           << " = " << test->getAddress() << endl;
    out << SP_TIMEOUT        << " = " << test->getTimeout() << endl;
    out << SP_RETRIES        << " = " << test->getPackets() << endl;
    out << SP_MAX_LOST_RATIO << " = " << test->getBadCriteria() * 100 << endl;
    out << SP_PACKET_SIZE    << " = " << test->getPacketSize() << endl;
    out << SP_DISPLAY_MODE   << " = " << m_DisplayModeEnum.key(test->getDisplayMode()) << endl;
    out << SP_DONT_FRAGMENT  << " = " << QString(test->isDontFragment()?"Yes":"No") << endl;
}

/***********************************************/

QJsonObject IOPingConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Ping)) {
        return jsonObj;
    }
    TPing* test = qobject_cast<TPing*>(m_TestMethod);
    jsonObj.insert(SP_HOST, QJsonValue(test->getAddress()));
    jsonObj.insert(SP_TIMEOUT, QJsonValue(test->getTimeout()));
    jsonObj.insert(SP_RETRIES, QJsonValue(test->getPackets()));
    jsonObj.insert(SP_MAX_LOST_RATIO, QJsonValue(test->getBadCriteria()));
    jsonObj.insert(SP_PACKET_SIZE, QJsonValue(test->getPacketSize()));
    jsonObj.insert(SP_DISPLAY_MODE, QJsonValue(m_DisplayModeEnum.key(test->getDisplayMode())));
    jsonObj.insert(SP_DONT_FRAGMENT, QJsonValue(test->isDontFragment()));
    return jsonObj;
}

/***********************************************/

TTestMethod *IOPingConverter::fromJsonObject(QJsonObject jsonObj)
{
    TPing *test = qobject_cast<TPing*>(getTestMethod());
    test->setAddress(jsonObj.value(SP_HOST).toString());
    test->setTimeout(jsonObj.value(SP_TIMEOUT).toInt());
    test->setPackets(jsonObj.value(SP_RETRIES).toInt());
    test->setBadCriteria(jsonObj.value(SP_MAX_LOST_RATIO).toDouble());
    test->setPacketSize(jsonObj.value(SP_PACKET_SIZE).toInt());
    TPing::DisplayMode dispMode = (TPing::DisplayMode) m_DisplayModeEnum.keyToValue(jsonObj.value(SP_DISPLAY_MODE).toString().toStdString().data());
    test->setDisplayMode(dispMode);
    test->setDontFragment(jsonObj.value(SP_DONT_FRAGMENT).toBool());
    return test;
}

/***********************************************/

} // namespace SDPO
