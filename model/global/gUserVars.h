#ifndef GUSERVARS_H
#define GUSERVARS_H

#include <QString>
#include <QMap>

namespace SDPO {

class GUserVars
{
public:
    static QMap<QString, QString> variables;
    static QStringList favorite;

    static void add(const QString &key, const QString &value);
    static QString get(const QString &key);
    static void replace(const QString &oldKey, const QString &newKey);
    static void remove(const QString &key);
};

} // namespace SDPO

#endif // GUSERVARS_H
