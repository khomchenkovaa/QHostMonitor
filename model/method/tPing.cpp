#include "tPing.h"
#include "tEnums.h"
#include "settings.h"
#include <QProcess>

#include <QDebug>

namespace SDPO {

/******************************************************************/

TPing::TPing(QString addr, QObject *parent) :
    TestMethod(TMethodID::Ping, parent)
{
    QSettings s;
    a_Address      = addr;
    a_Packets      = s.value(SKEY_PING_Packets, SVAL_PING_Packets).toInt();
    a_Timeout      = s.value(SKEY_PING_Timeout, SVAL_PING_Timeout).toInt();
    a_PacketSize   = s.value(SKEY_PING_PacketSize, SVAL_PING_PacketSize).toInt();
    a_TimeToLive   = s.value(SKEY_PING_TTL, SVAL_PING_TTL).toInt();
    b_DontFragment = false;
    a_BadCriteria  = 90;
    a_DisplayMode  = TPing::Time;
}

/******************************************************************/

void TPing::run()
{
    m_Result.clear();
    writeLogTitle();

    QString command = getCommand();
    m_Log.append(QString("[Command]$ %1\n\n").arg(command));
    if (command.isEmpty()) {
        m_Result.error = "Command is empty";
        emit testFailed();
        return;
    }

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(command);
    if (!process.waitForStarted()) {
        m_Result.reply = getTestedObjectInfo() + " can not start";
        process.close();
        emit testFailed();
        return;
    }
    if(!process.waitForFinished(a_Timeout * a_Packets + a_Timeout)) {
        m_Result.reply = getTestedObjectInfo() + " terminated";
        process.close();
        emit testFailed();
        return;
    }
    if( process.exitStatus() == QProcess::NormalExit ) {
        parseResult(process.readAll().trimmed());
        emit testSuccess();
    } else {
        m_Result.error = process.errorString();
        emit testFailed();
    }
}

/******************************************************************/

QString TPing::getCommand() const
{
    PingProtocol protocol = PingProtocol::Unknown;
    QString address = a_Address;
    if (a_Address.endsWith("::ipv4")) {
        protocol = PingProtocol::IPV4;
        address = a_Address.left(a_Address.length()-6);
    } else if (a_Address.endsWith("::ipv6")) {
        protocol = PingProtocol::IPV6;
        address = a_Address.left(a_Address.length()-6);
    } else if (a_Address.contains("::")) {
        protocol = PingProtocol::IPV6;
    }

    if (protocol == PingProtocol::Unknown) {
        protocol = PingProtocol::IPV4;
    }

    QString cmd = (protocol == PingProtocol::IPV6) ? PING6_COMMAND : PING_COMMAND;
    if (a_Packets) cmd.append(QString(" -c %1").arg(a_Packets));
    if (a_TimeToLive) cmd.append(QString(" -t %1").arg(a_TimeToLive));
    if (a_Timeout) cmd.append(QString(" -W %1").arg(a_Timeout));
    if (a_PacketSize) cmd.append(QString(" -s %1").arg(a_PacketSize));
    if (b_DontFragment) cmd.append(" -M dont");
    cmd.append(QString(" %1").arg(address));
    return cmd;
}

/******************************************************************/

void TPing::parseResult(const QString &data)
{
    TestResult tResult;
    tResult.reply = "No answer";
    m_Log.append(data).append("\n\n");

    QStringList result = data.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

    PingStat pingStat;

    foreach(const QString &line, result) {
        if (errorScan(line, tResult)) {
            m_Log.append(tResult.error);
            tResult.reply = tResult.error;
            tResult.status = TestStatus::Bad;
            m_Result = tResult;
            return;
        }
        if (getPercentLossStatistics(line, pingStat)) {
            m_Log.append(tr("Ping stat: %1 packets transmitted, %2 received, %3% packet loss\n").arg(pingStat.transmitted).arg(pingStat.received).arg(pingStat.percentLoss));
            continue;
        }
        if (getRoundTrip(line, pingStat)) {
            m_Log.append(tr("Round trip: rtt min/avg/max/mdev = %1/%2/%3/0.000 ms\n").arg(pingStat.rttMin).arg(pingStat.rttAvg).arg(pingStat.rttMax));
            continue;
        }
    }

    if (pingStat.percentLoss < a_BadCriteria) {
        m_Log.append(QString("Percent loss %1 < %2; status = OK\n").arg(pingStat.percentLoss).arg(a_BadCriteria));
        tResult.status = TestStatus::Ok;
    } else {
        m_Log.append(QString("Percent loss %1 >= %2; status = BAD\n").arg(pingStat.percentLoss).arg(a_BadCriteria));
        tResult.status = TestStatus::Bad;
    }

    switch(a_DisplayMode) {
    case TPing::Time :
        tResult.reply = pingStat.rttAvg;
        tResult.replyDesc = QString("%1ms").arg(pingStat.rttAvg);
        break;
    case TPing::Lost :
        tResult.reply = pingStat.percentLoss;
        tResult.replyDesc = QString("%1%").arg(pingStat.percentLoss);
        break;
    case TPing::Received :
        tResult.reply = 100 - pingStat.percentLoss;
        tResult.replyDesc = QString("%1%").arg(100 - pingStat.percentLoss);
        break;
    }

    m_Result = tResult;
}

/******************************************************************/

TestMethod *TPing::clone()
{
    TPing *result = new TPing(a_Address, parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Packets = a_Packets;
    result->a_Timeout = a_Timeout;
    result->a_PacketSize = a_PacketSize;
    result->b_DontFragment = b_DontFragment;
    result->a_BadCriteria = a_BadCriteria;
    result->a_DisplayMode = a_DisplayMode;
    return result;
}

/******************************************************************/

QString TPing::getTestMethod() const
{
    return QString("ping (timeout - %1 ms)").arg(getTimeout());
}

/******************************************************************/

QString TPing::getTestedObjectInfo() const
{
    return QString("ping %1 (timeout - %2 ms)").arg(a_Address).arg(getTimeout());
}

/******************************************************************/

QString TPing::displayModeToString(TPing::DisplayMode mode)
{
    switch (mode) {
    case TPing::Time: return "time";
    case TPing::Lost: return "lost";
    case TPing::Received: return "received";
    }
    return QString();
}

/******************************************************************/

bool TPing::errorScan(const QString &line, TestResult &result)
{
    bool match = false;
    if (line.contains("Network is unreachable") || line.contains("Destination Net Unreachable")) {
        result.error = tr("CRITICAL - Network Unreachable %1").arg(a_Address);
        match = true;
    } else if (line.contains("Destination Host Unreachable")) {
        result.error = tr("CRITICAL - Host Unreachable %1").arg(a_Address);
        match = true;
    } else if (line.contains("Destination Port Unreachable")) {
        result.error = tr("CRITICAL - Bogus ICMP: Port Unreachable (%1)").arg(a_Address);
        match = true;
    } else if (line.contains("Destination Protocol Unreachable")) {
        result.error = tr("CRITICAL - Bogus ICMP: Protocol Unreachable (%1)").arg(a_Address);
        match = true;
    } else if (line.contains("Destination Net Prohibited")) {
        result.error = tr("CRITICAL - Network Prohibited (%1)").arg(a_Address);
        match = true;
    } else if (line.contains("Destination Host Prohibited")) {
        result.error = tr("CRITICAL - Host Prohibited (%1)").arg(a_Address);
        match = true;
    } else if (line.contains("Packet filtered")) {
        result.error = tr("CRITICAL - Packet filtered (%1)").arg(a_Address);
        match = true;
    } else if (line.contains("unknown host")) {
        result.error = tr("CRITICAL - Host not found (%1)").arg(a_Address);
        match = true;
    } else if (line.contains("Time to live exceeded")) {
        result.error = tr("CRITICAL - Time to live exceeded (%1)").arg(a_Address);
        match = true;
    } else if (line.contains("Destination unreachable: ")) {
        result.error = tr("CRITICAL - Destination Unreachable (%1)").arg(a_Address);
        match = true;
    }
    return match;
}

/******************************************************************/

bool TPing::getPercentLossStatistics(const QString &line, PingStat &stat)
{
    bool match = false;
    QStringList patterns = QStringList()
            << "(\\d+) packets transmitted, (\\d+) packets received, \\+\\d+ errors, (\\d+)% packet loss"
            << "(\\d+) packets transmitted, (\\d+) packets received, \\+\\d+ duplicates, (\\d+)% packet loss"
            << "(\\d+) packets transmitted, (\\d+) received, \\+\\d+ duplicates, (\\d+)% packet loss"
            << "(\\d+) packets transmitted, (\\d+) packets received, (\\d+)% packet loss"
            << "(\\d+) packets transmitted, (\\d+) packets received, (\\d+)% loss, time"
            << "(\\d+) packets transmitted, (\\d+) received, (\\d+)% loss, time"
            << "(\\d+) packets transmitted, (\\d+) received, (\\d+)% packet loss, time"
            << "(\\d+) packets transmitted, (\\d+) received, \\+\\d+ errors, (\\d+)% packet loss"
            << "(\\d+) packets transmitted (\\d+) received, \\+\\d+ errors, (\\d+)% packet loss";

    foreach (const QString &pattern, patterns) {
        QRegExp rx(pattern);
        if (rx.indexIn(line) != -1) {
            stat.transmitted = rx.cap(1).toInt();
            stat.received = rx.cap(2).toInt();
            stat.percentLoss = rx.cap(3).toInt();
            match = true;
            break;
        }
    }
    if (!match) {
        QString pattern = "[^\\(]+\\((\\d+)%\\s*\\)[^\\)]+ ";
        QRegExp rx(pattern);
        if (rx.indexIn(line) != -1) {
            stat.percentLoss = rx.cap(1).toInt();
            match = true;
        }
    }

    return match;
}

/******************************************************************/

bool TPing::getRoundTrip(const QString &line, PingStat &stat)
{
    bool match = false;
    QStringList patterns = QStringList()
            << "round-trip min/avg/max = (\\d+\\.\\d+)/(\\d+\\.\\d+)/(\\d+\\.\\d+)"
            << "round-trip min/avg/max/mdev = (\\d+\\.\\d+)/(\\d+\\.\\d+)/(\\d+\\.\\d+)"
            << "round-trip min/avg/max/sdev = (\\d+\\.\\d+)/(\\d+\\.\\d+)/(\\d+\\.\\d+)"
            << "round-trip min/avg/max/stddev = (\\d+\\.\\d+)/(\\d+\\.\\d+)/(\\d+\\.\\d+)"
            << "round-trip min/avg/max/std-dev = (\\d+\\.\\d+)/(\\d+\\.\\d+)/(\\d+\\.\\d+)"
            << "round-trip (ms) min/avg/max = (\\d+\\.\\d+)/(\\d+\\.\\d+)/(\\d+\\.\\d+)"
            << "round-trip (ms) min/avg/max/stddev = (\\d+\\.\\d+)/(\\d+\\.\\d+)/(\\d+\\.\\d+)"
            << "rtt min/avg/max/mdev = (\\d+\\.\\d+)/(\\d+\\.\\d+)/(\\d+\\.\\d+)";

    foreach (const QString &pattern, patterns) {
        QRegExp rx(pattern);
        if (rx.indexIn(line) != -1) {
            stat.rttMin = rx.cap(1).toDouble();
            stat.rttAvg = rx.cap(2).toDouble();
            stat.rttMax = rx.cap(3).toDouble();
            match = true;
            break;
        }
    }
    if (!match) {
        QString pattern = "[^=]* = (\\d+\\.\\d+)ms, [^=]* = (\\d+\\.\\d+)ms, [^=]* = (\\d+\\.\\d+)ms";
        QRegExp rx(pattern);
        if (rx.indexIn(line) != -1) {
            stat.rttMin = rx.cap(1).toDouble();
            stat.rttMax = rx.cap(2).toDouble();
            stat.rttAvg = rx.cap(3).toDouble();
            match = true;
        }
    }

    return match;
}

/******************************************************************/

} // namespace SDPO
