#include "ioPingConverter.h"

namespace SDPO {

/***********************************************/

IOPingConverter::IOPingConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
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
        if (value == "lost") test->setDisplayMode(TPing::Lost);
        else if (value == "received") test->setDisplayMode(TPing::Received);
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
    out << SP_HOST           << " = " << test->getAddress()                          << endl;
    out << SP_TIMEOUT        << " = " << test->getTimeout()                          << endl;
    out << SP_RETRIES        << " = " << test->getPackets()                          << endl;
    out << SP_MAX_LOST_RATIO << " = " << test->getBadCriteria() * 100                << endl;
    out << SP_PACKET_SIZE    << " = " << test->getPacketSize()                       << endl;
    out << SP_DISPLAY_MODE   << " = " << displayModeToString(test->getDisplayMode()) << endl;
    out << SP_DONT_FRAGMENT  << " = " << QString(test->isDontFragment()?"Yes":"No")  << endl;
}

/***********************************************/

QString IOPingConverter::displayModeToString(TPing::DisplayMode mode)
{
    switch (mode) {
    case TPing::Time: return "time";
    case TPing::Lost: return "lost";
    case TPing::Received: return "received";
    }
    return QString();
}

/***********************************************/

} // namespace SDPO
