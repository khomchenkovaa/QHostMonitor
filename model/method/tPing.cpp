#include "tPing.h"
#include "tEnums.h"
#include "mSettings.h"
#include <QProcess>

namespace SDPO {

/******************************************************************/

TPing::TPing(QString addr, QObject *parent) :
    TTestMethod(TMethodID::Ping, parent)
{
    a_Address      = addr;
    a_Packets      = Settings::get(Settings::Ping_Trace, Settings::Packets, QVariant(1)).toInt();
    a_Timeout      = Settings::get(Settings::Ping_Trace, Settings::Timeout, QVariant(0)).toInt();
    a_PacketSize   = Settings::get(Settings::Ping_Trace, Settings::PacketSize, QVariant(0)).toInt();
    b_DontFragment = false;
    a_BadCriteria  = 0.9;
    a_DisplayMode  = TPing::Time;
}

/******************************************************************/

void TPing::run()
{
    clearResult();

    QString command = getCommand();
    if (command.isEmpty()) {
        m_ErrorString = "Command is empty";
        emit testFailed();
        return;
    }

//    qDebug() << getTestMethod() << ":" << command;

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(command);
    if (!process.waitForStarted()) {
        m_Reply = getTestedObjectInfo() + " can not start";
        process.close();
        emit testFailed();
        return;
    }
    if(!process.waitForFinished(a_Timeout)) {
        m_Reply = getTestedObjectInfo() + " terminated";
        process.close();
        emit testFailed();
        return;
    }
    if( process.exitStatus() == QProcess::NormalExit ) {
        parseResult(process.readAll().trimmed());
        emit testSuccess();
    } else {
        m_ErrorString = process.errorString();
        emit testFailed();
    }
}

/******************************************************************/

QString TPing::getCommand() const
{
    int timeToLive = Settings::get(Settings::Ping_Trace, Settings::TTL, QVariant(3)).toInt();
    QString cmd = "ping";
    if (a_Packets > 0) cmd.append(QString(" -c %1").arg(a_Packets));
    if (timeToLive > 0) cmd.append(QString(" -t %1").arg(timeToLive));
//    if (a_Timeout > 0) cmd.append(QString(" -W %1").arg(a_Timeout));
    if (a_PacketSize > 0) cmd.append(QString(" -s %1").arg(a_PacketSize));
    if (b_DontFragment) cmd.append(" -M dont");
    cmd.append(QString(" -q %1").arg(a_Address));
    return cmd;
}

/******************************************************************/

void TPing::parseResult(QString data)
{
    QString newReply = "No answer";
    float newReplyFloat = 0.0;
    int newReplyInt = 0;
    TestStatus newStatus = TestStatus::Unknown;

    QStringList result = data.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

    if (result.count() > 2) {
        // parse packets and time;
        // "1 packets transmitted, 1 received, 0% packet loss, time 0ms"
        // "1 packets transmitted, 0 received, +1 errors, 100% packet loss, time 5ms"
        QStringList packs = result.at(2).split(',');
        // "1 packets transmitted"
        int packIdx = 0;
        QString tmp = packs.at(packIdx).trimmed();
        int transmitted = tmp.mid(0,tmp.indexOf(' ')).toInt();
        Q_UNUSED(transmitted)
        // "1 received"
        ++packIdx;
        tmp = packs.at(packIdx).trimmed();
        int received = tmp.mid(0,tmp.indexOf(' ')).toInt();
        Q_UNUSED(received)
        // (optional) +1 errors
        ++packIdx;
        int errors = 0;
        tmp = packs.at(packIdx).trimmed();
        if (tmp.contains("errors")) {
           errors = tmp.mid(0,tmp.indexOf(' ')).toInt();
           ++packIdx;
        }
        // 100% packet loss
        tmp = packs.at(packIdx).trimmed();
        int packetLoss = tmp.mid(0,tmp.indexOf('%')).toInt();
        // time 5ms
        ++packIdx;
        tmp = packs.at(packs.count()-1).trimmed();
        QString time = tmp.mid(tmp.indexOf(' '));

        newStatus = errors? TestStatus::Bad : TestStatus::Ok;

        /*
         * Parse rtt?
         * // "rtt min/avg/max/mdev = 0.013/0.013/0.013/0.000 ms"
           QString rtt = result.at(3).mid(result.at(3).lastIndexOf('=') + 2);
           QStringList rttList = rtt.split('/');
           newReply = rttList.at(1) + "ms";
           newReplyFloat = rttList.at(1).toFloat();
           newReplyInt = rttList.at(1).toInt();
         */

        switch(a_DisplayMode) {
            case TPing::Time :
                newReply =  time;
                newReplyInt = newReply.remove(QRegExp("[^\\d]+")).toInt();
                newReplyFloat = newReplyInt;
                break;
            case TPing::Lost :
                newReplyInt = packetLoss;
                newReplyFloat = packetLoss;
                newReply = QString("%1\%").arg(newReplyInt);
                break;
            case TPing::Received :
                newReplyInt = 100 - packetLoss;
                newReplyFloat = newReplyInt;
                newReply = QString("%1\%").arg(newReplyInt);
                break;
        }
    }

    if (result.count() == 1) {
        // ping: unknown host unknown.host.ru
        newStatus = TestStatus::Unknown;
        newReply = "unknown host";
    }

    m_Status = newStatus;
    m_Reply = newReply;
    m_ReplyDouble = newReplyFloat;
    m_ReplyInt = newReplyInt;
}

/******************************************************************/

TTestMethod *TPing::clone()
{
    TPing *result = new TPing(a_Address, parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
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

} // namespace SDPO
