#include "gUserVars.h"

namespace SDPO {

/*****************************************************************/

QMap<QString, QString> GUserVars::variables;
QStringList GUserVars::favorite;

/*****************************************************************/

void GUserVars::add(const QString &key, const QString &value)
{
    variables[key] = value;
}

/*****************************************************************/

QString GUserVars::get(const QString &key)
{
    return variables.value(key, QString());
}

/*****************************************************************/

void GUserVars::replace(const QString &oldKey, const QString &newKey)
{
    QString value = variables.take(oldKey);
    variables[newKey] = value;
}

/*****************************************************************/

void GUserVars::remove(const QString &key)
{
    variables.remove(key);
}

/*****************************************************************/

} // namespace SDPO
