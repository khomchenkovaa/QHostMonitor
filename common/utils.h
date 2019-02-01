#pragma once
#include <QWidget>
#include <QPointer>

namespace SDPO {

class Utils
{
public:
    Utils();

    static void DestructorMsg(const QString& value);
    static void DestructorMsg(const QPointer<QObject> object);
    static QString getTimeFromMs(qint64 tm);

private:
    // singleton
    explicit Utils(const Utils& rhs);
    Utils& operator= (const Utils& rhs);
};

} // namespace
