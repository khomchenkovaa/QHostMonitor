#include "tMethod.h"

namespace SDPO {

/*****************************************************************/

QVector<TGroup> TGroup::tGroupList;

/*****************************************************************/

QVector<TMethod> TMethod::tMethodList;

/*****************************************************************/

QString TMethod::toName(TMethodID method) {
    return TMethod::tMethodList.at((int)method).name;
}

/*****************************************************************/

TMethodID TMethod::fromString(const QString name) {
    TMethodID result = TMethodID::Empty;
    foreach( const TMethod &method, tMethodList) {
        if (name.compare(method.name, Qt::CaseInsensitive) == 0 ) {
            result = method.id;
            break;
        }
    }
    return result;
}

/*****************************************************************/

} // namespace SDPO
