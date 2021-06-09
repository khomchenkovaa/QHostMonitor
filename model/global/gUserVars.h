#ifndef GUSERVARS_H
#define GUSERVARS_H

#include <QString>
#include <QVariant>

namespace SDPO {

struct GUserVars
{
    static QVariantMap variables;
    static QStringList favorite;

    static void add(const QString &key, const QVariant &value);
    static QVariant get(const QString &key);
    static void replace(const QString &oldKey, const QString &newKey);
    static void remove(const QString &key);
};

} // namespace SDPO

#endif // GUSERVARS_H
