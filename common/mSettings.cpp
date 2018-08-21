#include "mSettings.h"

namespace SDPO {

/******************************************************************/

Settings::Settings() {
    const QMetaObject &mo = staticMetaObject;
    int idx = mo.indexOfEnumerator("Key");
    keys = mo.enumerator(idx);

    idx = mo.indexOfEnumerator("Section");
    sections = mo.enumerator(idx);
}

/******************************************************************/

QVariant Settings::get(Section s, Key k, QVariant def) {
    Settings &self = instance();
    QString key = self.keyPath(s, k);
    return self.conf.value(key, def);
}

/******************************************************************/

Settings::ValueRef Settings::set(Section s, Key k) {
    Settings &self = instance();
    return ValueRef(self, self.keyPath(s, k));
}

/******************************************************************/

void Settings::save() {
    Settings &self = instance();
    self.conf.sync();
}

/******************************************************************/

Settings::ValueRef & Settings::ValueRef::operator = (const QVariant &data) {
    parent.conf.setValue(keyPath, data);
    return *this;
}

/******************************************************************/

QString Settings::keyPath(Section s, Key k) {
    QString section = sections.valueToKey(s);
    QString key = keys.valueToKey(k);
    return QString("%2/%1").arg(key).arg(section);
}

/******************************************************************/

Settings & Settings::instance() {
    static Settings singleton;
    return singleton;
}

/******************************************************************/

} // namespace SDPO
