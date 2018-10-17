#include "tPing.h"
#include "tEnums.h"
#include "gSettings.h"
#include <QProcess>

namespace SDPO {

/******************************************************************/

TPing::TPing(QString addr, QObject *parent) :
    TTestMethod(TMethodID::Ping, parent)
{
    QSettings s;
    a_Address      = addr;
    a_Packets      = s.value(SKEY_PING_Packets, 1).toInt();
    a_Timeout      = s.value(SKEY_PING_Timeout, 0).toInt();
    a_PacketSize   = s.value(SKEY_PING_PacketSize, 0).toInt();
    a_TimeToLive   = s.value(SKEY_PING_TTL, 3).toInt();
    b_DontFragment = false;
    a_BadCriteria  = 0.9;
    a_DisplayMode  = TPing::Time;
}

/******************************************************************/

void TPing::run()
{
    m_Result.clear();

    QString command = getCommand();
    if (command.isEmpty()) {
        m_Result.error = "Command is empty";
        emit testFailed();
        return;
    }

//    qDebug() << getTestMethod() << ":" << command;

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(command);
    if (!process.waitForStarted()) {
        m_Result.reply = getTestedObjectInfo() + " can not start";
        process.close();
        emit testFailed();
        return;
    }
    if(!process.waitForFinished(a_Timeout)) {
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
    QString cmd = "ping";
    if (a_Packets > 0) cmd.append(QString(" -c %1").arg(a_Packets));
    if (a_TimeToLive > 0) cmd.append(QString(" -t %1").arg(a_TimeToLive));
//    if (a_Timeout > 0) cmd.append(QString(" -W %1").arg(a_Timeout));
    if (a_PacketSize > 0) cmd.append(QString(" -s %1").arg(a_PacketSize));
    if (b_DontFragment) cmd.append(" -M dont");
    cmd.append(QString(" -q %1").arg(a_Address));
    return cmd;
}

/******************************************************************/

void TPing::parseResult(QString data)
{
    TTestResult tResult;
    tResult.reply = "No answer";

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

        tResult.status = errors? TestStatus::Bad : TestStatus::Ok;

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
                tResult.reply =  time;
                tResult.replyInt = tResult.reply.remove(QRegExp("[^\\d]+")).toInt();
                tResult.replyDouble = tResult.replyInt;
                break;
            case TPing::Lost :
                tResult.replyInt = packetLoss;
                tResult.replyDouble = packetLoss;
                tResult.reply = QString("%1\%").arg(tResult.replyInt);
                break;
            case TPing::Received :
                tResult.replyInt = 100 - packetLoss;
                tResult.replyDouble = tResult.replyInt;
                tResult.reply = QString("%1\%").arg(tResult.replyInt);
                break;
        }
    }

    if (result.count() == 1) {
        // ping: unknown host unknown.host.ru
        tResult.status = TestStatus::Unknown;
        tResult.reply = "unknown host";
    }

    m_Result = tResult;
}

/******************************************************************/

TTestMethod *TPing::clone()
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

} // namespace SDPO
