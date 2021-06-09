#include "utils.h"

#include <QCryptographicHash>
#include <QDateTime>

#include <QDebug>

using namespace SDPO;

/******************************************************************/

void Utils::DestructorMsg(const QString &value)
{
    static const QString DESTRUCTOR_MSG =
        QStringLiteral("Running the %1 destructor.");

    qDebug() << DESTRUCTOR_MSG.arg(value);
}

/******************************************************************/

void Utils::DestructorMsg(const QPointer<QObject> object)
{
    DestructorMsg(object->metaObject()->className());
}

/******************************************************************/

QByteArray Utils::md5(const QString &text)
{
    return QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Md5).toHex();
}

/******************************************************************/
//! convert msec to format '[N days] HH:MM:SS'
QString Utils::duration(qint64 msec)
{
    QDateTime dur = QDateTime::fromMSecsSinceEpoch(msec, Qt::UTC);
    qint64   days = QDateTime().daysTo(dur);
    QString hours = dur.toString("hh:mm:ss");
    if (days > 0) {
        return QString("%1 days %2").arg(days).arg(hours);
    }
    return hours;
}

/******************************************************************/
//! Print file size in human redabale format
QString Utils::sizeHuman(double dataSize)
{
    static const QStringList list =
        QStringList() << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("B");

    while(dataSize >= 1024.0 && i.hasNext())
    {
        unit = i.next();
        dataSize /= 1024.0;
    }
    return QString().setNum(dataSize,'f',2)+" "+unit;
}

/******************************************************************/
