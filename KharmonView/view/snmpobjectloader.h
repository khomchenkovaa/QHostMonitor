#ifndef SNMPOBJECTLOADER_H
#define SNMPOBJECTLOADER_H

#include "snmpobject.h"

namespace KharmonView {

class SnmpObjectLoader : public QObject
{
    Q_OBJECT
public:
    explicit SnmpObjectLoader(QObject *parent = nullptr);

public slots:
    void create();
    void load(const QString &fileName = QString());
    void save(const QString &fileName = QString());

signals:
    void loadFailed(const QString &err);

private:
    bool parseConf(const QString &diagConf);
    QString valueForKey(const QString &line, const QString &key) const;

private:
    QString m_FileName;

};

} // namespace KharmonView

#endif // SNMPOBJECTLOADER_H
