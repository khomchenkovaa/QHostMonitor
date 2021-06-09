#pragma once
#include <QString>
#include <QPointer>

namespace SDPO {

class Utils
{
public:
    static void DestructorMsg(const QString& value);
    static void DestructorMsg(const QPointer<QObject> object);
    static QByteArray md5(const QString &text);
    static QString duration(qint64 msec);

private:
    // singleton
    explicit Utils(const Utils& rhs);
    Utils& operator= (const Utils& rhs);
};

} // namespace
