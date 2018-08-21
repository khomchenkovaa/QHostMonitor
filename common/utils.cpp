#include "utils.h"
#include <QString>
#include <QTime>
#include <QDebug>

namespace SDPO {

/******************************************************************/

static QString DESTRUCTOR_MSG =
        QStringLiteral("Running the %1 destructor.");

/******************************************************************/

void Utils::DestructorMsg(const QString &value)
{
    qDebug() << DESTRUCTOR_MSG.arg(value);
}

/******************************************************************/

void Utils::DestructorMsg(const QPointer<QObject> object)
{
    DestructorMsg(object->metaObject()->className());
}

/******************************************************************/

QString Utils::getTimeFromMs(qint64 tm)
{
    // [N days] HH:MM:SS
    int secs = (int) (tm / 1000);
    int days = (int) (secs / (24 * 60 * 60));
    QTime time(0,0,0,0);
    if (days > 0) {
        QTime t = time.addSecs(secs % (24 * 60 * 60));
        return QString("%1 days %2").arg(QString::number(days), t.toString("hh:mm:ss"));
    } else {
        QTime t = time.addSecs(secs);
        return t.toString("hh:mm:ss");
    }
}

/******************************************************************/

} // namespace
