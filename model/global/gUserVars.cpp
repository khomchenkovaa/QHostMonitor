#include "gUserVars.h"

namespace SDPO {

/*****************************************************************/

QVariantMap GUserVars::variables;
QStringList GUserVars::favorite;

/*****************************************************************/

void GUserVars::add(const QString &key, const QVariant &value)
{
    variables[key] = value;
}

/*****************************************************************/

QVariant GUserVars::get(const QString &key)
{
    return variables.value(key, QString());
}

/*****************************************************************/

void GUserVars::replace(const QString &oldKey, const QString &newKey)
{
    QVariant value = variables.take(oldKey);
    variables[newKey] = value;
}

/*****************************************************************/

void GUserVars::remove(const QString &key)
{
    variables.remove(key);
}

/*****************************************************************/

} // namespace SDPO
